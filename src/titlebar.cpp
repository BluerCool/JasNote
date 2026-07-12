#include "titlebar.h"
#include "settings.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

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

    auto makeBtn = [](const QString &text, const QString &name, const QString &hoverColor) -> QPushButton* {
        auto *btn = new QPushButton(text);
        btn->setObjectName(name);
        btn->setFixedSize(S::TB_BTN_SIZE, S::TB_BTN_SIZE);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setStyleSheet(
            QString(
                "QPushButton {"
                "  color: %1;"
                "  background: transparent;"
                "  border: none;"
                "  font-size: %2px;"
                "}"
                "QPushButton:hover {"
                "  background: %3;"
                "  color: white;"
                "}"
            ).arg(S::TB_BTN_COLOR).arg(S::TB_BTN_FONT).arg(hoverColor)
        );
        return btn;
    };

    m_minBtn = makeBtn(QString::fromUtf8("\xe2\x94\x80"), "minBtn", S::TB_BTN_HOVER);
    m_maxBtn = makeBtn(QString::fromUtf8("\xe2\x96\xa1"), "maxBtn", S::TB_BTN_HOVER);
    m_closeBtn = makeBtn(QString::fromUtf8("\xc3\x97"), "closeBtn", S::TB_BTN_CLOSE_HOVER);

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
