#ifndef mixer_h_
#define mixer_h_

#include "../AudioAPI/AudioConstants.h"

class Mixer;
#include "Oscs.h"
#include "Vca.h"
#include "AudioOutput.h"

class Mixer {
public:
    void addInput(AudioOutput*);
    void output(void*, bool, bool);
    int test = 17;
    AudioOutput* audioOutput = NULL;
    Mixer();
private:
    int numInputs = 0;
    AudioOutput* inputs[VOICES];
    void writeInputsToBuffer(void* outputBuffer, bool Stereo, bool mod);
};

#endif