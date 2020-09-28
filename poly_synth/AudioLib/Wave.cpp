#include "Wave.h"

Wave::Wave(int type) {
    switch (type) {
    case 0: //sine wave
        this->sine();
        break;

    case 1: //saw wave
        this->saw();
        break;

    case 2: //tri wave
        this->tri();
        break;

    case 3: //square wave
        this->square();
        break;
    }
};

void Wave::sine(){
  for(int i=0; i<TABLE_SIZE; i++ )
  {
      this->wave[i] = SILENCE + (sample_t) (this->maxValue * sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2.));
  }
}

void Wave::square(){
  int middle = (int) (TABLE_SIZE / 2);
  for(int i=0; i<middle; i++ )
  {
      this->wave[i] = SILENCE + (sample_t) (this->maxValue);
  }
  for(int i=middle; i<TABLE_SIZE; i++ )
  {
      this->wave[i] = SILENCE - (sample_t) (this->maxValue);
  }
}

void Wave::tri(){
  int middle = (int) (TABLE_SIZE / 2);
  for(int i=0; i<middle; i++ )
  {
      this->wave[i] = SILENCE + (sample_t) (this->maxValue - 2. * this->maxValue
        * (float) i / middle);
  }
  for(int i=middle; i<TABLE_SIZE; i++ )
  {
      this->wave[i] = SILENCE + (sample_t) (- this->maxValue + 2. * this->maxValue
        * (float) (i - middle) / middle);
  }
}

void Wave::saw(){
  for(int i=0; i<TABLE_SIZE; i++ )
  {
      this->wave[i] = SILENCE + (sample_t) (this->maxValue - 2. * this->maxValue
        * (float) i / TABLE_SIZE);
  }
}