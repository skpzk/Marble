#include "Note.h"

Note::Note(){

  //this->voices = Voices;

  this->osc = new Osc(440.);

  this->note = -1;
  this->order = -1;

  this->va.setOsc(this->osc);
  this->va.setEnv(&this->env);

}

void Note::on(int midinote){
  printf("Note::on\n");
  // set osc note
  this->env.on();
  this->osc->setNote(midinote);
  this->note = midinote ;
}

void Note::off(int midinote){
  printf("Note::off\n");
  this->setAmplitude(0);
  this->env.off();
}

void Note::setAmplitude(float a){
  this->amp = a;
}

bool Note::isActive(){
  return this->env.isActive;
}

void Note::setWaveform(int w){
  /* 0 : WAVEFORM_SINE
   * 1 : WAVEFORM_SAWTOOTH
   * 2 : WAVEFORM_TRIANGLE
   * 3 : WAVEFORM_SQUARE
   */
  if((w>=0)&&(w<4)){
    this->osc->setWave(w);
  }
  else{
    printf("Wrong waveform type\n");
  }
}
