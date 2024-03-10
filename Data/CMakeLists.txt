cmake_minimum_required(VERSION 3.5)
project(Dao)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Sql Test Core)

# 使用 qt_add_executable 创建可执行文件
qt_add_executable(Dao
    testDao.cpp
    testDao.h
    dao.h
    dao.cpp

)
# add_executable(testDao ../Window/dao.cpp)

# qt6_generate_moc(testDao.cpp testDao.moc)
# 链接 Qt 库到 Test 可执行文件
target_link_libraries(Dao PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(Dao PRIVATE Qt${QT_VERSION_MAJOR}::Test)
# target_link_libraries(${PROJECT_NAME} PRIVATE window)
