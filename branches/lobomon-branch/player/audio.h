/* audio.h, EasyRPG player audio class declaration file.
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

#ifndef AUDIO_H_
#define AUDIO_H_

class Audio {
protected:
   Mix_Music * musica;  
   Mix_Chunk * sonido;
   int phaserChannel;

public:
    void init();
    void musicload(const char* string);
    void stopmusic();
    void soundload(const char* string);
};

#endif
