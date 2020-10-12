#include "AudioOutput.h"

AudioOutput::AudioOutput(AudioObject* audioObject){
    this->audioObject = audioObject;
    this->outputType = audioobject_out;
}

AudioOutput::AudioOutput(){
    this->outputType = nooutput;
}

void AudioOutput::writeToBuffer(void* outputBuffer, bool stereo){
    this->writeToBuffer(outputBuffer, stereo, false);
}

void AudioOutput::writeToBuffer(void* outputBuffer, bool stereo, bool modification){
    //if the output is for modification purposes, don't modify object parameters
    //e.g. output the wave of an osc without updating its phase
    //as of now only implemented in env
    switch(this->outputType){
        case audioobject_out:
            this->audioObject->output(outputBuffer, stereo, modification);
            break;
        case nooutput:
            printf("No output\n");
            this->writeSilence(outputBuffer, stereo);
            break;
    }
}

void AudioOutput::writeSilence(void* outputBuffer, bool stereo){
    sample_t *out = (sample_t*)outputBuffer;

    for(int i=0; i<FRAMES_PER_BUFFER; i++){
        *out++ = 0;
        if(stereo){
	        *out++ = 0;// right
        }
    }
}
