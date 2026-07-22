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
- **C++17 编译器**
- cmark-gfm 通过 CMake FetchContent 自动下载（无需手动安装）

## 从源码构建

```bash
git clone https://github.com/BluerCool/JasNote.git
cd JasNote
mkdir build
cd build
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

## 开源协议

[MIT](LICENSE) 