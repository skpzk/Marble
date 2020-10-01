#ifndef midi_h_
#define midi_h_

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"

class Midi;
#include "../AudioLib/AudioPatch.h"

void usage( void );

void mycallback( double deltatime, std::vector< unsigned char > *message, void */*userData*/ );

bool chooseMidiPort( RtMidiIn *rtmidi );

class Midi{
	public:
		int open(int);
		int close();
        
		Midi(AudioPatch* patch){
			this->patch = patch;
		}
	private:
		AudioPatch* patch;
		RtMidiIn *midiin;
		bool chooseMidiPort();
};


#endif