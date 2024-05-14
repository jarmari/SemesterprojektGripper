cmake_minimum_required(VERSION 3.0.0)

project(test2 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)
find_package(PkgConfig)
pkg_check_modules(TEST2 libserial)

add_executable(test2 new_main.cpp)
target_sources(test2 PRIVATE DBfetch.h gui.h transformations.h matrix.h rotmat.h move_robot.h serial.h)

target_link_libraries(test2 ${OpenCV_LIBS} ${SERIAL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test2 ${img})
target_link_libraries(test2 Qt5::Multimedia)
target_link_libraries(test2 Qt5::Core Qt5::Quick Qt5::Sql)


