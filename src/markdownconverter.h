#pragma once
#include <QString>

class QTextDocument;

class MarkdownConverter
{
public:
    static void renderToDocument(const QString &markdown, QTextDocument *doc);
    static QString toHtml(const QString &markdown);
    static QString documentToMarkdown(QTextDocument *doc);
};
