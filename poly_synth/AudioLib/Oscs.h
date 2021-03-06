#ifndef oscs_h_
#define oscs_h_

#include "../AudioAPI/AudioConstants.h"
#include "../AudioAPI/MidiUtils.h"
#include "../Utils/SignalUtils.h"


#include "Wave.h"
#include "AudioOutput.h"
#include "AudioObject.h"


class Osc : public AudioObject{
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
		Osc(float);
};


class VOsc : public AudioObject {
	private:
		float freq;
		float volume;
		float phase;
		float phaseIncrement;
		float interpFactor; // number used to compute the interpolation (interpValue + mod)
		float interpValue; // set by CC
		static inline WaveShape commonWaveshape;
		WaveShape* waveshape;
		sample_t wave_output[TABLE_SIZE];
		void updatePhaseIncrement();

	public:
		VOsc(float);
		void selectWaveShape(int);
		void interpolate();
		void setInterpolation(float);
		void addInterpolation(float);
		void setVolume(float);
		void setFreq(float);
		float getNote();
		void setNote(float);
		void output(void*, bool, bool);
	};

#endif
