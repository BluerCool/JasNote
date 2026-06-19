#include "mainwindow.h"
#include "markdowneditor.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumSize(900, 600);
    resize(1100, 750);

    auto *central = new QWidget(this);
    central->setObjectName("centralContainer");
    setCentralWidget(central);

    auto *layout = new QVBoxLayout(central);
    layout->setContentsMargins(16, 16, 16, 16);

    m_editor = new MarkdownEditor(this);
    layout->addWidget(m_editor);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 16, 16);
    p.setClipPath(path);

    QLinearGradient bg(0, 0, width(), height());
    bg.setColorAt(0.0, QColor(18, 22, 30, 220));
    bg.setColorAt(0.5, QColor(22, 28, 38, 210));
    bg.setColorAt(1.0, QColor(16, 20, 28, 225));
    p.fillRect(rect(), bg);

    QLinearGradient edge(0, 0, 0, height());
    edge.setColorAt(0.0, QColor(255, 255, 255, 35));
    edge.setColorAt(0.5, QColor(255, 255, 255, 5));
    edge.setColorAt(1.0, QColor(255, 255, 255, 20));
    p.setPen(QPen(edge, 1));
    p.drawRoundedRect(QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5), 16, 16);
}
