# JasNote

A WYSIWYG Markdown editor built with Qt 6.

Read and edit Markdown with ease.

[中文文档](README_zh.md)

## Requirements

- Qt 6.5+
- CMake 3.21+
- C++17 compiler (GCC, Clang, or MSVC)
- cmark-gfm (clone into project root)

## Build

### 1. Clone dependencies

```bash
git clone https://github.com/BluerCool/JasNote.git
cd JasNote
git clone https://github.com/github/cmark-gfm.git
```

### 2. Compile

#### Linux

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/path/to/qt/6.x.x/<compiler>"
cmake --build . -j$(nproc)
```

Run directly:

```bash
./jasnote
```

#### Windows (MinGW)

```bat
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="<path-to-qt>/mingw_64"
cmake --build . -j
<path-to-qt>/mingw_64/bin/windeployqt.exe build\jasnote.exe
```

#### Windows (MSVC)

```bat
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="<path-to-qt>/msvc2022_64"
cmake --build . --config Release
<path-to-qt>/msvc2022_64/bin/windeployqt.exe build\jasnote.exe
```

#### macOS

macOS has not been tested. Feel free to try building it yourself — the process is essentially the same as Linux:

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="/path/to/qt/6.x.x/<compiler>"
cmake --build . -j$(sysctl -n hw.ncpu)
```

## Configuration

Edit `config.json` to override default values. Only include the fields you want to change.

Configuration load order:

1. `~/.config/jasnote/config.json` (global)
2. `./config.json` (local)

## License

MIT
