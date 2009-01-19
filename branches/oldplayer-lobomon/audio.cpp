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

///a quedado perfessto

void Audio::init()
{
    int audio_rate      = 44100;
    Uint16 audio_format = AUDIO_S16;
    int audio_channels  = 2;
    int audio_buffers   = 4096;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
    {
        printf("Unable to open audio!\n");
        exit(1);
    }
    phaser_channel=-1;
}


void Audio::music_load(const char*string)
{
    My_mix_music        = Mix_LoadMUS(string);
    Mix_PlayMusic(My_mix_music, -1);
    //Mix_HookMusicFinished(funcion); //to call one function when this finishes
}


void Audio::stop_music()
{
    Mix_HaltMusic();
    Mix_FreeMusic(My_mix_music);
    My_mix_music        = NULL;
}


void Audio::sound_load(const char*string)
{
    My_mix_sound = Mix_LoadWAV(string);
    if (phaser_channel < 0)
    {
        phaser_channel = Mix_PlayChannel(-1, My_mix_sound, 1);
    }
    else
    {
        Mix_HaltChannel(phaser_channel);

        phaser_channel = -1;
    }
}

