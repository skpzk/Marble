#ifndef vca_h_
#define vca_h_

#include "../AudioAPI/AudioConstants.h"
#include "Oscs.h"
#include "Env.h"

class Vca{
	private:
		float volume = 1;
		bool has_env=false;
		bool has_osc=false;
		Osc* osc;
		Env* env;
		sample_t bufOsc[FRAMES_PER_BUFFER];
		sample_t bufEnv[FRAMES_PER_BUFFER];
		void init(sample_t*, int);
	public:
		void setVolume(float);
		void output(void*);
		void setOsc(Osc*);
		void setEnv(Env*);
};

#endif
