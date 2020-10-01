#include "AudioOutput.h"

AudioOutput::AudioOutput(Osc* osc){
    this->osc = osc;
    this->outputType = osc_out;
}

AudioOutput::AudioOutput(BiquadFilter* filter){
    this->filter = filter;
    this->outputType = filter_out;
}

AudioOutput::AudioOutput(Vca* vca){
    this->vca = vca;
    this->outputType = vca_out;
}

AudioOutput::AudioOutput(Mixer* mixer){
    this->mixer = mixer;
    this->outputType = mixer_out;
}

AudioOutput::AudioOutput(){
    this->outputType = nooutput;
}

void AudioOutput::writeToBuffer(void* outputBuffer, bool stereo){
    switch(this->outputType){
        case osc_out:
            this->osc->output(outputBuffer, stereo);
            break;
        case filter_out:
            this->filter->output(outputBuffer, stereo);
            break;
        case mixer_out:
            //printf("get output from Mixer\n");
            this->mixer->output(outputBuffer, stereo);
            break;
        case vca_out:
            this->vca->output(outputBuffer, stereo);
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
