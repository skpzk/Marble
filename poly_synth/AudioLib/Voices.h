#ifndef Voices_h
#define Voices_h
#include "../AudioAPI/AudioConstants.h"
#include "Note.h"
#include "Mixer.h"

class Voices {
  public:
    Voices(int);
    Note** notes = NULL;
    
    void on(int note);
    void off(int note);
    void update_status();
    void connectToMixer(Mixer*);
    
    void setWaveform(int);
    void setAmplitude(float);

    void printVoices();

    Mixer mixer;
    
  private:

    int  total_voices;
    int  voice;
    bool is_note_played(int note);
    int  find_stop_voice(int note);
    int  find_free_voice();
    void update_order(int n);
    int  find_last_order();

};

#endif