#ifndef va_h_
#define va_h_

#include "../AudioAPI/AudioConstants.h"
#include "Oscs.h"
#include "Env.h"

class Va{
	private:
		float volume = 1;
		bool has_env=false;
		bool has_osc=false;
		Osc* osc;
		Env* env;
		sample_t bufOsc[FRAMES_PER_BUFFER];
		sample_t bufEnv[FRAMES_PER_BUFFER];
		void init(sample_t*);
	public:
		void setVolume(float);
		void output(void*);
		void setOsc(Osc*);
		void setEnv(Env*);
};

#endif
