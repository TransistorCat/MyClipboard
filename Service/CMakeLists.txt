cmake_minimum_required(VERSION 3.5)
project(Service)
# add_library(core core.h core.cpp)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS  Widgets Test Core Sql)


# 添加你的可执行文件或库
# qt_add_executable(testService
#   service.cpp
#   service.h
# )
# target_link_libraries(testService PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
# target_link_libraries(testService PRIVATE Qt${QT_VERSION_MAJOR}::Test)
# target_link_libraries(testService PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# target_link_libraries(testService PRIVATE Dao)

set(SOURCES
    service.cpp
    service.h
)
add_library(Service ${SOURCES})
target_link_libraries(Service PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(Service PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Service PRIVATE Dao)
target_include_directories(Service PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# # 链接Qt模块
# target_link_libraries(core Qt6::Widgets)

