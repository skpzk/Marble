cmake_minimum_required(VERSION 3.0.0)
project(interface VERSION 0.1.0)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Threads REQUIRED)

add_executable(interface main.cpp 
    Gui/window.cpp          Gui/window.h 
    Gui/cdial.cpp           Gui/cdial.h
    Gui/cslider.cpp         Gui/cslider.h
    Gui/state.h             Gui/state.cpp
    MidiApi/Midi.cpp    MidiApi/Midi.h
    MidiApi/RtMidi.h    MidiApi/RtMidi.cpp
    Utils/fileio.h      Utils/fileio.cpp
    AudioLib/osc.h               AudioLib/osc.cpp
    AudioLib/env.h               AudioLib/env.cpp   
    )


if (WIN32) 
    find_package(portaudio)
    find_package(rtmidi)
    target_include_directories(interface PUBLIC 
        "C:/Program Files (x86)/portaudio/include"
        "D:\\pthreads4w")
    target_link_libraries(interface 
        "C:/Program Files (x86)/portaudio/lib/portaudio_x64.lib"
        "D:/Vagrant/c++/rtmidi/out/install/x64-Debug (default)/lib/rtmidi.lib"
        "D:\\pthreads4w\\pthreadVC3.lib"
        Threads::Threads
        Qt5::Widgets
        winmm)
    set_target_properties(interface PROPERTIES COMPILE_OPTIONS -D__WINDOWS_MM__)
endif (WIN32)

if (UNIX)
    target_link_libraries(interface Qt5::Widgets
        Threads::Threads
        pthread
        asound
        jack
        rt
        m
        )
    set_target_properties(interface PROPERTIES COMPILE_OPTIONS -D__LINUX_ALSA__)
endif (UNIX)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
