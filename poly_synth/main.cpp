#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <csignal>


#include "AudioAPI/Midi.h"
#include "AudioAPI/audio.h"

#include "AudioLib/Voices.h"

#include <pthread.h> //multithreading
#include "Utils/wait.h" //used to wait for X time intervals. (sleep_for is defined here)

using namespace std;

bool flagLoop = true;
void raiseFlag(int param)
{
    flagLoop = false;
}

int main(){
	pthread_t threads[1];
	int rc;
	int i;

	signal(SIGINT, raiseFlag);
	
	printf("test\n");

	Voices voices(8);

	Midi midi(&voices);
	midi.open(1);

	Audio audio;
	printf("voices.mixer.test = %d\n", voices.mixer.test);
	//
	audio.start();

	audio.addInputFromMixer(&voices.mixer);

	while(flagLoop){
		sleep_for(100ms);
		voices.update_status();
	}
	printf("Loop interrupted\n");
	midi.close();
	audio.stop();

}