#ifndef audio_h_
#define audio_h_

#include "AudioConstants.h"

#include <stdio.h>
#include <math.h>
#include "portaudio.h"

#include "../AudioLib/Mixer.h"
#include "../AudioLib/AudioOutput.h"

typedef struct{
	AudioOutput* output=NULL;
}paData;

int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );


class Audio{
	public:
		int start();
		int stop();

		paData          data;
		void setInput(AudioOutput*);
	private:
		PaStream*           stream;
		PaStreamParameters  outputParameters;
		PaError             err;		
		
		PaError startStream();
		PaError stopStream();
		PaError error();

		bool running;	
};

#endif