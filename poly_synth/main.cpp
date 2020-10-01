#include <stdio.h>
#include <csignal> // used to stop the main loop

#include "Utils/wait.h" //used to wait for X time intervals. (sleep_for is defined here)

#include "AudioLib/AudioPatch.h"

using namespace std;

bool flagLoop = true;
void raiseFlag(int param)
{
    flagLoop = false;
}

int main() {

	signal(SIGINT, raiseFlag);

	AudioPatch audioPatch;

	while(flagLoop){
		sleep_for(100ms);
		audioPatch.updateVoicesStatus(); //update the order in which notes are played (not the best way to call it, could be called by a note off event)
	}
	printf("Loop interrupted\n");
	audioPatch.stop();

}