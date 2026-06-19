#pragma once
#include <QMainWindow>

class MarkdownEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    MarkdownEditor *m_editor;
};
