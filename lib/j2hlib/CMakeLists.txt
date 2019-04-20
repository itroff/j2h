cmake_minimum_required(VERSION 3.1)
project (j2hlib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
include_directories(./src)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Xml CONFIG REQUIRED)
FILE(GLOB_RECURSE INC_ALL "src/*.h")

SET(CMAKE_CXX_FLAGS "${CXX_FLAGS} -march=native -g  -std=c++1y")

add_library(j2hlib SHARED src/page.cpp ${INC_ALL})
target_link_libraries(j2hlib
  Qt5::Core
  Qt5::Xml
)
target_include_directories(j2hlib PUBLIC ./src)


#testing
#aux_source_directory(./test test)

#add_executable(testing test/test.cpp src/ipv4.cpp src/ipv6.cpp src/ip.cpp test/test.cpp ${INC_ALL})



