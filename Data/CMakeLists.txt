cmake_minimum_required(VERSION 3.5)
project(Data)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Sql Test Core)



set(SOURCES
    dao.h
    dao.cpp
)
add_library(Dao ${SOURCES})
target_link_libraries(Dao PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_include_directories(Dao PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# qt6_generate_moc(testDao.cpp testDao.moc)


# 使用 qt_add_executable 创建可执行文件
qt_add_executable(testDao
    testDao.cpp
    testDao.h
    dao.h
    dao.cpp

)
# 链接 Qt 库到 Test 可执行文件
target_link_libraries(testDao PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(testDao PRIVATE Qt${QT_VERSION_MAJOR}::Test)
