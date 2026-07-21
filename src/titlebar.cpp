#include "titlebar.h"
#include "settings.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include <QSvgRenderer>

static QByteArray svgMinimize()
{
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 20 20">)"
           R"(<rect x="4" y="9" width="12" height="1.5" rx="0.75" fill="white"/>)"
           R"(</svg>)";
}

static QByteArray svgMaximize()
{
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 20 20">)"
           R"(<rect x="4" y="4" width="12" height="12" rx="1.5" fill="none" stroke="white" stroke-width="1.4"/>)"
           R"(</svg>)";
}

static QByteArray svgRestore()
{
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 20 20">)"
           R"(<rect x="2" y="5.5" width="10" height="10" rx="1.5" fill="#1a1e28" stroke="white" stroke-width="1.3"/>)"
           R"(<rect x="7" y="2.5" width="10" height="10" rx="1.5" fill="#1a1e28" stroke="white" stroke-width="1.3"/>)"
           R"(</svg>)";
}

static QByteArray svgClose()
{
    return R"(<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 20 20">)"
           R"(<line x1="5.5" y1="5.5" x2="14.5" y2="14.5" stroke="white" stroke-width="1.4" stroke-linecap="round"/>)"
           R"(<line x1="14.5" y1="5.5" x2="5.5" y2="14.5" stroke="white" stroke-width="1.4" stroke-linecap="round"/>)"
           R"(</svg>)";
}

static QPixmap renderSvg(const QByteArray &svg, int size)
{
    QSvgRenderer renderer(svg);
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    renderer.render(&painter);
    return pixmap;
}

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(S::TB_HEIGHT);
    setStyleSheet("background: transparent;");

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(12, 0, 4, 0);
    layout->setSpacing(0);

    m_title = new QLabel(S::TB_TITLE);
    m_title->setStyleSheet(
        QString("color: %1; font-size: %2px; font-family: '%3'; background: transparent; border: none;")
            .arg(S::TB_COLOR).arg(S::TB_FONT_SIZE).arg(S::TB_FONT)
    );
    layout->addWidget(m_title);
    layout->addStretch();

    auto makeBtn = [](const QString &objName, const QByteArray &svg, const QString &hoverBg) -> QPushButton* {
        auto *btn = new QPushButton;
        btn->setObjectName(objName);
        btn->setFixedSize(S::TB_BTN_SIZE, S::TB_BTN_SIZE);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setIcon(QIcon(renderSvg(svg, S::TB_BTN_ICON)));
        btn->setIconSize(QSize(S::TB_BTN_ICON, S::TB_BTN_ICON));
        btn->setStyleSheet(
            QString(
                "QPushButton {"
                "  background: transparent;"
                "  border: none;"
                "  border-radius: %1px;"
                "}"
                "QPushButton:hover {"
                "  background: %2;"
                "}"
            ).arg(S::TB_BTN_SIZE / 2).arg(hoverBg)
        );
        return btn;
    };

    m_minBtn = makeBtn("minBtn", svgMinimize(), S::TB_BTN_HOVER);
    m_maxBtn = makeBtn("maxBtn", svgMaximize(), S::TB_BTN_HOVER);
    m_closeBtn = makeBtn("closeBtn", svgClose(), S::TB_BTN_CLOSE_HOVER);
    m_closeBtn->setFixedSize(S::TB_BTN_SIZE + 1, S::TB_BTN_SIZE + 1);

    connect(m_minBtn, &QPushButton::clicked, this, [this]() { window()->showMinimized(); });
    connect(m_maxBtn, &QPushButton::clicked, this, [this]() {
        if (window()->isMaximized()) window()->showNormal();
        else window()->showMaximized();
    });
    connect(m_closeBtn, &QPushButton::clicked, this, [this]() { window()->close(); });

    layout->addWidget(m_minBtn);
    layout->addWidget(m_maxBtn);
    layout->addWidget(m_closeBtn);
}

void TitleBar::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
        updateMaxButton();
    QWidget::changeEvent(event);
}

void TitleBar::updateMaxButton()
{
    bool maximized = window() && window()->isMaximized();
    m_maxBtn->setIcon(QIcon(renderSvg(maximized ? svgRestore() : svgMaximize(), S::TB_BTN_ICON)));
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPos = event->globalPosition().toPoint() - window()->frameGeometry().topLeft();
        event->accept();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        window()->move(event->globalPosition().toPoint() - m_dragPos);
        event->accept();
    }
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (QWidget *w = window()) {
        if (w->isMaximized()) w->showNormal();
        else w->showMaximized();
    }
    event->accept();
}
