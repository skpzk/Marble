cmake_minimum_required(VERSION 3.0.0)
project(qwttest VERSION 0.1.0)

include(CTest)
enable_testing()

set(SOURCES
    window.cpp  window.h
    plot.cpp    plot.h
    rtplot.cpp  rtplot.h
    )

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(qwttest main.cpp ${SOURCES})

if (WIN32)
    include_directories("D:\\Qwt-6.1.5\\include")
    link_directories("D:\\Qwt-6.1.5\\include")
    target_link_libraries(qwttest
    Qt5::Widgets
    "D:\\Qwt-6.1.5\\lib\\qwt.lib")
endif (WIN32)

if (UNIX)
    include_directories(/usr/include/qwt)
    link_directories(/usr/include/qwt)
    target_link_libraries(qwttest Qt5::Widgets qwt)
endif(UNIX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
