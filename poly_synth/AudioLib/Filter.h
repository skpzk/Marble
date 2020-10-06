#ifndef filter_h_
#define filter_h_

#include <math.h> 

#include "../AudioAPI/AudioConstants.h"
#include "../Utils/SignalUtils.h"
#include "../AudioAPI/MidiUtils.h"
class BiquadFilter;
#include "AudioOutput.h"

typedef struct{
	float b0, b1, b2, a1, a2;
}BiquadCoefs;


class BiquadState{
    public:
        //BiquadState();
        void update(float, float);
        float xn1=0, xn2=0, yn1=0, yn2=0;
};

class BiquadFilter{
    public:
        void output(void*, bool, bool);
        void setInput(AudioOutput*);
        AudioOutput* input=NULL;
        AudioOutput* audioOutput=NULL;
        void setFc(float);
        void setMidiFc(float);
        void setQ(float);
        void setMidiQ(float);
        BiquadFilter();

    private:
        float fc, maxFc, T;
        float Q, Qinv;
		BiquadCoefs coefs;
        BiquadState state;
        void computeCoefs();
        void updateQ();
        bool has_input=false;
};


#endif