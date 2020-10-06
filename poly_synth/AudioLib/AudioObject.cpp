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
void AudioObject::output(void* outputBuffer, bool stereo, bool mod){
    printf("Getting data from AudioObject, something must be wrong\n");
    printf("This method should be overridden by objects that inherit from AudioObject\n");
}
