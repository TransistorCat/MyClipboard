cmake_minimum_required(VERSION 3.5)
project(core)
# add_library(core core.h core.cpp)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)


# 添加Qt的包含路径
include_directories(${Qt6Widgets_INCLUDE_DIRS})

# 添加你的可执行文件或库
add_executable(core core.cpp core.h)

# # 链接Qt模块
# target_link_libraries(core Qt6::Widgets)

