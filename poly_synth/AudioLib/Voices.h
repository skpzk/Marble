#ifndef Voices_h
#define Voices_h
#include "../AudioAPI/AudioConstants.h"
#include "Note.h"
#include "Mixer.h"

class Voices {
  public:
    Voices(int);
    Note** notes = NULL;
    Mixer* mixer = NULL;
    
    void on(int note);
    void off(int note);
    void update_status();
    void selectWaveShape(int);
    void modulate(modType, modValue);
    int setADSR(float, float, float, float);
    void set(setterType, float);
    void printVoices();
    
  private:
    int  total_voices;
    int  voice;

    bool is_note_played(int note);
    int  find_stop_voice(int note);
    int  find_free_voice();
    void update_order(int n);
    int  find_last_order();
    float adsr[4] = {0, 0, 127, 0};
};

#endif