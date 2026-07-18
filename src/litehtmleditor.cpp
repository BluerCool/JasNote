#include "litehtmleditor.h"
#include "markdownconverter.h"
#include "settings.h"
#include <QStackedLayout>
#include <QKeyEvent>
#include <QMimeData>
#include <QImage>
#include <QImageReader>
#include <QUrl>
#include <QDir>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QGuiApplication>
#include <QClipboard>
#include <QTextCursor>
#include <QTimer>
#include <QScrollBar>

LiteHtmlEditor::LiteHtmlEditor(const QString &filePath, QWidget *parent)
    : QWidget(parent)
{
    setObjectName("liteHtmlEditor");

    m_input = new QPlainTextEdit(this);
    m_input->setObjectName("markdownInput");
    m_input->setTabStopDistance(S::ED_TAB_STOP);
    m_input->setLineWrapMode(QPlainTextEdit::WidgetWidth);

    QFont font(S::ED_FONT, S::ED_FONT_SIZE);
    m_input->setFont(font);

    m_input->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_input->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_input->setStyleSheet(
        QString(
            "QPlainTextEdit {"
            "  background-color: transparent;"
            "  color: transparent;"
            "  border: none;"
            "  padding: %1px;"
            "  selection-background-color: %2;"
            "  selection-color: rgba(255,255,255,0.3);"
            "}"
            "QScrollBar { width: 0px; height: 0px; }"
        ).arg(S::ED_PADDING).arg(S::ED_SEL_BG)
    );

    m_preview = new LiteHtmlWidget(this);
    m_preview->setStyleSheet("background: transparent;");

    auto *layout = new QStackedLayout(this);
    layout->setStackingMode(QStackedLayout::StackAll);
    layout->addWidget(m_input);
    layout->addWidget(m_preview);

    m_input->stackUnder(m_preview);

    m_pasteDir = QDir::currentPath() + "/pastes";
    QDir().mkpath(m_pasteDir);

    if (filePath.isEmpty()) {
        m_filePath = QDir::currentPath() + "/markdowns/note.md";
    } else {
        m_filePath = QFileInfo(filePath).absoluteFilePath();
    }

    m_saveTimer = new QTimer(this);
    m_saveTimer->setSingleShot(true);
    m_saveTimer->setInterval(S::ED_AUTOSAVE_MS);
    if (S::ED_AUTOSAVE_MS > 0)
        connect(m_saveTimer, &QTimer::timeout, this, &LiteHtmlEditor::autoSave);

    QFile file(m_filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString content = QString::fromUtf8(file.readAll());
        file.close();
        setMarkdown(content);
    } else {
        setMarkdown("# Welcome to JasNote\n\nPaste images with Ctrl+V or drag & drop files.");
    }

    connect(m_input, &QPlainTextEdit::textChanged, this, [this]() {
        if (!m_loading) {
            if (!m_modified) {
                m_modified = true;
                emit modificationChanged(true);
            }
            syncPreview();
            emit textChanged(toMarkdown());
            if (S::ED_AUTOSAVE_MS > 0)
                m_saveTimer->start();
        }
    });

    connect(m_input->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](int value) {
        m_preview->setScrollY(value);
    });
}

QString LiteHtmlEditor::toMarkdown() const
{
    return m_input->toPlainText();
}

void LiteHtmlEditor::setMarkdown(const QString &md)
{
    m_loading = true;
    m_input->setPlainText(md);
    m_preview->setHtml(MarkdownConverter::toHtml(md));
    m_loading = false;
}

void LiteHtmlEditor::syncPreview()
{
    m_preview->setHtml(MarkdownConverter::toHtml(m_input->toPlainText()));
}

void LiteHtmlEditor::save()
{
    QDir().mkpath(QFileInfo(m_filePath).absolutePath());
    QFile file(m_filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString md = m_input->toPlainText();
        while (md.endsWith('\n')) md.chop(1);
        file.write(md.toUtf8());
        file.close();
    }
    if (m_modified) {
        m_modified = false;
        emit modificationChanged(false);
    }
}

void LiteHtmlEditor::autoSave()
{
    save();
}

QString LiteHtmlEditor::fileName() const
{
    return QFileInfo(m_filePath).fileName();
}

void LiteHtmlEditor::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    m_input->resize(size());
    m_preview->resize(size());
}
