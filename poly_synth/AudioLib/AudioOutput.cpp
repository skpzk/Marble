#include "AudioOutput.h"

AudioOutput::AudioOutput(Osc* osc){
    this->osc = osc;
    this->outputType = osc_out;
}

AudioOutput::AudioOutput(VOsc* vosc) {
    this->vosc = vosc;
    this->outputType = vosc_out;
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

AudioOutput::AudioOutput(Env* env){
    this->env = env;
    this->outputType = env_out;
}

AudioOutput::AudioOutput(WaveFolder* waveFolder){
    this->waveFolder = waveFolder;
    this->outputType = wavefolder_out;
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
        case osc_out:
            this->osc->output(outputBuffer, stereo, modification);
            break;
        case vosc_out:
            this->vosc->output(outputBuffer, stereo, modification);
            break;
        case filter_out:
            this->filter->output(outputBuffer, stereo, modification);
            break;
        case mixer_out:
            //printf("get output from Mixer\n");
            this->mixer->output(outputBuffer, stereo, modification);
            break;
        case vca_out:
            this->vca->output(outputBuffer, stereo, modification);
            break;
        case env_out:
            this->env->output(outputBuffer, stereo, modification);
            break;
        case wavefolder_out:
            this->waveFolder->output(outputBuffer, stereo, modification);
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
