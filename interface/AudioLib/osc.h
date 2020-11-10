#pragma once

#include "../Gui/state.h"

class Osc{
    public:
        StateParameter interp = StateParameter("osc.interp");
        StateParameter* freq;

        float midifreq = 0, midiInterp=0;
        Osc();
        void setMidiFreq(float);
        void setMidiInterp(float);
        static void setStaticThing(float);
};