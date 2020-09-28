#include "Va.h"

#include <stdio.h>
#include <stdlib.h>

void Va::output(void* outputBuffer){
    // printf("Getting data from Osc\n");
    sample_t *out = (sample_t*)outputBuffer;

    if(this->has_osc){
        this->osc->output(this->bufOsc);
        if(this->has_env){
            this->env->output(this->bufEnv);
        }else{
            this->init(this->bufEnv, 1);
        }
    }else{
        this->init(this->bufOsc, 0);
        this->init(this->bufEnv, 1);
    }
    for(int i=0; i<(FRAMES_PER_BUFFER); i++){ // Va is MONO !
        *out++ = bufOsc[i] * ((float) bufEnv[i] / MAX) * this->volume;  // mono
    }
}

void Va::init(sample_t* buffer, int value){
    for(int i=0; i<(FRAMES_PER_BUFFER); i++){     
        *buffer++ = value;
    }
}

void Va::setOsc(Osc* osc){
    this->osc = osc;
    this->has_osc = true;
}

void Va::setEnv(Env* env){
    this->env = env;
    this->has_env = true;
}

void Va::setVolume(float vol){
    this->volume = vol;
}
