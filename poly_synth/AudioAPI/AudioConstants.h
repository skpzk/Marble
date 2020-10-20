#ifndef audioconstants_h_
#define audioconstants_h_

#define SAMPLE_RATE         (44100)
#define TABLE_SIZE          (3200)
#define MAX_TABLE_NUM       (4)
#define FRAMES_PER_BUFFER   (512)
#define VOICES              (16)

#define FORMAT      paInt32
typedef int   sample_t;
#define SILENCE     ((sample_t)0x00)
#define MAX         ((sample_t)1<<30)

#define SINE     (0)
#define SAW      (1)
#define TRIANGLE (2)
#define SQUARE   (3)

enum modType : unsigned char { envelope, lfo };
enum modValue : unsigned char { amplitude, interpolation };

enum setterType : unsigned char { A, D, S, R, fc, Q, interp, fold, waveShape };

#include "../Utils/DebugUtils.h"

#endif