#include "Mixer.h"

// Utils functions

void deleteBuffer(sample_t** inputBuffer, int a) {
	for (int j = 0; j < a; j++) {
		delete[] inputBuffer[j];
	}
	delete[] inputBuffer;
	inputBuffer = NULL;
}

void silence(void* outputBuffer, bool stereo) {
	sample_t* out = (sample_t*)outputBuffer;

	for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
		*out++ = SILENCE;
		if (stereo) {
			*out++ = SILENCE;
		}
	}
}


// Mixer class

void Mixer::output(void* outputBuffer, bool stereo, bool mod) {
	//get sound data
	if (this->numInputs > 0) {
		this->writeInputsToBuffer(outputBuffer, stereo, mod);
	}
	else {
		silence(outputBuffer, stereo);
	}
}

void Mixer::addInput(AudioObject* input) {
	this->inputs[this->numInputs] = input;
	this->numInputs++;
}

sample_t** allocateBuffer(int a, int frames) {
	sample_t** t = new sample_t * [a];
	for (int i = 0; i < a; i++)
	{
		t[i] = new sample_t[frames];
		if (t[i] == NULL) { printf("Error allocating mem\n"); }
		//   else{printf("t[%d] = %p\n", i, t[i]);}
	}
	return t;
}

void Mixer::writeInputsToBuffer(void* outputBuffer, bool stereo, bool mod) {

	sample_t* out = (sample_t*)outputBuffer;
	sample_t** inputBuffer = allocateBuffer(this->numInputs, FRAMES_PER_BUFFER);
	
	for (int i = 0; i < this->numInputs; i++) {
		if (this->inputs[i]->isOn) {
			this->inputs[i]->output((void*)inputBuffer[i], false, mod);
		}
		else {
			silence((void*)inputBuffer[i], false);
		}
	}
	//write sound data to buffer
	for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
		sample_t data = 0;
		for (int j = 0; j < this->numInputs; j++) {
			data += inputBuffer[j][i] / this->numInputs;
		}
		*out++ = data; //left
		if (stereo) {
			*out++ = data; //right
		}
	}

	deleteBuffer(inputBuffer, this->numInputs);
}