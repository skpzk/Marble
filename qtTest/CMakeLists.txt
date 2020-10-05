cmake_minimum_required(VERSION 3.0.0)
project(qttest VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
add_executable(qttest main.cpp)

target_link_libraries(qttest Qt5::Widgets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
