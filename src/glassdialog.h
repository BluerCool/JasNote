#pragma once
#include <QDialog>

class QLabel;
class QPushButton;

class GlassDialog : public QDialog
{
    Q_OBJECT
public:
    enum Result { Save = 1, DontSave = 0, Cancel = -1 };
    explicit GlassDialog(const QString &fileName, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QString m_fileName;
    QPoint m_dragPos;
};
