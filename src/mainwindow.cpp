#include "mainwindow.h"
#include "markdowneditor.h"
#include "glassdialog.h"
#include "titlebar.h"
#include "settings.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QVBoxLayout>
#include <QLabel>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QSysInfo>

bool MainWindow::isTilingWM()
{
    return !qgetenv("NIRI_SOCKET").isEmpty()
        || !qgetenv("SWAYSOCK").isEmpty()
        || !qgetenv("I3SOCK").isEmpty()
        || !qgetenv("HYPRLAND_INSTANCE_SIGNATURE").isEmpty();
}

MainWindow::MainWindow(const QString &filePath, QWidget *parent)
    : QMainWindow(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(false);
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(S::WIN_MIN_W, S::WIN_MIN_H);
    resize(S::WIN_DEFAULT_W, S::WIN_DEFAULT_H);

    m_customChrome = (QSysInfo::productType() == "windows");

    auto *central = new QWidget(this);
    central->setObjectName("centralContainer");
    setCentralWidget(central);

    auto *layout = new QVBoxLayout(central);
    layout->setContentsMargins(S::WIN_LAYOUT_MARGIN, S::WIN_LAYOUT_MARGIN,
                               S::WIN_LAYOUT_MARGIN, S::WIN_LAYOUT_MARGIN);

    if (m_customChrome) {
        auto *titleBar = new TitleBar(this);
        layout->addWidget(titleBar);
    }

    m_editor = new MarkdownEditor(filePath, this);
    layout->addWidget(m_editor, 1);

    m_statusLabel = new QLabel(central);
    m_statusLabel->setStyleSheet(
        QString("color: %1; font-size: %2px; font-family: '%3'; background: transparent; border: none;")
            .arg(S::STATUS_COLOR).arg(S::STATUS_FONT_SIZE).arg(S::STATUS_FONT)
    );
    m_statusLabel->setContentsMargins(S::STATUS_MARGIN_LEFT, 0, 0, 0);
    updateStatusLabel();

    connect(m_editor, &MarkdownEditor::modificationChanged, this, [this](bool) {
        updateStatusLabel();
    });
}

void MainWindow::updateStatusLabel()
{
    QString path = m_editor->filePath();
    if (m_editor->isModified()) {
        m_statusLabel->setText(
            QString("%1 <span style='color: %2; font-size: %3px;'>*</span>")
                .arg(path.toHtmlEscaped())
                .arg(S::STATUS_MODIFIED)
                .arg(S::STATUS_MODIFIED_SIZE)
        );
    } else {
        m_statusLabel->setText(path);
    }
}

void MainWindow::setWindowOpacity(qreal opacity)
{
    m_windowOpacity = qBound(0.0, opacity, 1.0);
    update();
    emit windowOpacityChanged();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    int bgAlpha = qRound(255 * m_windowOpacity);
    int borderAlpha = qRound(S::WIN_BORDER_ALPHA_BASE + (255 - S::WIN_BORDER_ALPHA_BASE) * m_windowOpacity);

    QLinearGradient bg(0, 0, width(), height());
    bg.setColorAt(0.0, QColor(S::BG1_R, S::BG1_G, S::BG1_B, bgAlpha));
    bg.setColorAt(0.5, QColor(S::BG2_R, S::BG2_G, S::BG2_B, bgAlpha));
    bg.setColorAt(1.0, QColor(S::BG3_R, S::BG3_G, S::BG3_B, bgAlpha));

    QPainterPath path;
    if (m_customChrome) {
        path.addRoundedRect(QRectF(rect()), S::WIN_RADIUS, S::WIN_RADIUS);
    } else {
        path.addRect(QRectF(rect()));
    }
    p.fillPath(path, bg);

    p.setPen(QPen(QColor(255, 255, 255, borderAlpha), S::WIN_BORDER_WIDTH));
    if (m_customChrome) {
        p.drawRoundedRect(QRectF(rect()), S::WIN_RADIUS, S::WIN_RADIUS);
    } else {
        p.drawRect(QRectF(rect()));
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (m_statusLabel) {
        m_statusLabel->setGeometry(S::STATUS_X, height() - S::STATUS_Y_OFFSET,
                                   S::STATUS_W, S::STATUS_H);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (m_editor->isModified()) {
        GlassDialog dialog(m_editor->fileName(), this);
        int result = dialog.exec();
        if (result == GlassDialog::Save) {
            m_editor->save();
            event->accept();
        } else if (result == GlassDialog::DontSave) {
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        event->accept();
    }
}
