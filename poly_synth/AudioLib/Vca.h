#ifndef vca_h_
#define vca_h_

#include "../AudioAPI/AudioConstants.h"
#include "../Utils/SignalUtils.h"
// class Vca;
#include "Oscs.h"
#include "Env.h"
#include "AudioOutput.h"
#include "AudioObject.h"

class Vca : public AudioObject{
private:
	float volume = 1;
	bool has_env = false;
	// bool has_input = false;
	AudioOutput* env;
	// AudioOutput* input;

	sample_t bufInput[FRAMES_PER_BUFFER];
	sample_t bufEnv[FRAMES_PER_BUFFER];
public:
	void setVolume(float);
	void output(void*, bool, bool);
	// AudioOutput* audioOutput;
	// void setInput(AudioOutput*);
	void setEnv(AudioOutput*);
	Vca();
};

#endif