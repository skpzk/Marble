#ifndef oscs_h_
#define oscs_h_

#include "../AudioAPI/AudioConstants.h"
#include "Wave.h"
#include "../AudioAPI/MidiUtils.h"

class Osc{
	private:
		float freq;
		float volume;
		float phase;
		float phaseIncrement;
		void updatePhaseIncrement();
		Wave wave = Wave(2);

		//void writeWave(sample_t*);

	public:
				
		void setVolume(float);
		void setFreq(float);
		float getNote();
		void setNote(float);
		void setWave(char);
		void output(void*);
		int type=1;
		Osc(float freq){
			this->setFreq(freq);
			this->setVolume(1);
		}
};

#endif
