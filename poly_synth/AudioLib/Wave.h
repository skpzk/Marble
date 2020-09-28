#ifndef wave_h_
#define wave_h_
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include "../AudioAPI/AudioConstants.h"
#include <math.h>

class Wave{
  public:
    sample_t wave[TABLE_SIZE];
    Wave(int type){
      switch(type){
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
  private:
    sample_t maxValue = MAX;
    void sine();
    void tri();
    void square();
    void saw();
};



#endif
