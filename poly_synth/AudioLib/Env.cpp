#include "Env.h"

Env::Env(void){
    this->setA(50);
    this->setD(0);
    this->setS(127);
    this->setR(100);
    this->timeinterval = 1./SAMPLE_RATE;
    this->lastValue = 0;
    this->isOn = false;
    this->isActive = false;

    for (int i = 0; i < (FRAMES_PER_BUFFER); i++) {
        this->t[i] = ((float)i) / SAMPLE_RATE;
    }
}

void Env::on(){
    this->isOn = true;
    this->isActive = true;
    this->elapsed = 0;
}

void Env::off(){
    this->isOn = false;
    if (this->elapsed == 0) {
        this->isActive = false;
    }
    else {
        this->elapsed = 0;
    }
}

void Env::setA(float a){
    this->a = 3 * exp((a - 127) * 1. / 20);
}

void Env::setD(float d){
    this->d = 3 * exp((d - 127) * 1. / 20);
}

void Env::setS(float s){
    this->s = s/127.;
}

void Env::setR(float r){
	this->r = 5 * exp((r - 127) * 1. / 8);
}

sample_t Env::computeAttack(){
    if(this->a!=0){
        return MAX * this->elapsed / this->a;
    }else{
        return MAX;
    } 
}

sample_t Env::computeDecay(){
    if(this->d != 0){
        return MAX * (1 - (1 - this->s) * (this->elapsed - this->a) / this->d);
    }else{
        return MAX * this->s;
    }
}

sample_t Env::computeRelease(){
    if(this->r != 0){
        return 1 * (1 - this->elapsed / this->r) * this->lastValue;
    }else{
        return 0;
    }
}

void Env::output(void* outputBuffer, bool stereo, bool modification){
    sample_t* out = (sample_t*) outputBuffer;
    float tmp_elapsed, tmp_lastValue;
    if(modification){
        tmp_elapsed = this->elapsed;
        tmp_lastValue = this->lastValue;
    }

    for(int i=0; i<(FRAMES_PER_BUFFER); i++){
        if(this->isOn){
            if(this->elapsed < this->a){
                this->env[i] = this->computeAttack();
            }else if(this->elapsed < (this->a + this->d)){
                this->env[i] = this->computeDecay();             
            }else{
                this->env[i] = this->s * MAX;
            }
        this->lastValue = this->env[i];
        }else{
            if(this->elapsed < this->r){ //elapsed is reset to 0 when calling env::off
                this->env[i] = this->computeRelease();
            }else{
                this->isActive = false;
                this->env[i] = 0;
            }
        }
        this->elapsed += this->timeinterval;
        
    }
    for(int i=0; i<(FRAMES_PER_BUFFER); i++){
        *out++ = env[i]; //Mono/left
        if (stereo) {
            *out++ = env[i];  // right
        }
    }

    if(modification){
        this->elapsed = tmp_elapsed;
        this->lastValue = tmp_lastValue;
    }
}
