    #include <stdlib.h>
    #include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>    
#include "audio.h"
        
void Audio::musicload(char* string)
{    static int canal;
   // if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096)) {
   if(Mix_OpenAudio(22050, AUDIO_S16, 2, (4096))) {
		printf("No se puede inicializar SDL_mixer %s\n",Mix_GetError());
	}
	atexit(Mix_CloseAudio);
	musica = Mix_LoadMUS(string);
    if ( musica == NULL ) {
        printf("No pude cargar musica: %s\n", Mix_GetError());
    }
    canal = Mix_PlayMusic(musica, -1);
}    


void Audio::stopmusic()
{	
	Mix_HaltMusic();
	Mix_FreeMusic(musica);
}             


void Audio::soundload(char* string)
{   //static bool soundplayed =false;  
	if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096)) {
		printf("No se puede inicializar SDL_mixer %s\n",Mix_GetError());
	}
    //if(soundplayed)
	//Mix_FreeChunk(sonido);

	atexit(Mix_CloseAudio);
    //soundplayed=true;
	sonido = Mix_LoadWAV(string);
    if ( sonido == NULL ) {
        printf("No pude cargar sonido: %s\n", Mix_GetError());
    }
    Mix_PlayChannel(-1, sonido, 0);
 }

void Audio::freesound(){
    Mix_FreeChunk(sonido);
}
