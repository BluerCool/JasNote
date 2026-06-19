#pragma once
#include <QWidget>

class QTextEdit;
class QSplitter;
class QTextBrowser;

class MarkdownEditor : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownEditor(QWidget *parent = nullptr);
    ~MarkdownEditor() override = default;

    QString toMarkdown() const;
    void setMarkdown(const QString &md);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updatePreview();

private:
    QTextEdit *m_edit;
    QTextBrowser *m_preview;
    QSplitter *m_splitter;
};
