#ifndef midi_h_
#define midi_h_

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"

#include "../Gui/state.h"


void usage( void );

void mycallback( double deltatime, std::vector< unsigned char > *message, void */*userData*/ );

bool chooseMidiPort( RtMidiIn *rtmidi );

class Midi{
	public:
		int open(int);
		int close();
        
		Midi(){

		}
	private:

		RtMidiIn *midiin;
		bool chooseMidiPort();

		State* state = StateParameter::state;
};


#endif