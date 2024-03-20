cmake_minimum_required(VERSION 3.5)

project(MyClipboard VERSION 0.1 LANGUAGES CXX)


add_subdirectory(Service)

set(QT_NO_SQL_MYSQL ON)


add_subdirectory(Window)
add_subdirectory(Data)
# add_custom_target(MyClipboard
#     COMMAND linuxdeployqt ${CMAKE_INSTALL_PREFIX}/bin/MyClipboard -appimage
#     WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
# )
# 打包相关设置
set(CPACK_PACKAGE_NAME "MyClipboard")
set(CPACK_PACKAGE_VERSION "${MyClipboard_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION "Description of MyClipboard")
set(CPACK_PACKAGE_CONTACT "Your Contact Information")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_GENERATOR "ZIP")

# 调用linuxdeployqt打包AppDir
add_custom_target(bundle
    COMMAND linuxdeployqt "/home/TransistorCat/code/Qt/MyClipboard/build/Window/MyClipboard" -appimage
    WORKING_DIRECTORY "/home/TransistorCat/code/Qt/MyClipboard/build"
    COMMENT "Creating AppImage using linuxdeployqt"
)

# 包含CPack模块
include(CPack)
