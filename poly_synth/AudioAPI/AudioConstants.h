#ifndef audioconstants_h_
#define audioconstants_h_




#define NUM_SECONDS   (8)
#define SAMPLE_RATE   (44100)
#define TABLE_SIZE    (1600)
#define FRAMES_PER_BUFFER (256)
#define VOICES (8)

/*#define TEST_UNSIGNED (0)

#if TEST_UNSIGNED
#define TEST_FORMAT   paUInt16
typedef unsigned char sample_t;
#define SILENCE       ((sample_t)0x80)
#else*/
#define FORMAT   paInt16
typedef short int          sample_t;
#define SILENCE       ((sample_t)0x00)
#define MAX       ((sample_t)1<<14)
//#endif

#ifndef M_PI
#define M_PI (3.14159265)
#endif

#endif