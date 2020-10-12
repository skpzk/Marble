#ifndef Note_h
#define Note_h
#include "../AudioAPI/AudioConstants.h"

#include "Oscs.h"
#include "Vca.h"
#include "Env.h"
#include "WaveFolder.h"

enum setterType{A, D, S, R, fc, Q, interp, fold, waveShape};

class Note {
  public :

    int note;  
    int order;
    float amp;
    
    void output(void*);
    
    Note();

    //method to start and stop
    void on(int);
    void off(int);

    void selectWaveShape(int);
    void setInterpolation(float);

    void setFoldingLimit(float);

    void setWaveform(int);
    void setAmplitude(float);

    void set(setterType, float);

    bool isActive();
  
    Vca vca = Vca();

    void setADSR(float*);

  private:
    Osc *osc;
    VOsc* vosc;
    Env env = Env();
    WaveFolder* wfolder;
};

#endif