# JasNote

A WYSIWYG Markdown note editor built with Qt 6. Write and edit Markdown without learning the syntax — everything is rendered inline as you type.

## Features

- **WYSIWYG Editing** — Bold, italic, headings, lists, code blocks, and more are rendered live as you type
- **Image Paste** — Paste images directly with `Ctrl+V`; they are saved automatically and displayed inline
- **Drag & Drop** — Drag image files into the editor for inline insertion
- **Auto-Save** — Content is automatically saved to `markdowns/note.md` (800ms debounce)
- **Frameless Design** — Modern translucent window with rounded corners

## Build

### Requirements

- Qt 6.5+ (Qt 6.5+ required for `QTextDocument::toMarkdown()`)
- CMake 3.21+
- C++17 compiler

### Build from source

```bash
git clone https://github.com/BluerCool/JasNote.git
cd JasNote
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
```

### Run

```bash
./jasnote
```

## Usage

| Action | Description |
|--------|-------------|
| Type Markdown | Content is rendered inline (WYSIWYG) |
| `Ctrl+V` | Paste image from clipboard |
| Drag & drop | Drop image files into the editor |
| `Tab` | Insert 4 spaces |

Saved notes are located at `markdowns/note.md` and pasted images at `pastes/` (both next to the executable).

## Project Structure

```
JasNote/
├── CMakeLists.txt
├── src/
│   ├── main.cpp            # Entry point
│   ├── mainwindow.cpp/h    # Frameless main window with custom painting
│   └── markdowneditor.cpp/h # WYSIWYG Markdown editor (QTextEdit subclass)
├── tests/
│   └── test_mainwindow.cpp # Unit tests
├── resources.qrc
└── README.md
```

## License

MIT
