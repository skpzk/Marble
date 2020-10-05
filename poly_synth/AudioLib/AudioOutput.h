#ifndef audiooutput_h_
#define audiooutput_h_

#include "../AudioAPI/AudioConstants.h"
class AudioOutput;
#include "Oscs.h"
#include "Filter.h"
#include "Vca.h"
#include "Mixer.h"
#include "Env.h"
#include "WaveFolder.h"

enum typeOfOutput{osc_out, vosc_out, mixer_out, filter_out, 
                  vca_out, env_out, wavefolder_out,nooutput};

class AudioOutput{
	public:
        AudioOutput();
        AudioOutput(Osc*);
        AudioOutput(VOsc*);
        AudioOutput(BiquadFilter*);
        AudioOutput(Vca*);
        AudioOutput(Mixer*);
        AudioOutput(Env*);
        AudioOutput(WaveFolder*);
		void writeToBuffer(void*, bool);
		void writeToBuffer(void*, bool, bool);
    private:
        Osc* osc=NULL;
        VOsc* vosc = NULL;
        BiquadFilter* filter=NULL;
        Vca* vca=NULL;
        Mixer* mixer=NULL;
        Env* env=NULL;
        WaveFolder* waveFolder=NULL;
        typeOfOutput outputType = nooutput;
        void writeSilence(void*, bool);
};

#endif
