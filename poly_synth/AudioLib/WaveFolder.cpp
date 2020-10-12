#include "WaveFolder.h"

WaveFolder::WaveFolder(){
   this->audioOutput = new AudioOutput(this);
}

// void WaveFolder::setInput(AudioOutput* audioOutput){
//     if(!this->has_input){
//         this->input = audioOutput;
//         this->has_input = true;
//     }
// }

//condition to avoid out of range signal :
//Max - limit < 2 * limit, ie. limit > MAX/3
void WaveFolder::setFoldingLimit(float limit){
    this->limit = MAX / 3 + limit / 127. * 2. * MAX / 3.;
}

float WaveFolder::computeFold(float data){
    if(data > this->limit){
        return  (2 * this->limit - data) * MAX/this->limit;
    }else if(data < (-1*this->limit)){
        return (-2 * this->limit - data) * MAX/this->limit;
    }else{
        return data * MAX/this->limit;
    }
}

void WaveFolder::output(void* outputBuffer, bool stereo, bool mod){
    sample_t *out = (sample_t*)outputBuffer;

    sample_t in[FRAMES_PER_BUFFER];

    if(this->has_input){
        this->input->writeToBuffer(in, false, mod);
    }else{
        initBuffer(in, FRAMES_PER_BUFFER, 0);
    }

    float data=0;

    for(int i=0; i<(FRAMES_PER_BUFFER); i++){
        data = this->computeFold(in[i]);
        *out++ = data;  // mono/left
        if(stereo){
	        *out++ = data;// right
        }
        
    }
}