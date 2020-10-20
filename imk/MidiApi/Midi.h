#ifndef midi_h_
#define midi_h_

#include <iostream>
#include <cstdlib>
#include "RtMidi.h"

void mycallback( double deltatime, std::vector< unsigned char > *message, void */*userData*/ );

class Midi{
	public:
		int open(int);
		int close();

		void noteOn(int);
		void noteOff(int);

	private:
		RtMidiOut *midiout;
		bool chooseMidiPort();
};


#endif