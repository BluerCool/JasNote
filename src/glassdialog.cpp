#include "glassdialog.h"
#include "settings.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>

GlassDialog::GlassDialog(const QString &fileName, QWidget *parent)
    : QDialog(parent), m_fileName(fileName)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(S::DLG_W, S::DLG_H);
    setModal(true);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(S::DLG_ML, S::DLG_MT, S::DLG_MR, S::DLG_MB);

    auto *titleLabel = new QLabel("Save changes to " + fileName + "?");
    titleLabel->setStyleSheet(
        QString("color: %1; font-size: %2px; font-family: 'Cascadia Code', 'Fira Code', monospace; background: transparent; border: none;")
            .arg(S::DLG_TITLE_COLOR).arg(S::DLG_TITLE_SIZE)
    );
    titleLabel->setWordWrap(true);
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch();

    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    auto makeBtn = [](const QString &text, const QString &bg, const QString &hover) -> QPushButton* {
        auto *btn = new QPushButton(text);
        btn->setFixedSize(S::BTN_W, S::BTN_H);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            QString(
                "QPushButton {"
                "  color: %1;"
                "  background: %2;"
                "  border: 1px solid rgba(255,255,255,0.12);"
                "  border-radius: %3px;"
                "  font-size: %4px;"
                "  font-family: 'Cascadia Code', 'Fira Code', monospace;"
                "}"
                "QPushButton:hover {"
                "  background: %5;"
                "}"
            ).arg(S::BTN_COLOR).arg(bg).arg(S::BTN_RADIUS).arg(S::BTN_FONT_SIZE).arg(hover)
        );
        return btn;
    };

    auto *cancelBtn = makeBtn("Cancel", S::BTN_CANCEL_BG, S::BTN_CANCEL_HOVER);
    auto *dontSaveBtn = makeBtn("Don't Save", S::BTN_DONTSAVE_BG, S::BTN_DONTSAVE_HOVER);
    auto *saveBtn = makeBtn("Save", S::BTN_SAVE_BG, S::BTN_SAVE_HOVER);

    connect(saveBtn, &QPushButton::clicked, this, [this]() { done(Save); });
    connect(dontSaveBtn, &QPushButton::clicked, this, [this]() { done(DontSave); });
    connect(cancelBtn, &QPushButton::clicked, this, [this]() { done(Cancel); });

    buttonLayout->addWidget(cancelBtn);
    buttonLayout->addWidget(dontSaveBtn);
    buttonLayout->addWidget(saveBtn);

    mainLayout->addLayout(buttonLayout);
}

void GlassDialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QLinearGradient bg(0, 0, width(), height());
    bg.setColorAt(0.0, QColor(S::BG1_R, S::BG1_G, S::BG1_B, S::DLG_BG_ALPHA));
    bg.setColorAt(0.5, QColor(S::BG2_R, S::BG2_G, S::BG2_B, S::DLG_BG_ALPHA));
    bg.setColorAt(1.0, QColor(S::BG3_R, S::BG3_G, S::BG3_B, S::DLG_BG_ALPHA));

    QPainterPath path;
    path.addRoundedRect(QRectF(rect()), S::DLG_RADIUS, S::DLG_RADIUS);
    p.fillPath(path, bg);

    p.setPen(QPen(QColor(255, 255, 255, S::DLG_BORDER_ALPHA), S::DLG_BORDER_W));
    p.drawRoundedRect(QRectF(rect()), S::DLG_RADIUS, S::DLG_RADIUS);
}

void GlassDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void GlassDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPos);
        event->accept();
    }
}
