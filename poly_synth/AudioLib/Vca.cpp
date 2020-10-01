#include "Vca.h"

Vca::Vca(){
    this->audioOutput = new AudioOutput(this);
}

void Vca::output(void* outputBuffer, bool stereo){
    // printf("Getting data from Osc\n");
    sample_t *out = (sample_t*)outputBuffer;

    if(this->has_input){
        this->input->writeToBuffer(this->bufInput, false);
    }else{
        initBuffer(this->bufInput, FRAMES_PER_BUFFER, 0); //initBuffer defined in Utils/SignalUtils
    }
    if(this->has_env){
        this->env->output(this->bufEnv);
    }else{
        initBuffer(this->bufEnv, FRAMES_PER_BUFFER, 1);
    }

    for(int i=0; i<(FRAMES_PER_BUFFER); i++){ // Vca is MONO !
        *out++ = bufInput[i] * ((float) bufEnv[i] / MAX) * this->volume;  // mono/left
        if(stereo){
	        *out++ = bufInput[i] * ((float) bufEnv[i] / MAX) * this->volume;// right
        }
        
    }
}

void Vca::setInput(AudioOutput* audioOutput){
    if(!this->has_input){
        this->input = audioOutput;
        this->has_input = true;
    }
}

void Vca::setEnv(Env* env){
    this->env = env;
    this->has_env = true;
}

void Vca::setVolume(float vol){
    this->volume = vol;
}
