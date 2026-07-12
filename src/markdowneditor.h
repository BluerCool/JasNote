#pragma once
#include <QTextEdit>

class QTimer;

class MarkdownEditor : public QTextEdit
{
    Q_OBJECT
public:
    explicit MarkdownEditor(const QString &filePath = QString(), QWidget *parent = nullptr);

    QString toMarkdown() const;
    void setMarkdown(const QString &md);
    void save();
    bool isModified() const { return m_modified; }
    QString filePath() const;
    QString fileName() const;

    Q_INVOKABLE bool handlePaste();

signals:
    void textChanged(const QString &text);
    void modificationChanged(bool modified);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void insertFromMimeData(const QMimeData *source) override;

private slots:
    void autoSave();

private:
    bool m_loading = false;
    bool m_modified = false;
    QString m_pasteDir;
    QString m_filePath;
    QTimer *m_saveTimer;
};
