#ifndef wave_h_
#define wave_h_
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include "../AudioAPI/AudioConstants.h"
#include <math.h>

class Wave{
  public:
    Wave(int);
    sample_t wave[TABLE_SIZE];
  private:
    sample_t maxValue = MAX;
    void sine();
    void tri();
    void square();
    void saw();
};

#endif