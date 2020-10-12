#include "Filter.h"

BiquadFilter::BiquadFilter(){
    this->maxFc = SAMPLE_RATE/2;
    this->T = 1. / SAMPLE_RATE;
    this->Q = 1.;
	this->Qinv = 1./this->Q;
    this->setFc(220.);
    this->audioOutput = new AudioOutput(this);
}

void BiquadState::update(float x, float y){
    this->xn2 = this->xn1;
    this->yn2 = this->yn1;
    this->xn1 = x;
    this->yn1 = y;
}

void BiquadFilter::setFc(float fc){
    this->fc = trim(fc, this->maxFc);
    this->computeCoefs();
}

void BiquadFilter::setMidiFc(float fc){
    this->setFc(mtof(fc));
}

void BiquadFilter::setQ(float Q){
	this->Q = trim(Q, 1, 100);
	this->Qinv = 1./this->Q;
    this->computeCoefs();
}
void BiquadFilter::setMidiQ(float Q){
    this->setQ(Q * 5./127.);
}

void BiquadFilter::computeCoefs(){
    float w0 = 2 * M_PI * this->fc * this->T;
    // w0 = omega0 : pulsation
    float a0 = 1 + sin(w0) * 0.5 * this->Qinv;
    float a0inv = 1. / a0;
    // a0 != 0 as long as fc <= samplerate/2
    float cosw0 = cos(w0);
    float b1 = (1 - cosw0) * .5 * a0inv;

    this->coefs.b0 = b1 ;
    this->coefs.b1 = b1 * 2;
    this->coefs.b2 = b1;

    this->coefs.a1 = -2 * cosw0 * a0inv;
    this->coefs.a2 = (2 - a0) * a0inv;
}

void BiquadFilter::output(void* outputBuffer, bool stereo, bool mod){
    sample_t in[FRAMES_PER_BUFFER];

    this->input->writeToBuffer(in, false, mod);
    
    sample_t *out = (sample_t*)outputBuffer;
    float data = 0;

    BiquadState tmpState;

    if(mod){
        tmpState.xn1 = this->state.xn1;
        tmpState.xn2 = this->state.xn2;
        tmpState.yn1 = this->state.yn1;
        tmpState.yn2 = this->state.yn2;
    }

	for(int i=0; i<FRAMES_PER_BUFFER; i++){ 

        data = in[i] * this->coefs.b0 
            + this->coefs.b1 * this->state.xn1 + this->coefs.b2 * this->state.xn2
    	    - this->coefs.a1 * this->state.yn1 - this->coefs.a2 * this->state.yn2;

    	this->state.update(in[i], data);
 
        *out++ = (sample_t) data;  // mono/left
        if(stereo){
			*out++ = (sample_t) data; //right
		}

    }

    if(mod){
        this->state.xn1 = tmpState.xn1;
        this->state.xn2 = tmpState.xn2;
        this->state.yn1 = tmpState.yn1;
        this->state.yn2 = tmpState.yn2;
    }
}
