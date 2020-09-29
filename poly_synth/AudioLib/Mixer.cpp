#include "Mixer.h"

#include <stdlib.h>
#include <stdio.h>


void Mixer::output(void* outputBuffer, int framesPerBuffer, bool Stereo){
	//get sound data
	if(this->numInputs > 0){
		this->inputs.output(outputBuffer, Stereo);
	}else{
		sample_t *out = (sample_t*)outputBuffer;
		for(int i=0; i < framesPerBuffer; i++){
			*out++ = SILENCE;
			if(Stereo){
	        	*out++ = SILENCE;
			}
		}
	}
}
void Mixer::addInput(Vca* input){
	this->numInputs++;
	this->inputs.addElement(input);
}
