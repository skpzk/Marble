#ifndef audiopatch_h_
#define audiopatch_h_

#include "../AudioAPI/AudioConstants.h"
class AudioPatch;
#include "../AudioAPI/Midi.h"
#include "../AudioAPI/audio.h"
#include "AudioOutput.h"

#include "Voices.h"
#include "Filter.h"
#include "WaveFolder.h"
#include "Note.h" //definition of setter types

struct thread_data {
   bool loop=true;
   AudioPatch* patch;
};

class AudioPatch{
    public:
        AudioPatch();
        static void* updateVoicesStatus(void*);
        void stop();
        //midi methods
        void on(int);
        void off(int);
        void cc(int, int);
        void setInterpolation(float);
        AudioOutput* audioOutput;
    private:
        Voices* voices=NULL;
        Audio* audio=NULL;
        Midi* midi=NULL;
        BiquadFilter* filter=NULL;
        WaveFolder* wfolder=NULL;
        void start();
        thread_data threadData;
};

#endif