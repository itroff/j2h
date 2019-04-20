cmake_minimum_required(VERSION 3.1)
project (j2hlib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
include_directories(./src)
find_package(Qt5Core CONFIG REQUIRED)
FILE(GLOB_RECURSE INC_ALL "src/*.h")

SET(CMAKE_CXX_FLAGS "${CXX_FLAGS} -march=native -g  -std=c++1y")

add_library(j2hlib SHARED src/page.cpp src/tag.cpp src/tagimg.cpp src/tagp.cpp src/taga.cpp ${INC_ALL})
target_link_libraries(j2hlib
  Qt5::Core
)
target_include_directories(j2hlib PUBLIC ./src)


#testing
aux_source_directory(./test test)

add_executable(testing test/test.cpp src/page.cpp src/tag.cpp src/tagimg.cpp src/tagp.cpp src/taga.cpp ${INC_ALL})
target_link_libraries(testing
  Qt5::Core
)



