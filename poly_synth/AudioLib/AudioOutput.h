#ifndef audiooutput_h_
#define audiooutput_h_

#include "../AudioAPI/AudioConstants.h"
class AudioOutput;
#include "Oscs.h"
#include "Filter.h"
#include "Vca.h"
#include "Mixer.h"

enum typeOfOutput{osc_out, vosc_out, mixer_out, filter_out, vca_out, nooutput};

class AudioOutput{
	public:
        AudioOutput();
        AudioOutput(Osc*);
        AudioOutput(VOsc*);
        AudioOutput(BiquadFilter*);
        AudioOutput(Vca*);
        AudioOutput(Mixer*);
		void writeToBuffer(void*, bool);
    private:
        Osc* osc=NULL;
        VOsc* vosc = NULL;
        BiquadFilter* filter=NULL;
        Vca* vca=NULL;
        Mixer* mixer=NULL;
        typeOfOutput outputType = nooutput;
        void writeSilence(void*, bool);
};

#endif
