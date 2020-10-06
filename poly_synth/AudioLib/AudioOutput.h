#ifndef audiooutput_h_
#define audiooutput_h_

#include "../AudioAPI/AudioConstants.h"
class AudioOutput;
#include "AudioObject.h"


enum typeOfOutput{audioobject_out, nooutput};

class AudioOutput{
	public:
        AudioOutput();
        AudioOutput(AudioObject*);
		void writeToBuffer(void*, bool);
		void writeToBuffer(void*, bool, bool);
    private:
        AudioObject* audioObject=NULL;
        typeOfOutput outputType = nooutput;
        void writeSilence(void*, bool);
};

#endif
