# JasNote UI Settings

所有 UI 参数集中在 `src/settings.h` 的 `S` 命名空间中。修改后重新编译即可生效。

---

## 平台行为

| 环境 | 圆角 | 标题栏按钮 | 检测方式 |
|------|------|-----------|---------|
| Windows | 有 | 有 (最小化/最大化/关闭) | `QSysInfo::productType() == "windows"` |
| 平铺 WM (niri/sway/i3/Hyprland) | 无 | 无 | 环境变量 `NIRI_SOCKET` / `SWAYSOCK` / `I3SOCK` / `HYPRLAND_INSTANCE_SIGNATURE` |
| 其他 Linux (GNOME/KDE 等) | 无 | 无 | 默认 |

逻辑：只有 Windows 启用自定义 chrome（圆角+标题栏），平铺 WM 因桌面已提供圆角所以保持直角，其他环境同理。

---

## Window（主窗口）

| 参数 | 值 | 说明 |
|------|-----|------|
| `S::WIN_MIN_W` | `900` | 窗口最小宽度 |
| `S::WIN_MIN_H` | `600` | 窗口最小高度 |
| `S::WIN_DEFAULT_W` | `1100` | 窗口默认宽度 |
| `S::WIN_DEFAULT_H` | `750` | 窗口默认高度 |
| `S::WIN_OPACITY` | `0.25` | 背景绘制透明度（0~1，越小越透） |
| `S::WIN_RADIUS` | `16` | 窗口圆角半径 (px)，仅 Windows 生效 |
| `S::WIN_LAYOUT_MARGIN` | `16` | 内容区边距 (px) |
| `S::WIN_BORDER_WIDTH` | `2` | 窗口边框宽度 (px) |
| `S::WIN_BORDER_ALPHA_BASE` | `153` | 边框基础透明度 |

### 背景渐变色 (RGB)

| 参数 | 值 | 说明 |
|------|-----|------|
| `S::BG1_R/G/B` | `18, 22, 30` | 渐变起点 (左上) |
| `S::BG2_R/G/B` | `22, 28, 38` | 渐变中点 |
| `S::BG3_R/G/B` | `16, 20, 28` | 渐变终点 (右下) |

---

## Status Bar（左下角路径标签）

| 参数 | 值 | 说明 |
|------|-----|------|
| `S::STATUS_FONT_SIZE` | `15` | 字号 (px) |
| `S::STATUS_FONT` | `"Cascadia Code, Fira Code, monospace"` | 字体 |
| `S::STATUS_COLOR` | `"black"` | 文字颜色 |
| `S::STATUS_MODIFIED` | `"#ff6b9d"` | 未保存星号颜色 (粉色) |
| `S::STATUS_MODIFIED_SIZE` | `18` | 星号字号 (px) |
| `S::STATUS_X` | `20` | 左边距 (px) |
| `S::STATUS_Y_OFFSET` | `36` | 距窗口底部偏移 (px) |
| `S::STATUS_W` | `500` | 标签宽度 (px) |
| `S::STATUS_H` | `20` | 标签高度 (px) |
| `S::STATUS_MARGIN_LEFT` | `4` | 文字左边距 (px) |

---

## Editor（编辑器）

| 参数 | 值 | 说明 |
|------|-----|------|
| `S::ED_FONT_SIZE` | `14` | 编辑器字号 (px) |
| `S::ED_FONT` | `"Cascadia Code, Fira Code, JetBrains Mono, monospace"` | 编辑器字体 |
| `S::ED_COLOR` | `"#d4d4dc"` | 文字颜色 (浅灰) |
| `S::ED_SEL_BG` | `"#2a6f6f"` | 选中背景色 (青) |
| `S::ED_PADDING` | `16` | 内边距 (px) |
| `S::ED_TAB_STOP` | `40` | Tab 宽度 (px) |
| `S::ED_AUTOSAVE_MS` | `800` | 自动保存延迟 (ms) |

---

## Glass Dialog（退出确认毛玻璃对话框）

| 参数 | 值 | 说明 |
|------|-----|------|
| `S::DLG_W` | `440` | 对话框宽度 (px) |
| `S::DLG_H` | `180` | 对话框高度 (px) |
| `S::DLG_BG_ALPHA` | `242` | 背景透明度 (0~255) |
| `S::DLG_RADIUS` | `16` | 圆角半径 (px) |
| `S::DLG_BORDER_ALPHA` | `160` | 边框透明度 (0~255) |
| `S::DLG_BORDER_W` | `2` | 边框宽度 (px) |
| `S::DLG_ML/MT/MR/MB` | `28, 24, 28, 20` | 内边距 (左上右下) |
| `S::DLG_TITLE_COLOR` | `"#d4d4dc"` | 标题颜色 |
| `S::DLG_TITLE_SIZE` | `15` | 标题字号 (px) |

---

## Dialog Buttons（对话框按钮）

| 参数 | 值 | 说明 |
|------|-----|------|
| `S::BTN_W` | `110` | 按钮宽度 (px) |
| `S::BTN_H` | `34` | 按钮高度 (px) |
| `S::BTN_RADIUS` | `8` | 按钮圆角 (px) |
| `S::BTN_FONT_SIZE` | `13` | 按钮字号 (px) |
| `S::BTN_COLOR` | `"#d4d4dc"` | 按钮文字颜色 |
| `S::BTN_CANCEL_BG` | `"rgba(255,255,255,0.06)"` | Cancel 背景 |
| `S::BTN_CANCEL_HOVER` | `"rgba(255,255,255,0.12)"` | Cancel 悬停 |
| `S::BTN_DONTSAVE_BG` | `"rgba(200,60,60,0.35)"` | Don't Save 背景 (红) |
| `S::BTN_DONTSAVE_HOVER` | `"rgba(200,60,60,0.55)"` | Don't Save 悬停 |
| `S::BTN_SAVE_BG` | `"rgba(78,201,176,0.3)"` | Save 背景 (青) |
| `S::BTN_SAVE_HOVER` | `"rgba(78,201,176,0.5)"` | Save 悬停 |

---

## Title Bar（Windows 标题栏）

| 参数 | 值 | 说明 |
|------|-----|------|
| `S::TB_HEIGHT` | `36` | 标题栏高度 (px) |
| `S::TB_TITLE` | `"JasNote"` | 标题文字 |
| `S::TB_FONT` | `"Cascadia Code, Fira Code, monospace"` | 字体 |
| `S::TB_FONT_SIZE` | `13` | 字号 (px) |
| `S::TB_COLOR` | `"rgba(255,255,255,0.7)"` | 标题颜色 |
| `S::TB_BTN_SIZE` | `36` | 按钮尺寸 (px) |
| `S::TB_BTN_FONT` | `14` | 按钮图标字号 (px) |
| `S::TB_BTN_COLOR` | `"rgba(255,255,255,0.6)"` | 按钮颜色 |
| `S::TB_BTN_HOVER` | `"rgba(255,255,255,0.1)"` | 最小化/最大化悬停色 |
| `S::TB_BTN_CLOSE_HOVER` | `"rgba(220,50,50,0.8)"` | 关闭按钮悬停色 (红) |

---

## 使用方式

所有 UI 参数集中在 `src/settings.h` 的 `S` 命名空间中，以 `inline` 变量定义，支持两种调整方式：

### 方式一：运行时配置（无需重新编译）

编辑 `config.json`（项目根目录），只写需要覆盖的字段，未出现的字段保持默认值：

```bash
# 将配置放到系统配置目录（推荐）
cp config.json ~/.config/jasnote/config.json

# 或者放在当前运行目录（开发用）
# 直接放在 build/ 目录下即可
```

启动时自动加载：优先读取 `~/.config/jasnote/config.json`，其次 `./config.json`。

### 方式二：编译期默认值

修改 `src/settings.h` 中的初始值，重新编译：

```bash
cd build && ninja
```
