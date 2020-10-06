#ifndef wavefolder_h_
#define wavefolder_h_

#include "../AudioAPI/AudioConstants.h"
#include "../Utils/SignalUtils.h" //defines initBuffer

class WaveFolder; //forward declaration of WaveFolder
#include "AudioOutput.h"

//wavefolder applies a limit to the wave and folds the out of range data inside of the range
class WaveFolder{
   public:
          AudioOutput* audioOutput=NULL;
          WaveFolder();
          void setInput(AudioOutput*);
          void output(void*, bool, bool);
          void setFoldingLimit(float);
   private:
          bool has_input=false;
          AudioOutput* input;
          float computeFold(float);
          float limit=MAX;
};

#endif