#ifndef oscs_h_
#define oscs_h_

#include "../AudioAPI/AudioConstants.h"
#include "../AudioAPI/MidiUtils.h"

#include "Wave.h"
class Osc;
#include "AudioOutput.h"

class Osc{
	private:
		float freq;
		float volume;
		float phase;
		float phaseIncrement;
		void updatePhaseIncrement();
		Wave wave = Wave(2);

	public:
		void setVolume(float);
		void setFreq(float);
		float getNote();
		void setNote(float);
		void setWave(char);
		void output(void*, bool);
		AudioOutput* audioOutput;
		int type=1;
		Osc(float);
};

#endif
