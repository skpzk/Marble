#ifndef Modulation_h
#define Modulation_h

#include "../AudioAPI/AudioConstants.h"
#include "AudioObject.h"
#include "Env.h"
#include "Oscs.h"
class Modulator;
#include "SynthChannel.h"

class Modulator {
public:
	// Modulating devices
	Env* env;
	Osc* lfOsc;
	ModScalar* amp;
	ModScalar* interp;

	Modulator(SynthChannel*);
	void modulate(modType, modValue);
	void setADSR(float* adsr);
	void on();
	void off();
	bool isActive();
	void set();

private:
	void applyEnv(modValue);
	void applyLfo(modValue);
};

#endif