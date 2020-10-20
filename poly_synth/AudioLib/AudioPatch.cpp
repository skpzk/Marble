#include "AudioPatch.h"
#include "pthread.h"
#include "../Utils/wait.h"

AudioPatch::AudioPatch(){
    
    this->voices = new Voices(VOICES); //the Voices class manages polyphony
    this->voices->selectWaveShape(0); //1: organ shapes
	this->voices->setADSR(200, 10, 100, 80);
    this->voices->modulate(envelope, interpolation);
    //this->voices->modulate(lfo, amplitude);

	// this->midi = new Midi(this->voices); //note on/off events are send to the Voices class
    this->midi = new Midi(this); //Midi events are send back to AudioPatch
	this->midi->open(0); //use a negative number to display an interactive port selection
	//or use directly the port number

 //   this->wfolder = new WaveFolder;
 //   this->wfolder->setInput(this->voices->mixer);

	//this->filter = new BiquadFilter;
	//this->filter->setInput(this->wfolder); // filter gets its input from mixer

	//this->filter->setFc(880.); //set the cutoff frequency
	//this->filter->setMidiFc(93.); //same with midi note number
	//this->filter->setQ(2.); //set the resonance (filter is a resonant low-pass)

    this->audioOutput = this->voices->mixer;
    this->audio = new Audio;
	this->audio->setInput(this->audioOutput); // Now audio class gets a generic AudioObject as input
    this->audio->start();

    this->start();
}

void AudioPatch::start(){

    pthread_t threads[1];
	int rc;
    
    this->threadData.loop = true;
    this->threadData.patch = this;

	cout << "audioPatch() : creating thread."<< endl;
	rc = pthread_create(&threads[0], NULL, updateVoicesStatus, (void*) &this->threadData);
	
	if (rc) {
		cout << "Error:unable to create thread," << rc << endl;
		exit(-1);
	}
}

void* AudioPatch::updateVoicesStatus(void* p){
    // cout << dline() << "AudioPatch UpdateStatus\n";
    thread_data* data = (thread_data*) p;

    while(data->loop){
    	sleep_for(100ms);
        // cout<<dline()<<"Update status\n";
    	data->patch->voices->update_status(); //update the order in which notes are played (not the best way to call it, could be called by a note off event)
    }   
    pthread_exit(NULL);
    return 0;
}

void AudioPatch::stop(){
    this->threadData.loop = false;
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
        //case 14:
        //    this->filter->setMidiFc(ccValue);
        //    break;
        //case 15:
        //    this->filter->setMidiQ(ccValue);
        //    break;
        case 16:
            // cout << dline() << "setting interp value\n";
            // this->setInterpolation(ccValue / (float)127);
            this->voices->set(interp, ccValue / (float)127);
            break;
        case 17:
            // cout << dline() << "setting folding limit\n";
            // this->voices->setFoldingLimit(ccValue);
            this->voices->set(fold, ccValue);
            break;
        case 18:
        case 73:
            this->voices->set(A, ccValue);
            // this->voices->setA(ccValue);
            break;
        case 19:
        case 75:
            this->voices->set(D, ccValue);
            // this->voices->setD(ccValue);
            break;
        case 20:
        case 79:
            this->voices->set(S, ccValue);
            // this->voices->setS(ccValue);
            break;
        case 21:
        case 84:
            this->voices->set(R, ccValue);
            // this->voices->setR(ccValue);
            break;
    }
}
