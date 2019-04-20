cmake_minimum_required(VERSION 3.1.0)

project(j2h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

add_subdirectory(./lib/j2hlib)

set(J2H_SRC
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp

)
add_executable(j2h ${J2H_SRC})
target_link_libraries(j2h Qt5::Widgets j2hlib)
