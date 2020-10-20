#include "AudioObject.h"

void AudioObject::on()
{
    this->isOn = true;
}

void AudioObject::off()
{
    this->isOn = false;
}

void AudioObject::setInput(AudioObject* input){
    if(!this->has_input){
        this->input = input;
        this->has_input = true;
    }
}

void AudioObject::output(void* outputBuffer, bool stereo, bool mod){
    printf("Getting data from AudioObject, something must be wrong\n");
    printf("This method should be overridden by objects that inherit from AudioObject\n");
}
