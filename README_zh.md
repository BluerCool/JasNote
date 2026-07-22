# JasNote

基于 Qt 6 构建的所见即所得 Markdown 编辑器。

轻松阅读和编辑 Markdown。

## 依赖要求

- Qt 6.5+
- CMake 3.21+
- C++17 编译器（GCC、Clang 或 MSVC）
- cmark-gfm（克隆到项目根目录）

## 构建

### 1. 克隆依赖

```bash
git clone https://github.com/BluerCool/JasNote.git
cd JasNote
git clone https://github.com/github/cmark-gfm.git
```

### 2. 编译

#### Linux

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/path/to/qt/6.x.x/<compiler>"
cmake --build . -j$(nproc)
```

直接运行：

```bash
./jasnote
```

#### Windows（MinGW）

```bat
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="<path-to-qt>/mingw_64"
cmake --build . -j
<path-to-qt>/mingw_64/bin/windeployqt.exe build\jasnote.exe
```

#### Windows（MSVC）

```bat
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="<path-to-qt>/msvc2022_64"
cmake --build . --config Release
<path-to-qt>/msvc2022_64/bin/windeployqt.exe build\jasnote.exe
```

#### macOS

macOS 未经过测试，可自行尝试编译，流程与 Linux 基本一致：

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/path/to/qt/6.x.x/<compiler>"
cmake --build . -j$(sysctl -n hw.ncpu)
```

## 配置

编辑 `config.json` 覆盖默认值，只写需要修改的字段即可。

配置加载顺序：

1. `~/.config/jasnote/config.json`（全局）
2. `./config.json`（本地）

## 许可证

MIT
