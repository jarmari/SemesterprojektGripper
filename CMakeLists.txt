cmake_minimum_required(VERSION 3.1...3.28)

project(Semesterprojekt_2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)

add_executable(Semesterprojekt_2 new_main.cpp)
target_sources(Semesterprojekt_2 PRIVATE DBfetch.h gui.h transformations.h matrix.h rotmat.h move_robot.h)

target_link_libraries(Semesterprojekt_2 ${OpenCV_LIBS})
target_link_libraries(Semesterprojekt_2 ${img})
target_link_libraries(Semesterprojekt_2 Qt5::Multimedia)
target_link_libraries(Semesterprojekt_2 Qt5::Core Qt5::Quick Qt5::Sql)

