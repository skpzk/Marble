#ifndef oscs_h_
#define oscs_h_

#include "../AudioAPI/AudioConstants.h"
#include "../AudioAPI/MidiUtils.h"
#include "../Utils/SignalUtils.h"
#include "Wave.h"
#include "AudioObject.h"
#include "ModScalar.h"


class Osc : public AudioObject {
private:
	float freq;
	float phase;
	float phaseIncrement;
	float interpFactor; // Static interpolation value
	//static inline WaveShape commonWaveshape;
	WaveShape* waveshape;
	sample_t wave_output[TABLE_SIZE];
	void updatePhaseIncrement();

public:
	ModScalar amplitude;
	ModScalar interpModulation; // Modulable interpolation value that's added to the static value

	Osc(float);
	void selectWaveShape(int);
	void interpolate();
	void setInterpolation(float);
	void addInterpolation(float);
	void setAmplitude(float);
	void setFreq(float);
	float getNote();
	void setNote(float);
	void output(void*, bool, bool);
};

#endif
