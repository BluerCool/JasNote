<div align="center">

# ✨ JasNote ✨

### *一款 Markdown 编辑器和阅读器。*

**所见即所得的 Markdown 编辑 —— 没有分屏，没有预览面板，没有废话。**

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Qt 6.5+](https://img.shields.io/badge/Qt-6.5+-green.svg)](https://www.qt.io/)
[![C++17](https://img.shields.io/badge/C++-17-purple.svg)](https://isocpp.org/)

</div>

---

## 这是什么黑魔法？

JasNote 是一款基于 Qt 6 的轻量级 WYSIWYG Markdown 笔记编辑器。你输入 Markdown，它实时在原地渲染 —— **所见即所得，打字即渲染**。没有分屏。没有"源码"标签页。不需要在原始文本和预览之间来回切换，像原始人一样。

而且它做这一切的时候还 **非常好看**。窗口是 **半透明毛玻璃** 风格 —— 你真的能透过它看到桌面。到底是生产力工具还是隐私风险？是的。

## 功能一览

| 功能 | 做了什么 |
|------|---------|
| **实时 WYSIWYG 编辑** | 输入 `# 标题`，砰——它就是标题了。输入 `**加粗**`，它就加粗了。一切都在原位渲染，不需要预览。 |
| **完整 CommonMark + GFM** | 基于 [cmark-gfm](https://github.com/github/cmark-gfm)（CommonMark 参考实现）。表格、删除线、任务列表、自动链接——全部支持。 |
| **图片粘贴 (`Ctrl+V`)** | 从剪贴板粘贴图片，自动保存到 `pastes/` 文件夹并内联显示。截图狂魔们，这是你们的舞台。 |
| **拖拽图片** | 直接把图片文件拖进编辑器。就这么简单。理应如此。 |
| **毛玻璃窗口** | 窗口半透明带圆角。你能透过它看到桌面。有点诡异？有一点。酷不酷？绝对酷。 |
| **手动保存 (`Ctrl+S`)** | 给控制狂们的。我们尊重你。 |
| **Tab = 4 空格** | Tab 插入 4 个空格。不是制表符。这是我们选好的高地，死也要守住。 |
| **毛玻璃退出对话框** | 关闭有未保存修改的窗口时，弹出毛玻璃对话框问你"保存？不保存？取消？"非常高级。 |
| **自定义窗口装饰（全平台）** | 所有平台都获得圆角和自定义标题栏（最小化/最大化/关闭）。全面的毛玻璃体验。 |
| **全面可配置** | 每个像素、每个颜色、每个字体、每个边距 —— 全部通过 `config.json` 配置。你被赋予了太大的权力。 |

## "不分屏"哲学

大多数 Markdown 编辑器给你两个面板：一个原始文本，一个渲染输出。JasNote 说："如果我们……不分呢？" 你输入 Markdown。它渲染了。就在那里。在同一个地方。像魔法一样，但戏法更少，`QTextEdit` 子类化更多。底层使用 [cmark-gfm](https://github.com/github/cmark-gfm)（CommonMark 参考实现）将 Markdown 解析为 AST，再通过自定义转换器映射到 `QTextDocument` 富文本——无需分屏即可获得完整的 CommonMark + GFM 支持。

## 环境要求

- **Qt 6.5+**
- **CMake 3.21+**
- **C++17 编译器**（GCC、Clang、MSVC —— 我们不挑）
- cmark-gfm 通过 CMake FetchContent 自动下载（无需手动安装）

## 从源码构建

```bash
git clone https://github.com/BluerCool/JasNote.git
cd JasNote
mkdir build && cd build
cmake ..
cmake --build . -j$(nproc)
```

## 运行

```bash
./jasnote
```

如果窗口出现了，而且你能透过它看到桌面壁纸，恭喜 —— 一切都在按预期工作。

## 使用方式

| 快捷键 | 操作 |
|--------|------|
| 输入 Markdown | 实时原位渲染（WYSIWYG） |
| `Ctrl+V` | 从剪贴板粘贴图片 |
| `Ctrl+S` | 保存笔记到 `markdowns/note.md` |
| `Tab` | 插入 4 个空格 |
| 拖拽 | 拖入图片文件到编辑器 |
| 关闭窗口 | 弹出毛玻璃"保存？"对话框（如有修改） |

**文件位置**（相对于可执行文件）：

| 路径 | 内容 |
|------|------|
| `markdowns/note.md` | 你的笔记 |
| `pastes/` | 通过 `Ctrl+V` 粘贴的图片 |
| `config.json` | 运行时配置（可选） |

## 项目结构

```
JasNote/
├── CMakeLists.txt              # 构建配置
├── config.json                 # 运行时配置（可选）
├── resources.qrc               # Qt 资源文件
├── src/
│   ├── main.cpp                # 入口点 —— 一切从这里开始
│   ├── mainwindow.cpp/h        # 无边框窗口 + 毛玻璃绘制
│   ├── markdowneditor.cpp/h    # WYSIWYG Markdown 编辑器（QTextEdit 子类）
│   ├── markdownconverter.cpp/h # cmark-gfm AST → QTextDocument 渲染器
│   ├── glassdialog.cpp/h       # 毛玻璃"保存？"确认对话框
│   ├── titlebar.cpp/h          # 自定义标题栏（全平台）
│   ├── config.cpp              # JSON 配置加载器
│   ├── settings.h              # 所有 UI 默认值（S 命名空间）
│   └── fluentui/               # FluentUI 毛玻璃样式
├── tests/
│   └── test_mainwindow.cpp     # 单元测试（是的，我们有测试）
└── README.md                   # 你正在看的这个
```

## 配置说明

JasNote 通过 `config.json` 进行配置。只写你想覆盖的值，其余保持默认。启动时按以下顺序加载配置：

1. `~/.config/jasnote/config.json`（推荐 —— 全局）
2. `./config.json`（本地 —— 开发用）

### `window` —— 主窗口

| 键 | 类型 | 默认值 | 说明 |
|----|------|--------|------|
| `minWidth` | int | `900` | 窗口最小宽度 |
| `minHeight` | int | `600` | 窗口最小高度 |
| `defaultWidth` | int | `1100` | 窗口默认宽度 |
| `defaultHeight` | int | `750` | 窗口默认高度 |
| `opacity` | double | `0.25` | 背景透明度（0–1，越小越透明） |
| `radius` | int | `16` | 窗口圆角半径（px） |
| `layoutMargin` | int | `16` | 内容区边距（px） |
| `borderWidth` | int | `2` | 窗口边框宽度（px） |
| `borderAlphaBase` | int | `153` | 边框基础透明度 |
| `bg1` | [R,G,B] | `[18,22,30]` | 渐变起始色（左上） |
| `bg2` | [R,G,B] | `[22,28,38]` | 渐变中间色 |
| `bg3` | [R,G,B] | `[16,20,28]` | 渐变结束色（右下） |

### `statusBar` —— 状态标签（左下角）

| 键 | 类型 | 默认值 | 说明 |
|----|------|--------|------|
| `fontSize` | int | `15` | 字号（px） |
| `font` | string | `"Cascadia Code, Fira Code, monospace"` | 字体 |
| `color` | string | `"black"` | 文字颜色 |
| `modifiedColor` | string | `"#ff6b9d"` | 未保存指示器颜色（粉色） |
| `modifiedFontSize` | int | `18` | 未保存指示器字号（px） |
| `x` | int | `20` | 左边距（px） |
| `yOffset` | int | `36` | 距窗口底部偏移（px） |
| `width` | int | `500` | 标签宽度（px） |
| `height` | int | `20` | 标签高度（px） |
| `marginLeft` | int | `4` | 文字左内边距（px） |

### `editor` —— Markdown 编辑器

| 键 | 类型 | 默认值 | 说明 |
|----|------|--------|------|
| `fontSize` | int | `14` | 字号（px） |
| `font` | string | `"Cascadia Code, Fira Code, JetBrains Mono, monospace"` | 字体 |
| `textColor` | string | `"#d4d4dc"` | 文字颜色 |
| `selectionBg` | string | `"#2a6f6f"` | 选中背景色 |
| `padding` | int | `16` | 编辑器内边距（px） |
| `tabStop` | int | `40` | Tab 宽度（px） |
| `autosaveMs` | int | `0` | 自动保存防抖（ms，0 = 禁用） |

### `dialog` —— 毛玻璃退出对话框

| 键 | 类型 | 默认值 | 说明 |
|----|------|--------|------|
| `width` | int | `440` | 对话框宽度（px） |
| `height` | int | `180` | 对话框高度（px） |
| `bgAlpha` | int | `242` | 背景透明度（0–255） |
| `radius` | int | `16` | 圆角半径（px） |
| `borderAlpha` | int | `160` | 边框透明度（0–255） |
| `borderWidth` | int | `2` | 边框宽度（px） |
| `marginLeft` | int | `28` | 左内边距（px） |
| `marginTop` | int | `24` | 上内边距（px） |
| `marginRight` | int | `28` | 右内边距（px） |
| `marginBottom` | int | `20` | 下内边距（px） |
| `titleColor` | string | `"#d4d4dc"` | 标题文字颜色 |
| `titleFontSize` | int | `15` | 标题字号（px） |

### `dialogButtons` —— 对话框按钮（取消 / 不保存 / 保存）

| 键 | 类型 | 默认值 | 说明 |
|----|------|--------|------|
| `width` | int | `110` | 按钮宽度（px） |
| `height` | int | `34` | 按钮高度（px） |
| `radius` | int | `8` | 按钮圆角半径（px） |
| `fontSize` | int | `13` | 按钮字号（px） |
| `textColor` | string | `"#d4d4dc"` | 按钮文字颜色 |
| `cancelBg` | string | `"rgba(255,255,255,0.06)"` | 取消按钮背景 |
| `cancelHover` | string | `"rgba(255,255,255,0.12)"` | 取消按钮悬停 |
| `dontSaveBg` | string | `"rgba(200,60,60,0.35)"` | 不保存按钮背景（红色） |
| `dontSaveHover` | string | `"rgba(200,60,60,0.55)"` | 不保存按钮悬停 |
| `saveBg` | string | `"rgba(78,201,176,0.3)"` | 保存按钮背景（青色） |
| `saveHover` | string | `"rgba(78,201,176,0.5)"` | 保存按钮悬停 |

### `titleBar` —— 自定义标题栏

| 键 | 类型 | 默认值 | 说明 |
|----|------|--------|------|
| `height` | int | `36` | 标题栏高度（px） |
| `title` | string | `"JasNote"` | 标题文字 |
| `font` | string | `"Cascadia Code, Fira Code, monospace"` | 字体 |
| `fontSize` | int | `13` | 字号（px） |
| `color` | string | `"rgba(255,255,255,0.7)"` | 标题文字颜色 |
| `buttonSize` | int | `36` | 按钮尺寸（px） |
| `buttonFontSize` | int | `14` | 按钮图标字号（px） |
| `buttonColor` | string | `"rgba(255,255,255,0.6)"` | 按钮颜色 |
| `buttonHover` | string | `"rgba(255,255,255,0.1)"` | 最小化/最大化悬停色 |
| `closeButtonHover` | string | `"rgba(220,50,50,0.8)"` | 关闭按钮悬停色（红色） |

### 配置示例 `config.json`

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

## 平台行为

所有平台都获得圆角和自定义标题栏（最小化/最大化/关闭）。全面的毛玻璃体验。

你的桌面环境已经在处理窗口装饰了，JasNote 优雅地让位。它就是这么贴心。

## 为什么叫 "JasNote"？

因为 "Jas" 和 "Note" 是两个词，我们把它们拼在一起了。没有深意。但编辑器本身有深度 —— 深到能漂亮地渲染你的 Markdown，同时让你透过半透明玻璃看到自己的桌面壁纸在盯着你看。

## 开源协议

[MIT](LICENSE) —— 随便用，只是别怪我们让你花 20 分钟盯着窗口透明度看而不是写笔记。
