#include "AudioPatch.h"
#include "AudioPatch.h"

AudioPatch::AudioPatch(){
    
    this->voices = new Voices(VOICES); //the Voices class manages polyphony

	//this->voices->setWaveform(3); //0: sine; 1: saw; 2: tri; 3: square
    this->voices->selectWaveShape(0); //0: basic shapes
	this->voices->setAmplitude(1);
	this->voices->setADSR(30, 10, 100, 80);

	// this->midi = new Midi(this->voices); //note on/off events are send to the Voices class
    this->midi = new Midi(this); //Midi events are send back to AudioPatch
    
	this->midi->open(0); //use a negative number to display an interactive port selection
	//or use directly the port number

	this->filter = new BiquadFilter;
	this->filter->setInput(this->voices->mixer.audioOutput); // filter gets its input from mixer

	this->filter->setFc(330.); //set the cutoff frequency
	this->filter->setMidiFc(60.); //same with midi note number
	this->filter->setQ(2.); //set the resonance (filter is a resonant low-pass)

    this->audio = new Audio;
	this->audio->setInput(this->filter->audioOutput); // Now audio class gets a generic AudioOutput as input

    this->audio->start();
}

void AudioPatch::updateVoicesStatus(){
    this->voices->update_status();
}

void AudioPatch::stop(){
    this->midi->close();
	this->audio->stop();
}

void AudioPatch::on(int note){
    this->voices->on(note);
}

void AudioPatch::off(int note){
    this->voices->off(note);
}

void AudioPatch::cc(int ccNumber, int ccValue){
    switch(ccNumber){
        case 14:
            this->filter->setMidiFc(ccValue);
            break;
        case 15:
            this->filter->setMidiQ(ccValue);
            break;
    }
}

void AudioPatch::setInterpolation(float value)
{
    this->voices->setInterpolation(value);
}
