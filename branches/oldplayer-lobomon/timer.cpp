/*timer.cpp, timer routines.
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
#include "SDL.h"#include "timer.h"

///a quedado perfessto

Timer::Timer()
{
    //Initialize the variables
    start_ticks     = 0;
    paused_ticks    = 0;
    paused          = false;
    started         = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    start_ticks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        paused_ticks = SDL_GetTicks() - start_ticks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        start_ticks = SDL_GetTicks() - paused_ticks;

        //Reset the paused ticks
        paused_ticks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if(started == true)
    {
        //If the timer is paused
        if(paused == true)
        {
            //Return the number of ticks when the the timer was paused
            return paused_ticks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - start_ticks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}
