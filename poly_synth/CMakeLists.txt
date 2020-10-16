cmake_minimum_required(VERSION 3.0.0)
project(audioAPIforMarble LANGUAGES C CXX VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

set(SOURCES
    Utils/wait.h
    Utils/DebugUtils.cpp    Utils/DebugUtils.h
    Utils/SignalUtils.cpp   Utils/SignalUtils.h
    AudioAPI/AudioConstants.h
    AudioAPI/audio.cpp      AudioAPI/audio.h
    AudioAPI/Midi.cpp       AudioAPI/Midi.h
    AudioAPI/RtMidi.cpp     AudioAPI/RtMidi.h
    AudioAPI/MidiUtils.cpp  AudioAPI/MidiUtils.h
    AudioLib/Oscs.cpp               AudioLib/Oscs.h
    AudioLib/Mixer.cpp              AudioLib/Mixer.h
    AudioLib/AudioPatch.cpp         AudioLib/AudioPatch.h
    AudioLib/Wave.cpp               AudioLib/Wave.h
    AudioLib/Vca.cpp                AudioLib/Vca.h
    AudioLib/Voices.cpp             AudioLib/Voices.h
    AudioLib/Note.cpp               AudioLib/Note.h
    AudioLib/Env.cpp                AudioLib/Env.h
    AudioLib/Filter.cpp             AudioLib/Filter.h
    AudioLib/AudioOutput.cpp        AudioLib/AudioOutput.h
    AudioLib/WaveFolder.cpp         AudioLib/WaveFolder.h
    AudioLib/AudioObject.cpp        AudioLib/AudioObject.h
    AudioLib/Modulation.cpp       AudioLib/Modulation.h
    AudioLib/SynthChannel.cpp       AudioLib/SynthChannel.h
    Qt/plot.cpp                     Qt/plot.h)


add_executable(audioAPIforMarble main.cpp 
                ${SOURCES})

find_package(Threads REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)


if (WIN32) 
    include_directories("D:\\Qwt-6.1.5\\include")
    link_directories("D:\\Qwt-6.1.5\\include")
    find_package(portaudio)
    find_package(rtmidi)
    target_include_directories(audioAPIforMarble PUBLIC 
        "C:/Program Files (x86)/portaudio/include"
        "D:\\pthreads4w")
    target_link_libraries(audioAPIforMarble 
        "C:/Program Files (x86)/portaudio/lib/portaudio_x64.lib"
        "D:/Vagrant/c++/rtmidi/out/install/x64-Debug (default)/lib/rtmidi.lib"
        "D:\\Qwt-6.1.5\\lib\\qwt.lib"
        "D:\\pthreads4w\\pthreadVC3.lib"
        Threads::Threads
        Qt5::Widgets
        winmm)
    set_target_properties(audioAPIforMarble PROPERTIES COMPILE_OPTIONS -D__WINDOWS_MM__)
endif (WIN32)

if (UNIX)
    include_directories(/usr/include/qwt)
    link_directories(/usr/include/qwt)
    target_link_libraries(audioAPIforMarble  
        /usr/local/lib/libportaudio.a
        Threads::Threads
        pthread
        asound
        jack
        rt
        m
        Qt5::Widgets
        qwt
        )
# maybe this line is better than set(CMAKE_CXX_STANDARD 17)
#    target_compile_features(audioAPIforMarble PRIVATE cxx_std_17)

    set_target_properties(audioAPIforMarble PROPERTIES COMPILE_OPTIONS -D__LINUX_ALSA__)
endif (UNIX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)