#ifndef audioconstants_h_
#define audioconstants_h_

#define SAMPLE_RATE         (44100)
#define TABLE_SIZE          (1600)
#define FRAMES_PER_BUFFER   (256)
#define VOICES              (8)

#define FORMAT      paInt16
typedef short int   sample_t;
#define SILENCE     ((sample_t)0x00)
#define MAX         ((sample_t)1<<14)

#endif