cmake_minimum_required(VERSION 3.0.0)
project(audioAPIforMarble LANGUAGES C CXX VERSION 0.1.0)

include(CTest)
enable_testing()

# add_library(libportaudio /usr/local/lib/)


set(SOURCES
    Utils/wait.h
    AudioAPI/AudioConstants.h
    AudioAPI/audio.cpp      AudioAPI/audio.h
    AudioAPI/Midi.cpp       AudioAPI/Midi.h
    AudioAPI/RtMidi.cpp     AudioAPI/RtMidi.h
    AudioAPI/MidiUtils.cpp  AudioAPI/MidiUtils.h
    AudioLib/Oscs.cpp               AudioLib/Oscs.h
    AudioLib/Mixer.cpp              AudioLib/Mixer.h
    AudioLib/AudioCollection.cpp    AudioLib/AudioCollection.h
    AudioLib/Wave.cpp               AudioLib/Wave.h
    AudioLib/Va.cpp                 AudioLib/Va.h
    AudioLib/Voices.cpp             AudioLib/Voices.h
    AudioLib/Note.cpp               AudioLib/Note.h
    AudioLib/Env.cpp                AudioLib/Env.h
    )

add_executable(audioAPIforMarble main.cpp 
                ${SOURCES} 
                )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(audioAPIforMarble  /usr/local/lib/libportaudio.a
                      Threads::Threads
                      asound
                      jack
                      rt
                      m     
                      pthread  
                      )

set_target_properties(audioAPIforMarble PROPERTIES COMPILE_OPTIONS -D__LINUX_ALSA__)
#target_compile_options(audioAPIforMarble BEFORE -D__LINUX_ALSA__)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

