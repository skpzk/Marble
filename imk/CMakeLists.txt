cmake_minimum_required(VERSION 3.0.0)
project(kbd VERSION 0.1.0)
set(CMAKE_AUTOMOC ON)

include(CTest)
enable_testing()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Threads REQUIRED)

add_executable(imk main.cpp 
    window.cpp          window.h 
    MidiApi/Midi.cpp    MidiApi/Midi.h
    MidiApi/RtMidi.h    MidiApi/RtMidi.cpp
    Utils/keys.h            Utils/keys.cpp
    Utils/fileio.h          Utils/fileio.cpp
    Utils/calibrationData.h Utils/calibrationData.cpp)

target_link_libraries(imk Qt5::Widgets
    Threads::Threads
    pthread
    asound
    jack
    rt
    m
    )
set_target_properties(imk PROPERTIES COMPILE_OPTIONS -D__LINUX_ALSA__)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
