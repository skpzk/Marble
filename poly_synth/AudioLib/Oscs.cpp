#include "Oscs.h"
#include <iostream>

Osc::Osc(float freq){
    this->setFreq(freq);
    this->setVolume(1);
    this->phase = 0.0;
    this->audioOutput = new AudioOutput(this);
}

void Osc::output(void* outputBuffer, bool stereo, bool mod){
    // printf("Getting data from Osc\n");
    sample_t *out = (sample_t*)outputBuffer;

    float tmpPhase;

    if(mod){
        tmpPhase = this->phase;
    }

    for(int i=0; i<FRAMES_PER_BUFFER; i++){
        *out++ = this->wave.wave[(int)this->phase] * this->volume;  // mono/left
        if(stereo){
	        	*out++ = this->wave.wave[(int)this->phase] * this->volume;  // right
			  }

        this->phase += (this->phaseIncrement);
        if( this->phase >= TABLE_SIZE ) this->phase -= TABLE_SIZE;
    }
    if(mod){
        this->phase = tmpPhase;
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
}



// Variable wt oscillators

VOsc::VOsc(float freq) {
    this->setFreq(freq);
    this->setVolume(1);
    this->phase = 0;
    this->waveshape = new WaveShape();
    this->interpFactor = 0;
    this->selectWaveShape(0);
    this->audioOutput = new AudioOutput(this);
}

void VOsc::selectWaveShape(int type) {
    this->waveshape->selectWaveShape(type);

    for (int i = 0; i < TABLE_SIZE; i++) {
        this->wave_output[i] = this->waveshape->waveforms[0][i];
    }
}

void VOsc::setInterpolation(float interpValue)
{
    this->interpFactor = interpValue * (this->waveshape->numWaves - 1);
}

void VOsc::interpolate()
{
    double intpart, fractpart;
    fractpart = modf(this->interpFactor, &intpart);

    sample_t* wave_1;
    sample_t* wave_2;
    wave_1 = this->waveshape->waveforms[(int)intpart];
    wave_2 = this->waveshape->waveforms[(int)intpart + 1];

    // std::cout << intpart << " " << fractpart << std::endl;

    if (fractpart != 0) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            this->wave_output[i] = wave_1[i] * (1 - fractpart) + wave_2[i] * fractpart;
        }
    }
}

void VOsc::output(void* outputBuffer, bool stereo, bool mod) {
    sample_t* out = (sample_t*)outputBuffer;

    sample_t in[FRAMES_PER_BUFFER];

    float tmpPhase;

    if(mod){
        tmpPhase = this->phase;
    }

    if(this->has_input){
        this->input->writeToBuffer(in, false, true);
        this->setInterpolation(((float)in[0])/(5. * MAX));
    }else{
        initBuffer(in, FRAMES_PER_BUFFER, 0); //not really useful here
    }
    

    this->interpolate();

    for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
        // this->setInterpolation(((float)in[i])/(5. * MAX));

        // this->interpolate();

        *out++ = this->wave_output[(int)this->phase] * this->volume;  // mono/left
        if (stereo) {
            *out++ = this->wave_output[(int)this->phase] * this->volume;  // right
        }
        this->phase += (this->phaseIncrement);
        if (this->phase >= TABLE_SIZE) this->phase -= TABLE_SIZE;
    }
    if(mod){
        this->phase = tmpPhase;
    }
}

void VOsc::setFreq(float freq) {
    this->freq = freq;
    this->updatePhaseIncrement();
}

void VOsc::setNote(float note) {
    this->freq = mtof(note);
    this->updatePhaseIncrement();
}
float VOsc::getNote() {
    return ftom(this->freq);
}

void VOsc::setVolume(float volume) {
    this->volume = volume;
}

void VOsc::updatePhaseIncrement() {
    this->phaseIncrement = this->freq * TABLE_SIZE / SAMPLE_RATE;
}
