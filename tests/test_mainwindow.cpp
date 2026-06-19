#include <QtTest>
#include <QApplication>
#include <QMainWindow>
#include "../src/mainwindow.h"
#include "../src/markdowneditor.h"

class TestJasNote : public QObject
{
    Q_OBJECT

private slots:
    void testMarkdownEditorStartsWithContent();
    void testSetAndGetMarkdown();
    void testMarkdownStringManipulation();
    void testMainWindowHasEditor();
    void testWindowIsTranslucent();
};

void TestJasNote::testMarkdownEditorStartsWithContent()
{
    MarkdownEditor editor;
    QVERIFY(!editor.toMarkdown().isEmpty());
}

void TestJasNote::testSetAndGetMarkdown()
{
    MarkdownEditor editor;
    editor.setMarkdown("Hello **world**");
    QCOMPARE(editor.toMarkdown(), QString("Hello **world**"));
}

void TestJasNote::testMarkdownStringManipulation()
{
    MarkdownEditor editor;
    editor.setMarkdown("# Title\n\nParagraph with *italic* and **bold**.");
    QString md = editor.toMarkdown();
    QVERIFY(md.contains("Title"));
    QVERIFY(md.contains("Paragraph"));
    QVERIFY(md.contains("italic"));
    QVERIFY(md.contains("bold"));
}

void TestJasNote::testMainWindowHasEditor()
{
    MainWindow w;
    auto *editor = w.findChild<MarkdownEditor *>();
    QVERIFY(editor != nullptr);
    QVERIFY(!editor->toMarkdown().isEmpty());
}

void TestJasNote::testWindowIsTranslucent()
{
    MainWindow w;
    QVERIFY(w.testAttribute(Qt::WA_TranslucentBackground));
}

QTEST_MAIN(TestJasNote)
#include "test_mainwindow.moc"
