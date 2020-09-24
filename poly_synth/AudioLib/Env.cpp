#include "Env.h"

Env::Env(void){
    this->setA(50);
    this->setD(0);
    this->setS(127);
    this->setR(100);
    for(int i=0; i<(FRAMES_PER_BUFFER); i++){
        this->t[i] = ((float) i) / SAMPLE_RATE;
    }
    this->timeinterval = 1./SAMPLE_RATE;
    this->lastValue = 0;
    this->state = -1;// 0: a, 1: d, 2: s, 3: r, -1: inactive
    //this->state is not really useful in this design
    this->isOn = false;
    this->isActive = false;

}

void Env::on(){
    this->isOn = true;
    this->isActive = true;
    this->elapsed = 0;
}

void Env::off(){
    this->isOn = false;
    this->elapsed = 0;
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
    return MAX * this->elapsed / this->a;
}

sample_t Env::computeDecay(){
    return MAX * (1 - (1 - this->s) * (this->elapsed - this->a) / this->d);
}

sample_t Env::computeRelease(){
    return 1 * (1 - this->elapsed / this->r) * this->lastValue;
}

void Env::output(void* outputBuffer){
    sample_t* out = (sample_t*) outputBuffer;

    
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
        //Mono output
        *out++ = env[i];
    }
    
}
