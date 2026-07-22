cmake_minimum_required(VERSION 3.21)
project(JasNote VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

set(CMARK_STATIC ON CACHE BOOL "" FORCE)
set(CMARK_SHARED OFF CACHE BOOL "" FORCE)
set(CMARK_TESTS OFF CACHE BOOL "" FORCE)
set(CMARK_BIN_DIR ${CMAKE_BINARY_DIR}/cmark_bin)
add_subdirectory(cmark-gfm)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Network Test Svg)

add_executable(jasnote
    src/main.cpp
    src/mainwindow.cpp
    src/markdowneditor.cpp
    src/markdownconverter.cpp
    src/glassdialog.cpp
    src/titlebar.cpp
    src/config.cpp
)
target_include_directories(jasnote PRIVATE
    ${CMAKE_SOURCE_DIR}/cmark-gfm/src
    ${CMAKE_SOURCE_DIR}/cmark-gfm/extensions
    ${CMAKE_BINARY_DIR}/cmark-gfm/src
)
target_link_libraries(jasnote PRIVATE
    Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Network Qt6::Svg libcmark-gfm-extensions_static libcmark-gfm_static
)
install(TARGETS jasnote DESTINATION bin)

add_executable(jasnote_test
    tests/test_mainwindow.cpp
    src/mainwindow.cpp
    src/markdowneditor.cpp
    src/markdownconverter.cpp
    src/glassdialog.cpp
    src/titlebar.cpp
    src/config.cpp
)
target_include_directories(jasnote_test PRIVATE
    ${CMAKE_SOURCE_DIR}/cmark-gfm/src
    ${CMAKE_SOURCE_DIR}/cmark-gfm/extensions
    ${CMAKE_BINARY_DIR}/cmark-gfm/src
)
target_link_libraries(jasnote_test PRIVATE
    Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Network Qt6::Test Qt6::Svg libcmark-gfm-extensions_static libcmark-gfm_static
)
