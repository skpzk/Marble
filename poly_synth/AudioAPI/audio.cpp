#include "audio.h"
#include "../Utils/wait.h"


/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
int paCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    paData *data = (paData*)userData;
    sample_t *out = (sample_t*)outputBuffer;

    int finished = 0;
    (void) inputBuffer; /* Prevent unused variable warnings. */

	// if(data->mixer != NULL){
	// 	//if Audio::addInputFromMixer is called before Audio::start, mixer != NULL
	// 	data->mixer->output(out, framesPerBuffer, true);
	// }
	if(data->output != NULL){
		//if Audio::addInput is called before Audio::start, output != NULL
		data->output->writeToBuffer(out, true);
	}

    return finished;
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
	if(err!=0){
		printf("Error returned, err = %d\n", err);
	}
	return 0;
}

PaError Audio::startStream(void){
		int i, totalSamps;

		this->err = Pa_Initialize();
		if( this->err != paNoError )
		    return this->error();

		this->outputParameters.device = Pa_GetDefaultOutputDevice(); /* Default output device. */
		if (this->outputParameters.device == paNoDevice) {
			fprintf(stderr,"Error: No default output device.\n");
			return this->error();
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
		                     paCallback,
		                     &this->data);
		if( this->err != paNoError )
		    return this->error();

		this->err = Pa_StartStream( this->stream );
		if( this->err != paNoError )
		    return this->error();
		return 0;
	}

PaError Audio::error(){
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
		    return this->error();

		Pa_Terminate();
		return this->err;
	}

void Audio::setInput(AudioOutput* output){
	this->data.output = output;
	printf("Output added to audio\n");
}
