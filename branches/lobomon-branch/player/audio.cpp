/* audio.cpp, audio routines.
   Copyright (C) 2007 EasyRPG Project <http://easyrpg.sourceforge.net/>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "audio.h"

void Audio::init()
{
  int audio_rate = 44100;
  Uint16 audio_format = AUDIO_S16; 
  int audio_channels = 2;
  int audio_buffers = 4096;

  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  }
 phaserChannel = -1;
}

      
void Audio::musicload(const char* string)
{   
	musica = Mix_LoadMUS(string);
	Mix_PlayMusic(musica, -1);
	//Mix_HookMusicFinished(funcion); //por is queremos llamar uan funcion cuando termine
}    


void Audio::stopmusic()
{	
	Mix_HaltMusic();
	Mix_FreeMusic(musica);
	musica = NULL;
}             


void Audio::soundload(const char* string)
{   
     sonido = Mix_LoadWAV(string);
      if(phaserChannel < 0) {
	phaserChannel = Mix_PlayChannel(-1, sonido, 1);
      }
 else {
      Mix_HaltChannel(phaserChannel);
      
      phaserChannel = -1;
    }
 }

