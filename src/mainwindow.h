#pragma once
#include <QMainWindow>

class MarkdownEditor;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(qreal windowOpacity READ windowOpacity WRITE setWindowOpacity NOTIFY windowOpacityChanged)
public:
    explicit MainWindow(const QString &filePath = QString(), QWidget *parent = nullptr);

    qreal windowOpacity() const { return m_windowOpacity; }

public slots:
    void setWindowOpacity(qreal opacity);

signals:
    void windowOpacityChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateStatusLabel();
    static bool isTilingWM();

    MarkdownEditor *m_editor;
    QLabel *m_statusLabel;
    qreal m_windowOpacity = 0.25;
    bool m_customChrome = false;
};
