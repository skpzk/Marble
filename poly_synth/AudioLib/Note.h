#ifndef Note_h
#define Note_h
#include "../AudioAPI/AudioConstants.h"

#include "WaveFolder.h"
#include "SynthChannel.h"

class Note {
  public :
    int note;
    int order;
    SynthChannel* channel;
    
    Note();
    void on(int);
    void off(int);
    bool isActive();
};

#endif