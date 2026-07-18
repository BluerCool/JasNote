#ifndef LITEHTMLEDITOR_H
#define LITEHTMLEDITOR_H

#include <QWidget>
#include <QPlainTextEdit>
#include "litehtmlwidget.h"

class QTimer;

class LiteHtmlEditor : public QWidget
{
    Q_OBJECT
public:
    explicit LiteHtmlEditor(const QString &filePath = QString(), QWidget *parent = nullptr);

    QString toMarkdown() const;
    void setMarkdown(const QString &md);
    void save();
    bool isModified() const { return m_modified; }
    QString filePath() const { return m_filePath; }
    QString fileName() const;

signals:
    void textChanged(const QString &text);
    void modificationChanged(bool modified);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void autoSave();
    void syncPreview();

private:
    QPlainTextEdit *m_input;
    LiteHtmlWidget *m_preview;
    bool m_loading = false;
    bool m_modified = false;
    QString m_pasteDir;
    QString m_filePath;
    QTimer *m_saveTimer;
};

#endif // LITEHTMLEDITOR_H
