#include "Oscs.h"
#include <iostream>

// Variable wt oscillators

Osc::Osc(float freq) {
    this->setFreq(freq);
    this->setAmplitude(1);
    this->phase = 0;
    this->waveshape = new WaveShape();
    this->interpFactor = 0;
}

void Osc::selectWaveShape(int type) {
    this->waveshape->selectWaveShape(type);

    for (int i = 0; i < TABLE_SIZE; i++) {
        this->wave_output[i] = this->waveshape->waveforms[0][i];
    }

    this->interpModulation.setValue(1);
}

void Osc::setInterpolation(float interpValue)
{
    this->interpFactor = interpValue * (this->waveshape->numWaves - 1);
}

//void Osc::addInterpolation(float interpValue)
//{
//    this->interpFactor = trim(this->interpValue 
//        + interpValue * (this->waveshape->numWaves - 1), this->waveshape->numWaves - 1);
//}

void Osc::interpolate()
{
    float* modulation = this->interpModulation.getValueBuffer();
    float interpolation;

    interpolation = trim(this->interpFactor
        + (modulation[0] / 3.) * (this->waveshape->numWaves - 1), this->waveshape->numWaves - 1);

    double intpart, fractpart;
    fractpart = modf(interpolation, &intpart);

    sample_t* wave_1;
    sample_t* wave_2;
    wave_1 = this->waveshape->waveforms[(int)intpart];
    wave_2 = this->waveshape->waveforms[(int)intpart + 1];

    if (fractpart != 0) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            this->wave_output[i] = wave_1[i] * (1 - fractpart) + wave_2[i] * fractpart;
        }
    }
}

void Osc::output(void* outputBuffer, bool stereo, bool mod) {
    sample_t* out = (sample_t*)outputBuffer;
    sample_t in[FRAMES_PER_BUFFER];

    float tmpPhase;

    if(mod){
        tmpPhase = this->phase;
    }
    //
    //if(this->has_input){
    //    this->input->output(in, false, true);
    //    this->addInterpolation(((float)in[0])/(3. * MAX));
    //}else{
    //    initBuffer(in, FRAMES_PER_BUFFER, 0); //not really useful here
    //}
    
    this->interpolate();

    float* amplitude = this->amplitude.getValueBuffer();

    for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
        *out++ = this->wave_output[(int)this->phase] * amplitude[i];  // mono/left

        if (stereo) {
            *out++ = this->wave_output[(int)this->phase] * amplitude[i];  // right
        }
        this->phase += (this->phaseIncrement);
        if (this->phase >= TABLE_SIZE) this->phase -= TABLE_SIZE;
    }
    if(mod){
        this->phase = tmpPhase;
    }
}

void Osc::setFreq(float freq) {
    this->freq = freq;
    this->updatePhaseIncrement();
}

void Osc::setNote(float note) {
    this->freq = mtof(note);
    this->updatePhaseIncrement();
}

float Osc::getNote() {
    return ftom(this->freq);
}

void Osc::setAmplitude(float amplitude) {
    this->amplitude.setValue(amplitude);
}

void Osc::updatePhaseIncrement() {
    this->phaseIncrement = this->freq * TABLE_SIZE / SAMPLE_RATE;
}
