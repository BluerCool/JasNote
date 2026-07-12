import QtQuick 6.0
import QtQuick.Controls 6.0
import QtQuick.Layouts 6.0
import QtQuick.Controls.Basic 6.0
import FluentUI 1.0

Rectangle {
    id: root
    color: "transparent"

    property string internalMarkdown: "# Welcome to JasNote\n\nPaste images with Ctrl+V or drag & drop files."

    function toMarkdown() {
        return root.internalMarkdown
    }

    function setMarkdown(md) {
        editor.text = md
    }

    function insertAtCursor(text) {
        var pos = editor.cursorPosition
        var before = editor.text.substring(0, pos)
        var after = editor.text.substring(pos)
        editor.text = before + text + after
        editor.cursorPosition = pos + text.length
    }

    FluAppBar {
        id: appBar
        title: "JasNote"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        z: 2
        textColor: "black"
    }

    Item {
        anchors.top: appBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 8

        ScrollView {
            id: scroll
            anchors.fill: parent
            clip: true

            Text {
                id: preview
                width: scroll.width
                textFormat: Text.MarkdownText
                text: editor.text
                wrapMode: Text.WordWrap
                font.pixelSize: 14
                font.family: "Segoe UI, Noto Sans, sans-serif"
                color: "#d4d4dc"
                leftPadding: 16
                topPadding: 16
                rightPadding: 16
                bottomPadding: 16
                onLinkActivated: function(link) {
                    Qt.openUrlExternally(link)
                }
            }
        }

        TextArea {
            id: editor
            anchors.fill: parent
            font.pixelSize: 14
            font.family: "Cascadia Code, Fira Code, JetBrains Mono, monospace"
            color: "transparent"
            placeholderText: "Start writing markdown..."
            textFormat: TextEdit.PlainText
            wrapMode: TextArea.WordWrap
            readOnly: false
            background: null
            leftPadding: 16
            topPadding: 16
            rightPadding: 16
            bottomPadding: 16
            selectByMouse: true
            selectionColor: "#2a6f6f"
            selectedTextColor: "white"
            renderType: Text.NativeRendering

            Keys.onPressed: function(event) {
                if (event.key === Qt.Key_V && (event.modifiers & Qt.ControlModifier)) {
                    if (markdownEditor.handlePaste()) {
                        event.accepted = true
                    }
                }
            }

            Component.onCompleted: {
                editor.text = root.internalMarkdown
            }

            onTextChanged: {
                var raw = editor.text
                while (raw.endsWith("\n"))
                    raw = raw.substring(0, raw.length - 1)
                root.internalMarkdown = raw
            }
        }

        DropArea {
            anchors.fill: parent
            onDropped: function(drop) {
                if (drop.hasUrls) {
                    var urls = drop.urls
                    for (var i = 0; i < urls.length; i++) {
                        var url = urls[i]
                        var path = url.toString()
                        if (path.startsWith("file://")) {
                            path = path.substring(7)
                        }
                        var dot = path.lastIndexOf(".")
                        var ext = dot >= 0 ? path.substring(dot).toLowerCase() : ""
                        var imageExts = [".png", ".jpg", ".jpeg", ".gif", ".bmp", ".svg", ".webp"]
                        var videoExts = [".mp4", ".webm", ".avi", ".mov", ".mkv"]
                        if (imageExts.indexOf(ext) >= 0) {
                            root.insertAtCursor("\n![](" + path + ")\n")
                        } else if (videoExts.indexOf(ext) >= 0) {
                            root.insertAtCursor("\n<video src=\"" + path + "\" controls></video>\n")
                        } else {
                            root.insertAtCursor("\n[" + path + "](" + path + ")\n")
                        }
                    }
                    drop.acceptProposedAction()
                }
            }
        }
    }
}
