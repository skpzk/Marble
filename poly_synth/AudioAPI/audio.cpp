#include "audio.h"
#include "../Utils/wait.h"


/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    paTestData *data = (paTestData*)userData;
    sample_t *out = (sample_t*)outputBuffer;
    int i;
    int framesToCalc;
    int finished = 0;
    (void) inputBuffer; /* Prevent unused variable warnings. */

	data->mixer->output(out, framesPerBuffer, true);
    return finished;
}

void* Audio::run(void* p){
	Audio *audio = (Audio*)p;
	int i = 0;
	while(audio->running){
		//printf("Running, i = %d, running = %d, volume = %d\n", i, audio->running, audio->volume);
		i++;
		Pa_Sleep(100);
	}
	pthread_exit(NULL);
}

void* Audio::test(void* p){
	Audio *audio = (Audio*)p;
	int i = 0;
	printf("Running, i = %d, running = %d, volume = %d\n", i, audio->running, audio->volume);
	pthread_exit(NULL);
}

void Audio::setVolume(int volume){
	this->volume = volume;
}

int Audio::getVolume(){
	return this->volume;
}

int Audio::start(){
	this->running = true;
	PaError err = this->startStream();
	return 0;
}

int Audio::stop(){
	this->running = false;
	printf("Calling stop stream\n");
	PaError err = this->stopStream();
	printf("Error returned, err = %d\n", err);
	return 0;
}

PaError Audio::startStream(void){
		int i, totalSamps;

	#if TEST_UNSIGNED
		printf("PortAudio Test: output UNsigned 8 bit sine wave.\n");
	#else
		printf("PortAudio Test: output signed 8 bit sine wave.\n");
	#endif
		/* initialise sinusoidal wavetable */
		for( i=0; i<TABLE_SIZE; i++ )
		{
			sample_t max = 1<<14;
		    this->data.sine[i] = SILENCE + (sample_t) (max * sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2.));
		    //printf("this->data.sine[%d] = %d\n", i, this->data.sine[i]);
		}
		this->data.left_phase = this->data.right_phase = 0;
		this->data.framesToGo = totalSamps =  NUM_SECONDS * SAMPLE_RATE; /* Play for a few seconds. */

		this->err = Pa_Initialize();
		if( this->err != paNoError )
		    goto error;

		this->outputParameters.device = Pa_GetDefaultOutputDevice(); /* Default output device. */
		if (this->outputParameters.device == paNoDevice) {
		  fprintf(stderr,"Error: No default output device.\n");
		  goto error;
		}
		this->outputParameters.channelCount = 2;                     /* Stereo output. */
		this->outputParameters.sampleFormat = FORMAT;
		this->outputParameters.suggestedLatency = Pa_GetDeviceInfo( this->outputParameters.device )->defaultLowOutputLatency;
		this->outputParameters.hostApiSpecificStreamInfo = NULL;
		this->err = Pa_OpenStream( &this->stream,
		                     NULL,      /* No input. */
		                     &this->outputParameters,
		                     SAMPLE_RATE,
		                     FRAMES_PER_BUFFER,       /* Frames per buffer. */
		                     paClipOff, /* We won't output out of range samples so don't bother clipping them. */
		                     patestCallback,
		                     &this->data);
		if( this->err != paNoError )
		    goto error;

		this->streamOpened = Pa_GetStreamTime( this->stream ); /* Time in seconds when stream was opened (approx). */

		this->err = Pa_StartStream( this->stream );
		if( this->err != paNoError )
		    goto error;

		return 0;
	error:
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", this->err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( this->err ) );
		return this->err;
	}

PaError Audio::stopStream(){

		/* Stop sound. */
		printf("Stopping Stream.\n");
		this->err = Pa_StopStream( this->stream );
		if( this->err != paNoError )
		    goto error;
		/*
		printf("Pause for 2 seconds.\n");
		Pa_Sleep( 2000 );

		printf("Starting again.\n");
		this->err = Pa_StartStream( this->stream );
		if( this->err != paNoError )
		    goto error;

		printf("Waiting for sound to finish.\n");

		while( ( this->err = Pa_IsStreamActive( this->stream ) ) == 1 )
		    Pa_Sleep(100);
		if( this->err < 0 )
		    goto error;

		this->err = Pa_CloseStream( this->stream );
		if( this->err != paNoError )
		    goto error;*/
		printf("trying Pa_Terminate\n");
		Pa_Terminate();
		printf("Test finished.\n");
		return this->err;
	error:
		Pa_Terminate();
		fprintf( stderr, "An error occured while using the portaudio stream\n" );
		fprintf( stderr, "Error number: %d\n", err );
		fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
		return err;
	}


void Audio::addInputFromMixer(Mixer* mixer){
	this->data.mixer = mixer;
	printf("Mixer added\n");
}