#pragma once

#include "../Gui/state.h"

class Env{
    public:
        StateParameter D = StateParameter("env.D");
        StateParameter* A;

        float midiA = 0, midiD=0;
        Env();
        void setMidiA(float);
        void setMidiD(float);
};