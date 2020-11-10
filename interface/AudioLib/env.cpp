#include "env.h"

Env::Env(){
    A = new StateParameter("env.A");
    A->setCallback(&Env::setMidiA, this);
    D.setCallback(&Env::setMidiD, this);
}

void Env::setMidiA(float f){
    midiA = f;
    cout << "setting Midi A :" << midiA << endl;
}

void Env::setMidiD(float i){
    midiD = i;
    cout << "setting Midi D :" << midiD << endl;
}