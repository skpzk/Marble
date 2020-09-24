#ifndef midi_h_
#define midi_h_

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include "../AudioLib/Voices.h"

void usage( void );

void mycallback( double deltatime, std::vector< unsigned char > *message, void */*userData*/ );

bool chooseMidiPort( RtMidiIn *rtmidi );

class Midi{
	public:
		int open(int);
		int close();
        
		Midi(Voices* voices){
			this->voices = voices;
		}
		//void mycallback( double deltatime, std::vector< unsigned char > *message, void *);
	private:
		Voices* voices;
		RtMidiIn *midiin;
		bool chooseMidiPort();
};


#endif