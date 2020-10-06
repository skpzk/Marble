#ifndef audioobject_h_
#define audioobject_h_
#include <iostream>
#include "../AudioAPI/AudioConstants.h"
class AudioObject;
#include "AudioOutput.h"


using namespace::std;


class AudioObject{
   public:
        AudioOutput* audioOutput=NULL;
        AudioObject();
        void setInput(AudioOutput*);
        virtual void output(void*, bool, bool);
   protected:
		bool has_input=false;
		AudioOutput* input;
};
#endif
