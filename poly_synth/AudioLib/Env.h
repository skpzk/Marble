#ifndef env_h_
#define env_h_

#include "../AudioAPI/AudioConstants.h"
#include <math.h>

class Env{
    public:
        void setA(float);
        void setD(float);
        void setS(float);
        void setR(float);
        void on();
        void off();
        bool isActive;
        bool isOn;
        void output(void*);
        Env();

    private:
        float a, d, s, r;
        float elapsed, timeinterval;
        sample_t t[FRAMES_PER_BUFFER];
        sample_t env[FRAMES_PER_BUFFER];
        sample_t lastValue;
        int state;

        sample_t computeAttack();
        sample_t computeDecay();
        sample_t computeRelease();
};

#endif
