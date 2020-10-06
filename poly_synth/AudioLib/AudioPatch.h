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


class AudioPatch{
    public:
        AudioPatch();
        void updateVoicesStatus();
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
};

#endif