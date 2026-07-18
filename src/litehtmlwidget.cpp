#include "litehtmlwidget.h"
#include <QPainter>

static const char *MASTER_CSS = R"(
    * { margin: 0; padding: 0; box-sizing: border-box; }
    body {
        color: #d4d4dc;
        font-family: 'Cascadia Code', 'Fira Code', monospace;
        font-size: 14px;
        line-height: 1.6;
        padding: 16px;
        background: transparent;
    }
    h1 { font-size: 26px; color: #e8e8ec; font-weight: bold; margin: 18px 0 10px 0; }
    h2 { font-size: 21px; color: #e0e0e6; font-weight: bold; margin: 16px 0 8px 0; }
    h3 { font-size: 17px; color: #d8d8de; font-weight: bold; margin: 14px 0 6px 0; }
    h4 { font-size: 15px; color: #d4d4dc; font-weight: bold; margin: 12px 0 4px 0; }
    h5, h6 { font-size: 14px; color: #c0c0c8; font-weight: bold; margin: 10px 0 4px 0; }
    code {
        font-family: 'Cascadia Code', 'Fira Code', monospace;
        background: rgba(255,255,255,0.08);
        padding: 2px 5px;
        border-radius: 4px;
        font-size: 13px;
    }
    pre {
        background: rgba(255,255,255,0.06);
        padding: 14px;
        border-radius: 8px;
        margin: 10px 0;
        overflow-x: auto;
    }
    pre code { background: transparent; padding: 0; font-size: 13px; }
    a { color: #4ec9b0; text-decoration: none; }
    blockquote {
        border-left: 3px solid #4ec9b0;
        padding-left: 14px;
        color: rgba(212,212,220,0.6);
        margin: 8px 0;
    }
    hr {
        border: none;
        border-top: 1px solid rgba(255,255,255,0.12);
        margin: 18px 0;
    }
    table { border-collapse: collapse; margin: 10px 0; width: 100%; }
    th {
        background: rgba(255,255,255,0.08);
        font-weight: bold;
        border: 1px solid rgba(255,255,255,0.15);
        padding: 7px 14px;
    }
    td {
        border: 1px solid rgba(255,255,255,0.15);
        padding: 7px 14px;
    }
    ul, ol { margin: 4px 0 4px 20px; }
    li { margin: 3px 0; }
    img { max-width: 100%; border-radius: 6px; }
    p { margin: 6px 0; }
)";

LiteHtmlWidget::LiteHtmlWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
}

void LiteHtmlWidget::setHtml(const QString &html)
{
    m_html = html;
    renderDocument();
    update();
}

void LiteHtmlWidget::renderDocument()
{
    QByteArray utf8 = m_html.toUtf8();
    m_document = litehtml::document::createFromString(
        utf8.constData(), &m_container, MASTER_CSS);

    if (m_document) {
        m_container.setWidgetSize(width(), height());
        int bestWidth = m_document->render(width());
        if (bestWidth < width()) {
            m_document->render(bestWidth);
        }
    }
}

void LiteHtmlWidget::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::transparent);

    if (!m_document) return;

    m_container.setPainter(&painter);
    m_container.setWidgetSize(width(), height());
    m_container.setScrollY(m_scrollY);

    litehtml::position clip(0, 0, width(), height());
    m_document->draw(0, 0, -m_scrollY, &clip);
}

void LiteHtmlWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_document) {
        m_container.setWidgetSize(width(), height());
        m_document->media_changed();
        renderDocument();
    }
}

void LiteHtmlWidget::setScrollY(int y)
{
    m_scrollY = y;
    update();
}

int LiteHtmlWidget::documentHeight() const
{
    if (m_document) return m_document->height();
    return 0;
}
