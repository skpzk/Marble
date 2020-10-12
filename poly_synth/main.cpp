#include <stdio.h>
#include <csignal> // used to stop the main loop

#include "Utils/wait.h" //used to wait for X time intervals. (sleep_for is defined here)

#include "AudioLib/AudioPatch.h"
#include <QApplication>
#include "Qt/plot.h"

using namespace std;

bool flagLoop = true;
void raiseFlag(int param)
{
    flagLoop = false;
}

int main(int argc, char **argv) {

	QApplication app( argc, argv );

	signal(SIGINT, raiseFlag);

	AudioPatch audioPatch;

	Plot plot;
	plot.setTitle("Audio Output");
	plot.setInput(audioPatch.audioOutput);
	plot.show();
	app.exec();

	while(flagLoop){
		sleep_for(100ms);
	}
	printf("Loop interrupted\n");
	audioPatch.stop();

	return 0;
}