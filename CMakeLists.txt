cmake_minimum_required(VERSION 3.19.2) #cmake最低版本
project(QssEditor) #工程名

set(CMAKE_CXX_STANDARD 14) #C++标准
# 开启QT用于预处理的组件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# 设置cmake模块的查询目录，注意这里的路径，到mingw路径即可
set(CMAKE_PREFIX_PATH D:/Qt/5.14.2/mingw73_64)
# 查找QT的模块

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
# 添加源文件
add_executable(QssEditor
        From/main.cpp
        Header/MainWindow.h
        From/MainWindow.cpp
        Header/EditWidget.h
        From/EditWidget.cpp
        From/TabWidget.cpp
        Header/TabWidget.h
        From/Dialog.cpp
        Header/Dialog.h
        Header/Syntax.h
        From/Syntax.cpp
        app_win32.rc Header/HelpWidget.h From/HelpWidget.cpp)
# 添加模块
target_link_libraries(QssEditor
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )