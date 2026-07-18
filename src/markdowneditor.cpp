#include "markdowneditor.h"
#include "markdownconverter.h"
#include "settings.h"
#include <QKeyEvent>
#include <QMimeData>
#include <QImage>
#include <QImageReader>
#include <QUrl>
#include <QDir>
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QGuiApplication>
#include <QClipboard>
#include <QTextCursor>
#include <QTextDocument>
#include <QTextImageFormat>
#include <QTextBlock>
#include <QAbstractTextDocumentLayout>
#include <QScrollBar>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

MarkdownEditor::MarkdownEditor(const QString &filePath, QWidget *parent)
    : QTextEdit(parent)
{
    setObjectName("markdownEditor");
    setLineWrapMode(QTextEdit::WidgetWidth);
    setTabStopDistance(S::ED_TAB_STOP);
    setAcceptRichText(true);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFont font(S::ED_FONT, S::ED_FONT_SIZE);
    setFont(font);

    setStyleSheet(
        QString(
            "QTextEdit {"
            "  background-color: transparent;"
            "  color: %1;"
            "  border: none;"
            "  padding: %2px;"
            "  selection-background-color: %3;"
            "  selection-color: white;"
            "}"
            "QScrollBar { width: 0px; height: 0px; }"
        ).arg(S::ED_COLOR).arg(S::ED_PADDING).arg(S::ED_SEL_BG)
    );

    document()->setDefaultStyleSheet(R"(
        body { color: #d4d4dc; }
        h1 { font-size: 26px; color: #e8e8ec; font-weight: bold; margin-top: 18px; margin-bottom: 10px; }
        h2 { font-size: 21px; color: #e0e0e6; font-weight: bold; margin-top: 16px; margin-bottom: 8px; }
        h3 { font-size: 17px; color: #d8d8de; font-weight: bold; margin-top: 14px; margin-bottom: 6px; }
        h4 { font-size: 15px; color: #d4d4dc; font-weight: bold; margin-top: 12px; margin-bottom: 4px; }
        h5, h6 { font-size: 14px; color: #c0c0c8; font-weight: bold; margin-top: 10px; margin-bottom: 4px; }
        code { font-family: 'Cascadia Code', 'Fira Code', monospace; background: rgba(255,255,255,0.08); padding: 2px 5px; border-radius: 4px; font-size: 13px; }
        pre { background: rgba(255,255,255,0.06); padding: 14px; border-radius: 8px; margin: 10px 0; }
        pre code { background: transparent; padding: 0; font-size: 13px; }
        a { color: #4ec9b0; text-decoration: none; }
        a:hover { text-decoration: underline; }
        blockquote { border-left: 3px solid #4ec9b0; padding-left: 14px; color: rgba(212,212,220,0.6); margin: 8px 0; }
        hr { border: none; border-top: 1px solid rgba(255,255,255,0.12); margin: 18px 0; }
        table { border-collapse: collapse; margin: 10px 0; }
        th { background: rgba(255,255,255,0.08); font-weight: bold; }
        th, td { border: 1px solid rgba(255,255,255,0.15); padding: 7px 14px; }
        ul, ol { margin: 4px 0; }
        li { margin: 3px 0; }
        img { max-width: 100%; border-radius: 6px; }
    )");

    m_pasteDir = QDir::currentPath() + "/pastes";
    QDir().mkpath(m_pasteDir);

    if (filePath.isEmpty()) {
        m_filePath = QDir::currentPath() + "/markdowns/note.md";
    } else {
        m_filePath = QFileInfo(filePath).absoluteFilePath();
    }

    m_saveTimer = new QTimer(this);
    m_saveTimer->setSingleShot(true);
    m_saveTimer->setInterval(S::ED_AUTOSAVE_MS);
    if (S::ED_AUTOSAVE_MS > 0)
        connect(m_saveTimer, &QTimer::timeout, this, &MarkdownEditor::autoSave);

    m_netManager = new QNetworkAccessManager(this);

    QFile file(m_filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString content = QString::fromUtf8(file.readAll());
        file.close();
        setMarkdown(content);
    } else {
        setMarkdown("# Welcome to JasNote\n\nPaste images with Ctrl+V or drag & drop files.");
    }

    connect(this, &QTextEdit::textChanged, this, [this]() {
        if (!m_loading) {
            if (!m_modified) {
                m_modified = true;
                emit modificationChanged(true);
            }
            emit textChanged(toMarkdown());
            if (S::ED_AUTOSAVE_MS > 0)
                m_saveTimer->start();
        }
    });
}

QString MarkdownEditor::toMarkdown() const
{
    return MarkdownConverter::documentToMarkdown(document());
}

void MarkdownEditor::setMarkdown(const QString &md)
{
    m_loading = true;
    m_rawMarkdown = md;
    MarkdownConverter::renderToDocument(md, document());
    m_loading = false;
    fetchRemoteImages();
}

void MarkdownEditor::save()
{
    QDir().mkpath(QFileInfo(m_filePath).absolutePath());
    QFile file(m_filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QString md = MarkdownConverter::documentToMarkdown(document());
        while (md.endsWith('\n')) md.chop(1);
        file.write(md.toUtf8());
        file.close();
    }
    if (m_modified) {
        m_modified = false;
        emit modificationChanged(false);
    }
}

void MarkdownEditor::autoSave()
{
    save();
}

QString MarkdownEditor::filePath() const
{
    return m_filePath;
}

QString MarkdownEditor::fileName() const
{
    return QFileInfo(m_filePath).fileName();
}

bool MarkdownEditor::handlePaste()
{
    const QMimeData *mimeData = QGuiApplication::clipboard()->mimeData();
    if (!mimeData)
        return false;

    if (mimeData->hasImage()) {
        insertFromMimeData(mimeData);
        return true;
    }

    return false;
}

void MarkdownEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab) {
        insertPlainText("    ");
        return;
    }

    if (event->key() == Qt::Key_S && (event->modifiers() & Qt::ControlModifier)) {
        save();
        return;
    }

    QTextEdit::keyPressEvent(event);
}

void MarkdownEditor::insertFromMimeData(const QMimeData *source)
{
    QImage image;

    if (source->hasImage()) {
        image = qvariant_cast<QImage>(source->imageData());
    } else if (source->hasUrls()) {
        const QList<QUrl> urls = source->urls();
        for (const QUrl &url : urls) {
            if (!url.isLocalFile()) continue;
            QString localPath = url.toLocalFile();
            QImageReader reader(localPath);
            if (reader.canRead()) {
                image = reader.read();
                if (!image.isNull()) break;
            }
        }
    }

    if (!image.isNull()) {
        QString fileName = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss_zzz") + ".png";
        QString filePath = m_pasteDir + "/" + fileName;
        if (image.save(filePath)) {
            QTextCursor cursor = textCursor();
            cursor.beginEditBlock();
            cursor.insertBlock();

            QTextImageFormat imageFormat;
            imageFormat.setName(filePath);
            int maxWidth = viewport()->width() - 48;
            if (image.width() > maxWidth) {
                imageFormat.setWidth(maxWidth);
                imageFormat.setHeight(image.height() * maxWidth / image.width());
            } else {
                imageFormat.setWidth(image.width());
                imageFormat.setHeight(image.height());
            }
            document()->addResource(QTextDocument::ImageResource, QUrl::fromLocalFile(filePath), image);
            cursor.insertImage(imageFormat);

            cursor.insertBlock();
            cursor.endEditBlock();
        }
        return;
    }

    QTextEdit::insertFromMimeData(source);
}

void MarkdownEditor::fetchRemoteImages()
{
    QTextBlock block = document()->begin();
    while (block.isValid()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextFragment frag = it.fragment();
            if (!frag.isValid()) continue;
            QTextImageFormat imgFmt = frag.charFormat().toImageFormat();
            if (!imgFmt.isValid()) continue;

            QString name = imgFmt.name();
            QUrl url(name);
            if (!url.scheme().startsWith("http")) continue;

            QVariant res = document()->resource(QTextDocument::ImageResource, url);
            if (res.isValid() && res.typeId() == QMetaType::QImage && !res.value<QImage>().isNull())
                continue;

            QNetworkReply *reply = m_netManager->get(QNetworkRequest(url));
            connect(reply, &QNetworkReply::finished, this, [this, url, reply]() {
                reply->deleteLater();
                if (reply->error() != QNetworkReply::NoError) return;
                QImage img;
                img.loadFromData(reply->readAll());
                if (img.isNull()) return;
                document()->addResource(QTextDocument::ImageResource, url, img);
                QTextCursor cursor(document());
                cursor.beginEditBlock();
                QTextBlock blk = document()->begin();
                while (blk.isValid()) {
                    for (QTextBlock::iterator it = blk.begin(); !it.atEnd(); ++it) {
                        QTextFragment frag = it.fragment();
                        if (!frag.isValid()) continue;
                        QTextImageFormat fmt = frag.charFormat().toImageFormat();
                        if (fmt.isValid() && fmt.name() == url.toString()) {
                            cursor.setPosition(frag.position());
                            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                            QTextImageFormat newFmt = fmt;
                            cursor.removeSelectedText();
                            cursor.insertImage(newFmt);
                        }
                    }
                    blk = blk.next();
                }
                cursor.endEditBlock();
            });
        }
        block = block.next();
    }
}
