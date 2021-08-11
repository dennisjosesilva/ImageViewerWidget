project(ImageViewerWidget)

# CMAKE VERSION
cmake_minimum_required(VERSION 3.10)

# INCLUDE DIRECTORY (HEADER FILES)
include_directories(../include)

# C++ STANDARD VERSION
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QT CONFIG
find_package(Qt5 REQUIRED Widgets Core Gui REQUIRED)

# SOURCES
file(GLOB_RECURSE PROJECT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# MOC SOURCES
qt5_wrap_cpp(PROJECT_SOURCE 
  ../include/ImageViewerWidget/ImageViewerWidget.hpp)

# LIB
add_library(ImageViewerWidget ${PROJECT_SOURCE})
target_link_libraries(ImageViewerWidget PUBLIC Qt5::Widgets Qt5::Core Qt5::Gui)