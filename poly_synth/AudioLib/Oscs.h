#ifndef oscs_h_
#define oscs_h_

#include "../AudioAPI/AudioConstants.h"
#include "../AudioAPI/MidiUtils.h"

#include "Wave.h"
class Osc;
class VOsc;
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
		void output(void*, bool, bool);
		AudioOutput* audioOutput;
		// int type=1;
		Osc(float);
};


class VOsc {
	private:
		float freq;
		float volume;
		float phase;
		float phaseIncrement;
		float interpFactor;
		WaveShape* waveshape;
		sample_t wave_output[TABLE_SIZE];
		void updatePhaseIncrement();
		bool has_input=false;
		AudioOutput* input;

	public:
		VOsc(float);
		void selectWaveShape(int);
		void interpolate();
		void setInterpolation(float);
		void setVolume(float);
		void setFreq(float);
		float getNote();
		void setNote(float);
		void output(void*, bool, bool);
		AudioOutput* audioOutput;
		void setInput(AudioOutput*);
		// int type = 1;
	};

#endif
