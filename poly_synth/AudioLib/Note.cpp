#include "Note.h"

Note::Note(){

  this->osc = new Osc(440.);
  this->vosc = new VOsc(440.);

  this->wfolder = new WaveFolder;

  this->note = -1;
  this->order = -1;

  this->wfolder->setInput(this->vosc->audioOutput);

  this->vca.setInput(this->wfolder->audioOutput);
  this->vca.setEnv(this->env.audioOutput);
  this->vosc->setInput(this->env.audioOutput);
}

void Note::on(int midinote){
  // set osc note
  this->env.on();
  //this->osc->setNote(midinote);
  this->vosc->setNote(midinote);
  this->note = midinote ;
}

void Note::off(int midinote){
  this->setAmplitude(0);
  this->env.off();
}

void Note::set(setterType t, float value){
  switch(t){
    case A:
      this->env.setA(value);
      break;
    case D:
      this->env.setD(value);
      break;
    case S:
      this->env.setS(value);
      break;
    case R:
      this->env.setR(value);
      break;
    case waveShape:
      this->vosc->selectWaveShape(value);
      break;
    case interp:
      this->vosc->setInterpolation(value);
      break;
    case fold:
      this->wfolder->setFoldingLimit(value);
      break;
  }

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

void Note::selectWaveShape(int type) {
    this->vosc->selectWaveShape(type);
}

void Note::setInterpolation(float value)
{
    this->vosc->setInterpolation(value);
}

void Note::setFoldingLimit(float value)
{
    this->wfolder->setFoldingLimit(value);
}

void Note::setADSR(float* adsr){
  this->env.setA(adsr[0]);
  this->env.setD(adsr[1]);
  this->env.setS(adsr[2]);
  this->env.setR(adsr[3]);
}
