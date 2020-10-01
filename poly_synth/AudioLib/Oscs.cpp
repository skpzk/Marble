#include "Oscs.h"

Osc::Osc(float freq){
    this->setFreq(freq);
    this->setVolume(1);
    this->phase = 0.0;
    this->audioOutput = new AudioOutput(this);
}

void Osc::output(void* outputBuffer, bool stereo){
    // printf("Getting data from Osc\n");
    sample_t *out = (sample_t*)outputBuffer;

    for(int i=0; i<FRAMES_PER_BUFFER; i++){ // Osc is MONO !
        *out++ = this->wave.wave[(int)this->phase] * this->volume;  // mono/left
        if(stereo){
	        	*out++ = this->wave.wave[(int)this->phase] * this->volume;  // right
			  }

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

