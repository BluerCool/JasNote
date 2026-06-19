#include "markdowneditor.h"
#include <QTextEdit>
#include <QTextBrowser>
#include <QSplitter>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>

MarkdownEditor::MarkdownEditor(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_splitter = new QSplitter(Qt::Horizontal, this);

    m_edit = new QTextEdit(this);
    m_edit->setPlaceholderText("Start writing markdown...");
    m_edit->setFrameShape(QFrame::NoFrame);
    m_edit->setStyleSheet(R"(
        QTextEdit {
            background-color: rgba(28, 32, 40, 190);
            color: #d4d4dc;
            border: none;
            font-family: 'Cascadia Code', 'Fira Code', 'JetBrains Mono', monospace;
            font-size: 14px;
            padding: 16px;
            selection-background-color: #2a6f6f;
            selection-color: white;
        }
    )");

    m_preview = new QTextBrowser(this);
    m_preview->setFrameShape(QFrame::NoFrame);
    m_preview->setStyleSheet(R"(
        QTextBrowser {
            background-color: rgba(28, 32, 40, 170);
            color: #d4d4dc;
            border: none;
            font-family: 'Segoe UI', 'Noto Sans', sans-serif;
            font-size: 14px;
            padding: 16px;
            selection-background-color: #2a6f6f;
            selection-color: white;
        }
    )");

    m_preview->document()->setDefaultStyleSheet(R"(
        body { color: #d4d4dc; font-family: 'Segoe UI', sans-serif; font-size: 14px; line-height: 1.6; margin: 0; }
        h1, h2, h3, h4 { color: #4ec9b0; }
        h1 { border-bottom: 1px solid rgba(78, 201, 176, 0.3); padding-bottom: 8px; }
        h2 { border-bottom: 1px solid rgba(78, 201, 176, 0.2); padding-bottom: 4px; }
        code { background: rgba(78, 201, 176, 0.15); color: #b5cea8; padding: 2px 6px; border-radius: 4px; font-family: 'Cascadia Code', monospace; }
        pre { background: rgba(0, 0, 0, 0.3); padding: 16px; border-radius: 8px; border-left: 3px solid #4ec9b0; }
        blockquote { border-left: 3px solid #4ec9b0; margin: 0; padding: 4px 16px; background: rgba(78, 201, 176, 0.05); }
        a { color: #4ec9b0; text-decoration: none; }
        a:hover { text-decoration: underline; }
        table { border-collapse: collapse; width: 100%; }
        th, td { border: 1px solid rgba(78, 201, 176, 0.2); padding: 8px 12px; text-align: left; }
        th { background: rgba(78, 201, 176, 0.1); }
        hr { border: none; border-top: 1px solid rgba(78, 201, 176, 0.2); }
    )");

    m_splitter->addWidget(m_edit);
    m_splitter->addWidget(m_preview);
    m_splitter->setStretchFactor(0, 1);
    m_splitter->setStretchFactor(1, 1);
    m_splitter->setHandleWidth(4);
    m_splitter->setStyleSheet(R"(
        QSplitter::handle {
            background: rgba(78, 201, 176, 80);
            border-radius: 2px;
        }
        QSplitter::handle:hover {
            background: rgba(78, 201, 176, 180);
        }
    )");

    layout->addWidget(m_splitter);

    connect(m_edit, &QTextEdit::textChanged, this, &MarkdownEditor::updatePreview);

    setMarkdown("# Welcome to JasNote\n\nEdit markdown on the left. **Preview** updates live on the right.\n\n## Features\n\n- Split-pane editor & preview\n- Frosted glass design\n- Live markdown rendering\n- Teal accent theme\n\n> Write beautifully.");
}

void MarkdownEditor::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 12, 12);
    p.setClipPath(path);

    QLinearGradient g(0, 0, 0, height());
    g.setColorAt(0.0, QColor(78, 201, 176, 10));
    g.setColorAt(0.5, QColor(78, 201, 176, 0));
    g.setColorAt(1.0, QColor(78, 201, 176, 5));
    p.fillRect(rect(), g);

    QLinearGradient eg(0, 0, width(), 0);
    eg.setColorAt(0.0, QColor(255, 255, 255, 0));
    eg.setColorAt(0.5, QColor(255, 255, 255, 10));
    eg.setColorAt(1.0, QColor(255, 255, 255, 0));
    p.setPen(QPen(eg, 1));
    p.drawRoundedRect(QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5), 12, 12);
}

QString MarkdownEditor::toMarkdown() const
{
    return m_edit->toPlainText();
}

void MarkdownEditor::setMarkdown(const QString &md)
{
    m_edit->setPlainText(md);
    updatePreview();
}

void MarkdownEditor::updatePreview()
{
    m_preview->setMarkdown(m_edit->toPlainText());
}
