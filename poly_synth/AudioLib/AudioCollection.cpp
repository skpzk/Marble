#include "AudioCollection.h"
#include <stdio.h>
#include <stdlib.h>

int AudioCollection::addElement(Va* element) {
	Va *va = element;
	int N = this->numOfVas;
	this->vas[N] = va;
	this->numOfElements++;
	this->numOfVas++;
	return 0;
}

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

void deleteBuffer(sample_t ** inputBuffer, int a){
	for(int j=0; j<a; j++){
		delete[] inputBuffer[j];
	}
	delete[] inputBuffer;
	inputBuffer = NULL;
}

void AudioCollection::output(void* outputBuffer, bool Stereo){
	// printf("Getting data from AudioCollection\nnum elts = %d\n", this->numOfElements);
	// printf("num vas = %d\nnum oscs = %d\n", this->numOfVas, this->numOfOscs);
	sample_t *out = (sample_t*)outputBuffer;
	int numElements = this->numOfElements;
	sample_t ** inputBuffer = allocateBuffer(numElements, FRAMES_PER_BUFFER);
	int i, j;
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
	deleteBuffer(inputBuffer, numElements);
	
}
