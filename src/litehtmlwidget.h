#ifndef LITEHTMLWIDGET_H
#define LITEHTMLWIDGET_H

#include <QWidget>
#include <litehtml.h>
#include "litehtmlcontainer.h"

class LiteHtmlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LiteHtmlWidget(QWidget *parent = nullptr);

    void setHtml(const QString &html);
    QString html() const { return m_html; }

    void setScrollY(int y);
    int scrollY() const { return m_scrollY; }
    int documentHeight() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void renderDocument();

    LiteHtmlContainer m_container;
    litehtml::document::ptr m_document;
    QString m_html;
    int m_scrollY = 0;
};

#endif // LITEHTMLWIDGET_H
