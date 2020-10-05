cmake_minimum_required(VERSION 3.0.0)
project(qwttest VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCES
    window.cpp  window.h
    plot.cpp    plot.h
    )

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include_directories(/usr/include/qwt)
link_directories(/usr/include/qwt)

add_executable(qwttest main.cpp ${SOURCES})

target_link_libraries(qwttest Qt5::Widgets qwt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
