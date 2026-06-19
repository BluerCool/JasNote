cmake_minimum_required(VERSION 3.16)
project(JasNote VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Test)

add_executable(jasnote
    src/main.cpp
    src/mainwindow.cpp
    src/markdowneditor.cpp
)
target_link_libraries(jasnote PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

add_executable(jasnote_test
    tests/test_mainwindow.cpp
    src/mainwindow.cpp
    src/markdowneditor.cpp
)
target_link_libraries(jasnote_test PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Test)
