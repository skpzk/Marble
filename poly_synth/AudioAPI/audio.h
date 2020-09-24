#ifndef audio_h_
#define audio_h_

#include "AudioConstants.h"

#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "portaudio.h"
#include "MidiUtils.h"

#include "../AudioLib/Mixer.h"

typedef struct{
    sample_t sine[TABLE_SIZE];
    float left_phase;
    float right_phase;
    unsigned int framesToGo;
    float midiNote = 60;
	Mixer* mixer;
}paTestData;

int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData );


class Audio{
	public:
		void setVolume(int);
		static void* run(void*);
		static void* test(void*);
		int start();
		int stop();
		int getVolume();
		paTestData          data;
		void addInputFromMixer(Mixer*);
	private:
		PaStream*           stream;
		PaStreamParameters  outputParameters;
		PaError             err;
		
		PaTime              streamOpened;
		
		PaError startStream();
		PaError stopStream();
		int volume = 1;
		bool running;	
};

#endif