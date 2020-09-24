#include "Oscs.h"
#include <stdio.h>
#include <stdlib.h>

void Osc::output(void* outputBuffer){
  // printf("Getting data from Osc\n");
  sample_t *out = (sample_t*)outputBuffer;

	for(int i=0; i<FRAMES_PER_BUFFER; i++){ // Osc is MONO !
    //printf("Osc : this->wave.wave[(int)this->phase] = %d ", this->wave.wave[(int)this->phase]);
    *out++ = this->wave.wave[(int)this->phase] * this->volume;  // mono
    // *out++ = 0;


    this->phase += (this->phaseIncrement);
    if( this->phase >= TABLE_SIZE ) this->phase -= TABLE_SIZE;
    //printf("osc phase = %f\n", this->phase);
  }
}

void Osc::setWave(char type){
  this->wave = Wave(type);
}


void Osc::setFreq(float freq){
  this->freq = freq;
  this->updatePhaseIncrement();
}

void Osc::setNote(float note){
  this->freq = mtof(note);
  this->updatePhaseIncrement();
}
float Osc::getNote(){
  return ftom(this->freq);
}

void Osc::setVolume(float volume){
  this->volume = volume;
}

void Osc::updatePhaseIncrement(){
  this->phaseIncrement = this->freq * TABLE_SIZE / SAMPLE_RATE;
  // printf("osc phase increment = %f\n", this->phaseIncrement);
}
/*
int main(){
  printf("Osc\n");
  Osc osc;
  osc.setWave(3);

  sample_t buf[TABLE_SIZE];
  osc.output(buf, TABLE_SIZE);

  for(int i = 0; i < TABLE_SIZE; i++){
    //printf("%06d ", osc.wave.wave[i]);
    printf("%06d ", buf[i]);
  }
  printf("\n");

}*/
