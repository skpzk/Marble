#ifndef wavefolder_h_
#define wavefolder_h_

#include "../AudioAPI/AudioConstants.h"
#include "../Utils/SignalUtils.h" //defines initBuffer

// class WaveFolder; //forward declaration of WaveFolder
#include "AudioObject.h"

//wavefolder applies a limit to the wave and folds the out of range data inside of the range
class WaveFolder : public AudioObject{
   public:
          void output(void*, bool, bool);
          void setFoldingLimit(float);
   private:
          float computeFold(float);
          float limit=MAX;
};

#endif