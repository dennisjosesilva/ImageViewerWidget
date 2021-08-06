project(ImageViewerWidget)

# CMAKE VERSION
cmake_minimum_required(VERSION 3.10)

# INCLUDE DIRECTORY (HEADER FILES)
include_directories(include)

# C++ STANDARD VERSION
set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT CONFIG
find_package(Qt5 REQUIRED Widgets Core Gui REQUIRED)

# SOURCES
file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# APP TEST
# file(GLOB_RECURSE APP_TEST_SOURCE "{CMAKE_CURRENT_SOURCE_DIR}/appTest/*.cpp")
set(APP_TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/appTest/mainwindow.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/appTest/main.cpp")

# MOC SOURCES
qt5_wrap_cpp(PROJECT_SOURCE 
  include/ImageViewerWidget/ImageViewerWidget.hpp)

# MOC APPTEST
qt5_wrap_cpp(APP_TEST_SOURCE 
  appTest/mainwindow.hpp)

# LIB
add_library(ImageViewerWidgetLib ${PROJECT_SOURCE})
target_link_libraries(ImageViewerWidgetLib PUBLIC Qt5::Widgets Qt5::Core Qt5::Gui)

# EXECUTABLES
add_executable(appTestExec ${APP_TEST_SOURCE})
target_link_libraries(appTestExec PUBLIC
  ImageViewerWidgetLib
  Qt5::Widgets
  Qt5::Core
  Qt5::Gui)