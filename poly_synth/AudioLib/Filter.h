#ifndef filter_h_
#define filter_h_

#include <math.h> 

#include "../AudioAPI/AudioConstants.h"
#include "../Utils/SignalUtils.h"
#include "../AudioAPI/MidiUtils.h"
// class BiquadFilter;
#include "AudioOutput.h"
#include "AudioObject.h"

enum FilterType{lpf, bpf};

typedef struct{
	float b0, b1, b2, a1, a2;
}BiquadCoefs;


class BiquadState{
    public:
        //BiquadState();
        void update(float, float);
        float xn1=0, xn2=0, yn1=0, yn2=0;
};

class BiquadFilter : public AudioObject{
    public:
        void output(void*, bool, bool);

        void setFc(float);
        void setMidiFc(float);

        // lpf
        void setQ(float);
        void setMidiQ(float);

        // bpf
        void setBW(float);
        void setMidiBW(float);

        void setFilterType(FilterType);
        BiquadFilter();

    private:
        float fc, maxFc, T;
        float Q, Qinv, BW;
		BiquadCoefs coefs;
        BiquadState state;
        void computeCoefs();
        void computeCoefsLpf();
        void computeCoefsBpf();
        void updateQ(); //lpf
        void updateBW(); //bpf
        FilterType filterType;
        // bool has_input=false;
};


#endif