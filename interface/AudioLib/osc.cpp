#include "osc.h"

Osc::Osc(){
    freq = new StateParameter("osc.freq");
    freq->setCallback(&Osc::setMidiFreq, this);
    interp.setCallback(&Osc::setMidiInterp, this);
}

void Osc::setMidiFreq(float f){
    midifreq = f;
    cout << "setting Midi freq :" << midifreq << endl;
}

void Osc::setMidiInterp(float i){
    midiInterp = i;
    cout << "setting Midi interp :" << midiInterp << endl;
}