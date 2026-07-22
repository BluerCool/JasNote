# JasNote

A WYSIWYG Markdown editor built with Qt 6.

## Requirements

- Qt 6.5+
- CMake 3.21+
- C++17 compiler (GCC, Clang, or MSVC)
- cmark-gfm and litehtml (clone into project root)

## Build

### 1. Clone dependencies

```bash
git clone https://github.com/BluerCool/JasNote.git
cd JasNote
git clone https://github.com/github/cmark-gfm.git
git clone https://github.com/litehtml/litehtml.git
```

### 2. Compile

#### Linux

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

Run directly:

```bash
./jasnote
```

#### Windows (MinGW)

```bat
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . -j%NUMBER_OF_PROCESSORS%
```

#### Windows (MSVC)

```bat
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

#### Windows — Bundle DLLs

Windows 下编译完成后需要将 Qt DLL 打包到 exe 旁边，否则双击无法运行：

```bat
F:\Qt\6.10.2\mingw_64\bin\windeployqt.exe build\jasnote.exe
```

路径根据实际 Qt 安装位置调整。执行后 `build\` 目录下会包含所有运行所需的 DLL，直接双击 `jasnote.exe` 即可运行。

#### macOS

macOS 未经过测试，请自行尝试编译，流程与 Linux 基本一致：

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(sysctl -n hw.ncpu)
```

### Specifying Qt path

如果 CMake 找不到 Qt，手动指定路径：

```bash
cmake .. -DCMAKE_PREFIX_PATH="/path/to/qt/6.x.x/<compiler>"
```

例如：

```bash
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.10.2/mingw_64"
```

## Configuration

编辑 `config.json` 覆盖默认值，只写需要修改的字段即可。

配置加载顺序：

1. `~/.config/jasnote/config.json`（全局）
2. `./config.json`（本地）

## License

MIT
