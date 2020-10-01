cmake_minimum_required(VERSION 3.0.0)
project(audioAPIforMarble LANGUAGES C CXX VERSION 0.1.0)

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
#    AudioLib/AudioCollection.cpp    AudioLib/AudioCollection.h
    AudioLib/Wave.cpp               AudioLib/Wave.h
    AudioLib/Vca.cpp                AudioLib/Vca.h
    AudioLib/Voices.cpp             AudioLib/Voices.h
    AudioLib/Note.cpp               AudioLib/Note.h
    AudioLib/Env.cpp                AudioLib/Env.h
    AudioLib/Filter.cpp             AudioLib/Filter.h
    AudioLib/AudioOutput.cpp        AudioLib/AudioOutput.h
)

add_executable(audioAPIforMarble main.cpp 
                ${SOURCES} 
                )

find_package(Threads REQUIRED)


if (WIN32) 
    find_package(portaudio)
    find_package(rtmidi)
    target_include_directories(audioAPIforMarble PUBLIC 
        "C:/Program Files (x86)/portaudio/include")
    target_link_libraries(audioAPIforMarble 
        "C:/Program Files (x86)/portaudio/lib/portaudio_x64.lib"
        "D:/Vagrant/c++/rtmidi/out/install/x64-Debug (default)/lib/rtmidi.lib"
        Threads::Threads
        winmm)
    set_target_properties(audioAPIforMarble PROPERTIES COMPILE_OPTIONS -D__WINDOWS_MM__)
endif (WIN32)

if (UNIX)
    target_link_libraries(audioAPIforMarble  /usr/local/lib/libportaudio.a
                          Threads::Threads
                          asound
                          jack
                          rt
                          m)

    set_target_properties(audioAPIforMarble PROPERTIES COMPILE_OPTIONS -D__LINUX_ALSA__)
endif (UNIX)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)