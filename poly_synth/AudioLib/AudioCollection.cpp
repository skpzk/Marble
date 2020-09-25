#include "AudioCollection.h"
#include <stdio.h>
#include <stdlib.h>
/*
int AudioCollection::addElement(Osc* element) {
	Osc *osc = element;
	int N = this->numOfOscs;
	if(N==0){
		this->oscs = new Osc*[N+1];
		this->oscs[N] = osc;
		this->numOfElements++;
		this->numOfOscs++;
		N++;
	}else{
		Osc** tmp = new Osc*[N];
		for(int i=0; i < N; i++){
			tmp[i] = this->oscs[i];
		}
		this->numOfElements++;
		N++;
		this->numOfOscs++;
		this->oscs = new Osc*[N];
		for(int i=0; i<(N-1); i++){
			this->oscs[i] = tmp[i];
		}
		this->oscs[N-1] = osc;
	}
	return 0;
}

int AudioCollection::addElement(Va* element) {
	Va *va = element;
	int N = this->numOfVas;
	if(N==0){
		this->vas = new Va*[N+1];
		this->vas[N] = va;
		this->numOfElements++;
		this->numOfVas++;
		N++;
	}else{
		Va** tmp = new Va*[N];
		for(int i=0; i < N; i++){
			tmp[i] = this->vas[i];
		}
		this->numOfElements++;
		N++;
		this->numOfVas++;
		this->vas = new Va*[N];
		for(int i=0; i<(N-1); i++){
			this->vas[i] = tmp[i];
		}
		this->vas[N-1] = va;
	}
	return 0;
}*/

int AudioCollection::addElement(Va* element) {
	Va *va = element;
	int N = this->numOfVas;
	this->vas[N] = va;
	this->numOfElements++;
	this->numOfVas++;
	return 0;
}

/*
void AudioCollection::listElements(){
	int i;
	void* p;
	for(i=0; i<this->numOfOscs; i++){
		this->oscs[i]->output(p);
	}
	for(i=0; i<this->numOfVas; i++){
		this->vas[i]->output(p);
	}
}*/

sample_t** allocateBuffer(int a, int frames){
	sample_t ** t = new sample_t*[a];
	  for(int i = 0; i < a; i++)
	  {
	      t[i] = new sample_t[frames];
		  if(t[i] == NULL){printf("Error allocating mem\n");}
		//   else{printf("t[%d] = %p\n", i, t[i]);}
	  }
  return t;
}

void AudioCollection::output(void* outputBuffer, bool Stereo){
	// printf("Getting data from AudioCollection\nnum elts = %d\n", this->numOfElements);
	// printf("num vas = %d\nnum oscs = %d\n", this->numOfVas, this->numOfOscs);
	sample_t *out = (sample_t*)outputBuffer;
	int numElements = this->numOfElements;
	sample_t ** inputBuffer = allocateBuffer(numElements, FRAMES_PER_BUFFER);
	int i, j;
	//get sound data
	// for(i=0; i<this->numOfOscs; i++){
	// 	this->oscs[i]->output((void*) inputBuffer[i]);
	// }
	for(i=0; i<this->numOfVas; i++){
		this->vas[i]->output((void*) inputBuffer[i]);// + this->numOfOscs]);
	}
	//write sound data to buffer
	// printf("AudioCollection : nbOscs = %d, nbElements = %d\n", this->numOfOscs, this->numOfElements);
	for(i=0; i<FRAMES_PER_BUFFER; i++){
		sample_t data = 0;
		for(j=0; j<numElements; j++){
			data += inputBuffer[j][i] / this->numOfElements;
			//printf("Data = %d\n", data);
		}
		*out++ = data; //left
		if(Stereo){
			*out++ = data; //right
		}
	}
	
	for(j=0; j<numElements; j++){
			delete[] inputBuffer[j];
	}
	delete[] inputBuffer;
	inputBuffer = NULL;
	
}
/*
int main() {
	printf("Audio Collection\n");
	Osc osc;
	Va va;
	AudioCollection coll;
	coll.addElement(&osc);
	coll.addElement(&va);
	coll.listElements();
}*/
