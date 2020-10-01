#include "Wave.h"

// WAVE CLASS

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
}

Wave::Wave()
{
    this->sine();
}

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


// WAVETABLE CLASS

WaveShape::WaveShape()
{
    this->numWaves = 0;
    this->waveforms = new sample_t* [MAX_TABLE_NUM];
}

void WaveShape::selectWaveShape(int type) {
    switch (type) {
    case 0:
        this->basicShapes();
        break;
    }
}

void WaveShape::basicShapes()
{
    this->addWave(new Wave(SINE));
    this->addWave(new Wave(SQUARE));
    this->addWave(new Wave(TRIANGLE));
    this->addWave(new Wave(SAW));
}

void WaveShape::addWave(Wave* wave)
{
    if (this->numWaves < MAX_TABLE_NUM + 1) {
        this->waveforms[this->numWaves] = wave->wave;
        ++this->numWaves;
        // cout <<dline()<<"num waves : "<<this->numWaves<<"\n";s
    }
    else {
        printf("Maximum number of waveforms exceeded");
    }
}