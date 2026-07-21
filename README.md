# JasNote

A WYSIWYG Markdown editor built with Qt 6.

## Requirements

- Qt 6.5+
- CMake 3.21+
- C++17 compiler (GCC, Clang, or MSVC)

## Build

### 1. Clone dependencies

```bash
git clone https://github.com/github/cmark-gfm.git
git clone https://github.com/litehtml/litehtml.git
```

### 2. Build

#### Linux / macOS

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

#### Windows (MSVC)

```bat
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

#### Windows (MinGW / MSYS2)

```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

### 3. Run

```bash
./build/jasnote
```

### Specifying Qt path

If CMake cannot find Qt automatically, pass the Qt installation path:

```bash
cmake .. -DCMAKE_PREFIX_PATH="/path/to/qt/6.x.x/<compiler>"
```

For example:

```bash
# MinGW
cmake .. -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/Qt/6.10.2/mingw_64"

# MSVC
cmake .. -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH="C:/Qt/6.10.2/msvc2022_64"
```

## Configuration

Edit `config.json` to override default settings. Only specify values you want to change.

Config is loaded from:

1. `~/.config/jasnote/config.json` (system-wide)
2. `./config.json` (local)

## License

MIT
