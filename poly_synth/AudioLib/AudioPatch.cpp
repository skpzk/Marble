#include "AudioPatch.h"
#include "pthread.h"
#include "../Utils/wait.h"

AudioPatch::AudioPatch(){
    
    this->voices = new Voices(VOICES); //the Voices class manages polyphony
    this->voices->selectWaveShape(0); //1: organ shapes

    float adsr[] = { 200, 10, 100, 80 };
    this->voices->setADSR(ampEnvelope, adsr);
    this->voices->setADSR(envelope, adsr);

    this->voices->modulate(ampEnvelope, amplitude);
    this->voices->modulate(lfo, interpolation);

    this->midi = new Midi(this); //Midi events are send back to AudioPatch
	this->midi->open(0); //use a negative number to display an interactive port selection
	//or use directly the port number

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
        case 14:
            this->voices->set(filterFc, ccValue);
            break;
        case 15:
            this->voices->set(filterQ, ccValue);
            break;
        case 16:
            // cout << dline() << "setting interp value\n";
            this->voices->set(interp, ccValue / (float)127);
            break;
        case 17:
            // cout << dline() << "setting folding limit\n";
            this->voices->set(fold, ccValue);
            break;
        case 18:
        case 73:
            this->voices->set(A, ccValue);
            break;
        case 19:
        case 75:
            this->voices->set(D, ccValue);
            break;
        case 20:
        case 79:
            this->voices->set(S, ccValue);
            break;
        case 21:
        case 84:
            this->voices->set(R, ccValue);
            break;
    }
}
