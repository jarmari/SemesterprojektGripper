cmake_minimum_required(VERSION 3.1...3.28)

project(GUI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

add_executable(GUI main.cpp)
target_sources(GUI PRIVATE DBfetch.h gui.h)

target_link_libraries(GUI ${OpenCV_LIBS})
target_link_libraries(GUI ${img})
target_link_libraries(GUI Qt5::Multimedia)
target_link_libraries(GUI Qt5::Core Qt5::Quick Qt5::Sql)
