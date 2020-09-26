#ifndef Note_h
#define Note_h
#include "Oscs.h"
#include "../AudioAPI/AudioConstants.h"
#include "Va.h"
#include "Env.h"

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
    
    void setWaveform(int);
    void setAmplitude(float);

    bool isActive();
  
    Va va;

  private:
    Osc *osc;
    Env env;
};

#endif