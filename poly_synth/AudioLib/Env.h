#ifndef env_h_
#define env_h_

#include "../AudioAPI/AudioConstants.h"
#include <math.h>

#include "../AudioAPI/AudioConstants.h"
#include "../Utils/SignalUtils.h" //defines initBuffer

// class Env;
#include "AudioObject.h"

class Env : public AudioObject{
    public:
        void setA(float);
        void setD(float);
        void setS(float);
        void setR(float);
        void on();
        void off();
        bool isActive;
        Env();
        void output(void*, bool, bool);

    private:
        float a, d, s, r;
        float elapsed, timeinterval;
        sample_t t[FRAMES_PER_BUFFER];
        sample_t env[FRAMES_PER_BUFFER];
        sample_t lastValue;

        sample_t computeAttack();
        sample_t computeDecay();
        sample_t computeRelease();
};

#endif
