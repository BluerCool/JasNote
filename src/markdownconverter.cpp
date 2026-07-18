#include "markdownconverter.h"
#include <QTextDocument>
#include <QTextCursor>
#include <cmark-gfm.h>
#include <cmark-gfm-extension_api.h>
#include <cmark-gfm-core-extensions.h>

static QString markdownToHtml(const QString &markdown)
{
    QByteArray utf8 = markdown.toUtf8();

    cmark_gfm_core_extensions_ensure_registered();

    cmark_parser *parser = cmark_parser_new(CMARK_OPT_DEFAULT | CMARK_OPT_UNSAFE);

    const char *ext_names[] = {"strikethrough", "table", "autolink", "tagfilter", "tasklist"};
    for (const char *name : ext_names) {
        cmark_syntax_extension *ext = cmark_find_syntax_extension(name);
        if (ext) cmark_parser_attach_syntax_extension(parser, ext);
    }

    cmark_parser_feed(parser, utf8.constData(), utf8.size());
    cmark_node *root = cmark_parser_finish(parser);
    cmark_parser_free(parser);

    if (!root) return markdown;

    cmark_mem *mem = cmark_get_default_mem_allocator();
    cmark_llist *exts = nullptr;
    for (const char *name : ext_names) {
        cmark_syntax_extension *ext = cmark_find_syntax_extension(name);
        if (ext) exts = cmark_llist_append(mem, exts, ext);
    }
    char *html = cmark_render_html(root, CMARK_OPT_UNSAFE, exts);
    cmark_llist_free(mem, exts);
    cmark_node_free(root);

    if (!html) return markdown;

    QString result = QString::fromUtf8(html);
    free(html);
    return result;
}

void MarkdownConverter::renderToDocument(const QString &markdown, QTextDocument *doc)
{
    doc->clear();
    QString html = toHtml(markdown);
    doc->setHtml(html);
}

QString MarkdownConverter::toHtml(const QString &markdown)
{
    return markdownToHtml(markdown);
}

QString MarkdownConverter::documentToMarkdown(QTextDocument *doc)
{
    return doc->toMarkdown().trimmed();
}
