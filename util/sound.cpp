#ifdef noaudio

void doExplosion(){}
void doMusic(){}
void doShoot(){}
void initSound(){}
void cleanUpSound(){}
#else
//Sound stuff based on Gordon's Worm Framework Sound
/*------------------------------------------------------------------------------------------------------------------------------------------*/

//Finally a straight forward OpenAL sample program.
//Gordon Griesel
//2016
//This demo plays two simultaneous sounds.
//One is looping, the other is not looping.
//Modified By: Robert Ripley for Tank-Blaster April,2017
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <AL/alut.h>
#include <pthread.h>

//Buffers hold the sound information.
ALuint alBuffer[2];
//Source refers to the sound.
ALuint alSource[2];

ALuint alBufferExplode, alBufferMusic, alBufferShoot;
ALuint alSourceExplode, alSourceMusic, alSourceShoot;

void initExplosion();
void initMusic();

void initSound() {

	alutInit(0, NULL);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: alutInit()\n");
		return;
	}
	//Clear error state.
	alGetError();
	//
	//Setup the listener.
	//Forward and up vectors are used.
	float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);
	//
	//Buffer holds the sound information.
	alBufferExplode = alutCreateBufferFromFile("./Explode.wav");

	//Source refers to the sound.
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSourceExplode);
	alSourcei(alSourceExplode, AL_BUFFER, alBufferExplode);
	alSourcef(alSourceExplode, AL_GAIN, .5f);
	alSourcef(alSourceExplode, AL_PITCH, 1.0f);
	alSourcei(alSourceExplode, AL_LOOPING, AL_FALSE);

	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

	alBufferMusic   = alutCreateBufferFromFile("./Home_Base_Groove.wav");
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSourceMusic);
	alSourcei(alSourceMusic, AL_BUFFER, alBufferMusic);
	alSourcef(alSourceMusic, AL_GAIN, 5.0f);
	alSourcef(alSourceMusic, AL_PITCH, 1.0f);
	alSourcei(alSourceMusic, AL_LOOPING, AL_TRUE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

	alBufferShoot   = alutCreateBufferFromFile("./Shoot.wav");
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSourceShoot);
	alSourcei(alSourceShoot, AL_BUFFER, alBufferShoot);
	alSourcef(alSourceShoot, AL_GAIN, .1f);
	alSourcef(alSourceShoot, AL_PITCH, 1.0f);
	alSourcei(alSourceShoot, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
		return;
	}

}


void cleanUpSound() {

	//First delete the source.
	alDeleteSources(1, &alSourceExplode);
	alDeleteSources(1, &alSourceMusic);
	alDeleteSources(1, &alSourceShoot);
	//Delete the buffer.
	alDeleteBuffers(1, &alBufferExplode);
	alDeleteBuffers(1, &alBufferMusic);
	alDeleteBuffers(1, &alBufferShoot);
	//Close out OpenAL itself.
	//Get active context.
	ALCcontext *Context = alcGetCurrentContext();
	//Get device for active context.
	ALCdevice *Device = alcGetContextsDevice(Context);
	//Disable context.
	alcMakeContextCurrent(NULL);
	//Release context(s).
	alcDestroyContext(Context);
	//Close device.
	alcCloseDevice(Device);

}

void playSound(ALuint source){
	alSourcePlay(source);
}

pthread_t soundThread[2];

void doMusic() {
	alSourcePlay(alSourceMusic);
}

void doShoot() {
	playSound(alSourceShoot);
}

void doExplosion() {
	playSound(alSourceExplode);
}
#endif
