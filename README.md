<div align="center">

# JasNote

### A Markdown editor and reader so transparent, it has trust issues.

**WYSIWYG Markdown editing — no split pane, no preview pane, no nonsense.**

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Qt 6.5+](https://img.shields.io/badge/Qt-6.5+-green.svg)](https://www.qt.io/)
[![C++17](https://img.shields.io/badge/C++-17-purple.svg)](https://isocpp.org/)

</div>

---

## What is this sorcery?

JasNote is a lightweight WYSIWYG Markdown note editor built with Qt 6. You type Markdown, and it renders inline — live, as you type. No split pane. No "Source" tab. No toggling between raw text and preview like some kind of animal.

It also looks **really** good doing it. The window is a translucent glassmorphism frame — you can literally see your desktop through it. Is it a productivity tool or a privacy risk? Yes.

## Features

| Feature | What it does |
|---------|-------------|
| **Live WYSIWYG Editing** | Type `# Heading` and boom — it's a heading. Type `**bold**` and it's bold. Everything renders inline, no preview needed. |
| **Full CommonMark + GFM** | Powered by [cmark-gfm](https://github.com/github/cmark-gfm) (the reference CommonMark implementation). Tables, strikethrough, task lists, autolinks — all supported. |
| **Image Paste (Ctrl+V)** | Paste images from your clipboard. They're saved to `pastes/` and displayed inline. Screenshot warriors, this is your moment. |
| **Drag & Drop Images** | Drag image files straight into the editor. It just works. Like it should. |
| **Glassmorphism Window** | The window is translucent with rounded corners. You can see your desktop behind it. Spooky? A little. Cool? Absolutely. |
| **Auto-Save** | Saves to `markdowns/note.md` automatically. Because losing notes is a crime. |
| **Manual Save (Ctrl+S)** | For the control freaks. We respect that. |
| **Tab = 4 Spaces** | Tab inserts 4 spaces. Not a tab character. This is the hill we chose to die on. |
| **Glass Exit Dialog** | When you try to close with unsaved changes, a frosted glass dialog appears asking "Save? Don't Save? Cancel?" Very fancy. |
| **Custom Chrome (All Platforms)** | Every platform gets rounded corners and a custom title bar (minimize/maximize/close). You get the full glassmorphism experience everywhere. |
| **Fully Configurable** | Every pixel, every color, every font, every margin — configurable via `config.json`. You have been given too much power. |

## The "No Split Pane" Philosophy

Most Markdown editors give you two panes: one with raw text, one with rendered output. JasNote said "what if we just... didn't?" You type Markdown. It renders. Right there. In the same spot. Like magic, but with fewer hat tricks and more `QTextEdit` subclassing. Under the hood, [cmark-gfm](https://github.com/github/cmark-gfm) parses Markdown into an AST, and a custom converter maps it to `QTextDocument` rich text — full CommonMark + GFM support without a split pane.

## Requirements

- **Qt 6.5+**
- **CMake 3.21+**
- **C++17 compiler** (GCC, Clang, MSVC — we don't judge)
- cmark-gfm is fetched automatically via CMake FetchContent (no manual install needed)

## Build from Source

```bash
git clone https://github.com/BluerCool/JasNote.git
cd JasNote
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
```

## Run

```bash
./jasnote
```

If the window appears and you can see your desktop wallpaper through it, congratulations — everything is working exactly as intended.

## Usage

| Shortcut | Action |
|----------|--------|
| Type Markdown | Renders inline in real-time (WYSIWYG) |
| `Ctrl+V` | Paste image from clipboard |
| `Ctrl+S` | Save note to `markdowns/note.md` |
| `Tab` | Insert 4 spaces |
| Drag & Drop | Drop image files into the editor |
| Close window | Triggers glass "Save?" dialog (if modified) |

**File locations** (relative to the executable):

| Path | Contents |
|------|----------|
| `markdowns/note.md` | Your saved note |
| `pastes/` | Images pasted via `Ctrl+V` |
| `config.json` | Runtime configuration (optional) |

## Project Structure

```
JasNote/
├── CMakeLists.txt              # Build configuration
├── config.json                 # Runtime config (optional)
├── resources.qrc               # Qt resources
├── src/
│   ├── main.cpp                # Entry point — where it all begins
│   ├── mainwindow.cpp/h        # Frameless window with glassmorphism painting
│   ├── markdowneditor.cpp/h    # WYSIWYG Markdown editor (QTextEdit subclass)
│   ├── markdownconverter.cpp/h # cmark-gfm AST → QTextDocument renderer
│   ├── glassdialog.cpp/h       # Frosted glass "Save?" confirmation dialog
│   ├── titlebar.cpp/h          # Custom title bar (all platforms)
│   ├── config.cpp              # JSON config loader
│   ├── settings.h              # All UI defaults live here (S namespace)
│   └── fluentui/               # FluentUI glassmorphism styling
├── tests/
│   └── test_mainwindow.cpp     # Unit tests (yes, we have those)
└── README.md                   # You're looking at it
```

## Configuration

JasNote is configured via `config.json`. Only specify the values you want to override — everything else keeps its default. The config is loaded on startup from:

1. `~/.config/jasnote/config.json` (recommended — system-wide)
2. `./config.json` (local — development)

### `window` — Main Window

| Key | Type | Default | Description |
|-----|------|---------|-------------|
| `minWidth` | int | `900` | Minimum window width |
| `minHeight` | int | `600` | Minimum window height |
| `defaultWidth` | int | `1100` | Default window width |
| `defaultHeight` | int | `750` | Default window height |
| `opacity` | double | `0.25` | Background opacity (0–1, lower = more see-through) |
| `radius` | int | `16` | Window corner radius (px) |
| `layoutMargin` | int | `16` | Content area padding (px) |
| `borderWidth` | int | `2` | Window border width (px) |
| `borderAlphaBase` | int | `153` | Border base opacity |
| `bg1` | [R,G,B] | `[18,22,30]` | Gradient start color (top-left) |
| `bg2` | [R,G,B] | `[22,28,38]` | Gradient mid color |
| `bg3` | [R,G,B] | `[16,20,28]` | Gradient end color (bottom-right) |

### `statusBar` — Status Label (Bottom-Left)

| Key | Type | Default | Description |
|-----|------|---------|-------------|
| `fontSize` | int | `15` | Font size (px) |
| `font` | string | `"Cascadia Code, Fira Code, monospace"` | Font family |
| `color` | string | `"black"` | Text color |
| `modifiedColor` | string | `"#ff6b9d"` | Unsaved indicator color (pink) |
| `modifiedFontSize` | int | `18` | Unsaved indicator size (px) |
| `x` | int | `20` | Left margin (px) |
| `yOffset` | int | `36` | Distance from window bottom (px) |
| `width` | int | `500` | Label width (px) |
| `height` | int | `20` | Label height (px) |
| `marginLeft` | int | `4` | Text left padding (px) |

### `editor` — Markdown Editor

| Key | Type | Default | Description |
|-----|------|---------|-------------|
| `fontSize` | int | `14` | Font size (px) |
| `font` | string | `"Cascadia Code, Fira Code, JetBrains Mono, monospace"` | Font family |
| `textColor` | string | `"#d4d4dc"` | Text color |
| `selectionBg` | string | `"#2a6f6f"` | Selection background color |
| `padding` | int | `16` | Editor padding (px) |
| `tabStop` | int | `40` | Tab width (px) |
| `autosaveMs` | int | `0` | Auto-save debounce (ms, 0 = disabled) |

### `dialog` — Glass Exit Dialog

| Key | Type | Default | Description |
|-----|------|---------|-------------|
| `width` | int | `440` | Dialog width (px) |
| `height` | int | `180` | Dialog height (px) |
| `bgAlpha` | int | `242` | Background opacity (0–255) |
| `radius` | int | `16` | Corner radius (px) |
| `borderAlpha` | int | `160` | Border opacity (0–255) |
| `borderWidth` | int | `2` | Border width (px) |
| `marginLeft` | int | `28` | Left padding (px) |
| `marginTop` | int | `24` | Top padding (px) |
| `marginRight` | int | `28` | Right padding (px) |
| `marginBottom` | int | `20` | Bottom padding (px) |
| `titleColor` | string | `"#d4d4dc"` | Title text color |
| `titleFontSize` | int | `15` | Title font size (px) |

### `dialogButtons` — Dialog Buttons (Cancel / Don't Save / Save)

| Key | Type | Default | Description |
|-----|------|---------|-------------|
| `width` | int | `110` | Button width (px) |
| `height` | int | `34` | Button height (px) |
| `radius` | int | `8` | Button corner radius (px) |
| `fontSize` | int | `13` | Button font size (px) |
| `textColor` | string | `"#d4d4dc"` | Button text color |
| `cancelBg` | string | `"rgba(255,255,255,0.06)"` | Cancel background |
| `cancelHover` | string | `"rgba(255,255,255,0.12)"` | Cancel hover |
| `dontSaveBg` | string | `"rgba(200,60,60,0.35)"` | Don't Save background (red) |
| `dontSaveHover` | string | `"rgba(200,60,60,0.55)"` | Don't Save hover |
| `saveBg` | string | `"rgba(78,201,176,0.3)"` | Save background (teal) |
| `saveHover` | string | `"rgba(78,201,176,0.5)"` | Save hover |

### `titleBar` — Custom Title Bar

| Key | Type | Default | Description |
|-----|------|---------|-------------|
| `height` | int | `36` | Title bar height (px) |
| `title` | string | `"JasNote"` | Title text |
| `font` | string | `"Cascadia Code, Fira Code, monospace"` | Font family |
| `fontSize` | int | `13` | Font size (px) |
| `color` | string | `"rgba(255,255,255,0.7)"` | Title text color |
| `buttonSize` | int | `36` | Button size (px) |
| `buttonFontSize` | int | `14` | Button icon size (px) |
| `buttonColor` | string | `"rgba(255,255,255,0.6)"` | Button color |
| `buttonHover` | string | `"rgba(255,255,255,0.1)"` | Minimize/Maximize hover |
| `closeButtonHover` | string | `"rgba(220,50,50,0.8)"` | Close button hover (red) |

### Example `config.json`

```json
{
  "window": {
    "opacity": 0.4,
    "radius": 20,
    "bg1": [30, 40, 60]
  },
  "editor": {
    "fontSize": 16,
    "font": "JetBrains Mono",
    "textColor": "#e0e0e0"
  }
}
```

## Platform Behavior

All platforms get rounded corners and a custom title bar (minimize/maximize/close). Full glassmorphism everywhere.

## Why JasNote?

It can render your Markdown beautifully while you see your desktop wallpaper staring back at you through the translucent glass.

## License

**MIT** — do whatever you want with it, just don't blame us when you spend 20 minutes staring at your window transparency instead of writing notes.
