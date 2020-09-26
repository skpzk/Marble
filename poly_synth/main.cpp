#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <csignal> // used to stop the main loop

#include "AudioAPI/Midi.h"
#include "AudioAPI/audio.h"
#include "AudioLib/Voices.h"
#include "Utils/wait.h" //used to wait for X time intervals. (sleep_for is defined here)

using namespace std;

bool flagLoop = true;
void raiseFlag(int param)
{
    flagLoop = false;
}

int main(){

	signal(SIGINT, raiseFlag);

	Voices voices(VOICES); //the Voices class manages polyphony

	Midi midi(&voices); //note on/off events are send to the Voices class
	midi.open(-1); //use a negative number to display an interactive port selection
	//or use directly the port number

	Audio audio;
	audio.start();

	audio.addInputFromMixer(&voices.mixer); // the audio class gets audio data from voices.mixer

	while(flagLoop){
		sleep_for(100ms);
		voices.update_status(); //update the order in which notes are played (not the best way to call it, could be called by a note off event)
	}
	printf("Loop interrupted\n");
	midi.close();
	audio.stop();

}