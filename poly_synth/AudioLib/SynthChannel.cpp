#include "SynthChannel.h"

SynthChannel::SynthChannel() {
    this->osc = new Osc(440.);
    this->modulator = new Modulator(this);
    this->wfolder = new WaveFolder;
    this->wfolder->setInput(this->osc);
    this->filter = new BiquadFilter;
    this->filter->setInput(this->wfolder);
    this->filter->setFc(880.); //set the cutoff frequency
    this->filter->setQ(2.); //set the resonance (filter is a resonant low-pass)
    this->setFinalOutput(this->filter);
}

void SynthChannel::set(setterType t, float value) {
    switch (t) {
    case A:
        this->modulator->env->setA(value);
        break;
    case D:
        this->modulator->env->setD(value);
        break;
    case S:
        this->modulator->env->setS(value);
        break;
    case R:
        this->modulator->env->setR(value);
        break;
    case waveShape:
        this->osc->selectWaveShape(value);
        break;
    case interp:
        this->osc->setInterpolation(value);
        break;
    case fold:
        this->wfolder->setFoldingLimit(value);
        break;
    case filterFc:
        this->filter->setMidiFc(value);
        break;
    case filterQ:
        this->filter->setMidiQ(value);
        break;
    }
}

bool SynthChannel::isActive() {
    return this->modulator->isActive();
}

void SynthChannel::selectWaveShape(int type) {
    this->osc->selectWaveShape(type);
}

void SynthChannel::setInterpolation(float value){
    this->osc->setInterpolation(value);
}

void SynthChannel::activate(int midinote){
    this->modulator->on();
    this->osc->setNote(midinote);
    this->output->isOn = true;
}

void SynthChannel::deactivate(){
    this->modulator->off();
}

void SynthChannel::off()
{
    this->output->isOn = false;
}

void SynthChannel::setFinalOutput(AudioObject* output){
    this->output = output;
}