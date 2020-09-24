#ifndef mixer_h_
#define mixer_h_

#include "../AudioAPI/AudioConstants.h"
#include "Oscs.h"
#include "AudioCollection.h"

class Mixer{
	public:
		void addInput(Osc*);
		void addInput(Va*);
		void removeInput(); //not implemented
		void output(void*, int, bool);
		int test = 17;
	private:
		int numInputs = 0;
		AudioCollection inputs;
};

#endif
