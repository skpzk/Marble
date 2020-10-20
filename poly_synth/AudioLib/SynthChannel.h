#ifndef SynthChannel_h
#define SynthChannel_h

#include "../AudioAPI/AudioConstants.h"
#include "WaveFolder.h"
#include "Filter.h"
#include "AudioObject.h"
#include "Oscs.h"

class SynthChannel;
#include "Modulator.h"

class SynthChannel: public AudioObject{
public:
    AudioObject* output;
    Modulator* modulator;
    Osc* osc;
    WaveFolder* wfolder;
    BiquadFilter* filter;

    SynthChannel();
    void selectWaveShape(int);
    void setInterpolation(float);
    void set(setterType, float);
    bool isActive();
    void activate(int);
    void deactivate();
    void off();

private:
    void setFinalOutput(AudioObject*);
};

#endif