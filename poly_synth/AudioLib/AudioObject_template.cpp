/*

// AudioObject.h
#ifndef audioobject_h_
#define audioobject_h_

#include "../AudioAPI/AudioConstants.h"
#include "../Utils/SignalUtils.h" //defines initBuffer

class AudioObject; //forward declaration of AudioObject
#include "AudioOutput.h"

class AudioObject{
   public:
        AudioOutput* audioOutput=NULL;
        AudioObject();
        void setInput(AudioOutput*);
        void output(void*, bool);
   private:
		bool has_input=false;
		AudioOutput* input;
};
#endif



//AudioObject.cpp
#include "AudioObject.h"

AudioObject::AudioObject(){
   this->audioOutput = new AudioOutput(this);
}

void AudioObject::setInput(AudioOutput* audioOutput){
    if(!this->has_input){
        this->input = audioOutput;
        this->has_input = true;
    }
}
void AudioObject::output(void* outputBuffer, bool stereo){
    sample_t *out = (sample_t*)outputBuffer;

    sample_t in[FRAMES_PER_BUFFER];

    if(this->has_input){
        this->input->writeToBuffer(in, false);
    }else{
        initBuffer(in, FRAMES_PER_BUFFER, 0);
    }

    for(int i=0; i<(FRAMES_PER_BUFFER); i++){
        *out++ = data;  // mono/left
        if(stereo){
	        *out++ = data;// right
        }
        
    }
}


//AudioOutput.h
//what to add :

//after "class AudioOutput;" :
#include "AudioObject.h"

//add a new type of output
enum typeOfOutput{audioobject_out};

class AudioOutput{
	public:
        AudioOutput(AudioObject*);
    private:
        AudioObject* audioObject=NULL;
};



//AudioOutput.cpp
//what to add :

#include "AudioOutput.h"

//add new constructor
AudioOutput::AudioOutput(AudioObject* audioObject){
    this->audioObject = audioObject;
    this->outputType = audioobject_out;
}

//add new case for new outputType
void AudioOutput::writeToBuffer(void* outputBuffer, bool stereo){
    switch(this->outputType){
        case AudioObject_out:
            this->audioObject->output(outputBuffer, stereo);
            break;
    }
}
*/