#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <csignal> // used to stop the main loop

#include "AudioAPI/Midi.h"
#include "AudioAPI/audio.h"
#include "AudioLib/Voices.h"
#include "Utils/wait.h" //used to wait for X time intervals. (sleep_for is defined here)

#include "AudioLib/AudioOutput.h"

using namespace std;

bool flagLoop = true;
void raiseFlag(int param)
{
    flagLoop = false;
}

int main(){

	signal(SIGINT, raiseFlag);

	Voices voices(VOICES); //the Voices class manages polyphony
	voices.setWaveform(3); //0: sine; 1: saw; 2: tri; 3: square
	voices.setAmplitude(1);
	voices.setADSR(30, 10, 100, 80);

	Midi midi(&voices); //note on/off events are send to the Voices class
	midi.open(0); //use a negative number to display an interactive port selection
	//or use directly the port number

	Audio audio;

	BiquadFilter filter;
	filter.setInput(voices.mixer.audioOutput); // filter gets its input from mixer

	filter.setFc(330.); //set the cutoff frequency
	filter.setMidiFc(60.); //same with midi note number
	filter.setQ(2.); //set the resonance (filter is a resonant low-pass)

	audio.setInput(filter.audioOutput); // Now audio class gets a generic AudioOutput as input

	audio.start(); //start should be called after setInput

	while(flagLoop){
		sleep_for(100ms);
		voices.update_status(); //update the order in which notes are played (not the best way to call it, could be called by a note off event)
	}
	printf("Loop interrupted\n");
	midi.close();
	audio.stop();

}