#ifndef mixer_h_
#define mixer_h_

#include "../AudioAPI/AudioConstants.h"
#include "Oscs.h"
#include "AudioObject.h"

class Mixer : public AudioObject{
public:
    void addInput(AudioObject*);
    void output(void*, bool, bool);
    int test = 17;
private:
    int numInputs = 0;
    AudioObject* inputs[VOICES];
    void writeInputsToBuffer(void* outputBuffer, bool Stereo, bool mod);
};

#endif