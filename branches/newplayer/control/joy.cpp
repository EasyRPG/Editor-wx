/* joy.cpp, routines jor joypads and joysticks handling

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

#include "SDL.h"
#include "joy.h"
#include <iostream>

int Joy::n_joy = 0;

bool Joy::joy_on()
{
   if (!SDL_WasInit(SDL_INIT_JOYSTICK))
   {
      SDL_InitSubSystem(SDL_INIT_JOYSTICK);
   }

   if (SDL_NumJoysticks() > 0)
   {
      return true;
   }
   else
   {
      SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
      return false;
   }

}

Joy::Joy(int n)
{
   joy = SDL_JoystickOpen(n);
   if (joy == NULL)
   {
      std::cerr << "* Error: There aren't avaliable joysticks" << std::endl;
      exit(1);

   }
   SDL_JoystickEventState(SDL_ENABLE);
   n_joy++;
   REPEAT_BASE_TIME = 250;
   REPEAT_DELAY_TIME = 60;
}

Joy::~Joy()
{
   n_joy--;
   SDL_JoystickClose(joy);

   if (n_joy == 0)
   {
      SDL_JoystickEventState(SDL_IGNORE);
   }
}


bool Joy::axis_action(Uint8 joy_axis, Sint16 axis_value, bool repeat)
{

    switch(repeat)
    {
        case false:
        {
            return (Joy::axis_press(joy_axis, axis_value));
            break;
        }
        case true:
        {
            return (axis_repeat_control(joy_axis, axis_value));
        }
    }
}

bool Joy::axis_press(Uint8 joy_axis, Sint16 axis_value)
{
      if (SDL_PollEvent(joy_event))
      {
        if (joy_event->type == SDL_JOYAXISMOTION)
        {
            if (axis_value < 0)     //  if value is up or left
            {

                if (joy_event->jaxis.axis == joy_axis)
                {
                    if(joy_event->jaxis.value <= axis_value)
                    {

                        return(true);
                    }
                }
            }
            if (axis_value > 0)
            {
                if (joy_event->jaxis.axis == joy_axis)
                {
                    if (joy_event->jaxis.value >= axis_value)
                    {

                        return(true);
                    }
                }
            }
        }
        return(false);   //  if no condition returned true
    }
}

bool Joy::axis_repeat_control(Uint8 joy_axis, Sint16 axis_value)
{

    //if initial delay switch is disabled

    if(!delay)
    {
        if(first_time)// when event switches from none to keydown
        {
            first_time = false;
            return Joy::axis_press(joy_axis, axis_value);
        }

        Uint32 joy_time    = SDL_GetTicks();
        do
        {
            if(!axis_press(joy_axis, axis_value))
            {
                first_time = true;   // if there was a key-up event when time required...
                return (false);       // ... for enable initial delay switch
            }
        }while ((SDL_GetTicks() - joy_time) < REPEAT_BASE_TIME);

        delay = true; // if time loop finished with pressing all the time the desired key
    }

    //if initial delay switch is enabled

    Uint32 joy_time    = SDL_GetTicks();
    do
    {   if(!axis_press(joy_axis, axis_value))//if there was a key-up when delay switch is enabled)
        {
            delay = false;
            first_time = true;
            return (false);

        }
    }while ((SDL_GetTicks() - joy_time) < REPEAT_DELAY_TIME);
    return (true);//if there wasn't a key-up when switch enabled
}


bool Joy::button_action(Uint8 joy_button, bool repeat)
{
    switch(repeat)
    {
        case false:
        {
            return (Joy::button_press(joy_button));
            break;
        }
        case true:
        {
            return (Joy::button_repeat_control(joy_button));
	    break; 
	}
    }

}

bool Joy::button_press(Uint8 joy_button)
{
    SDL_Event *joy_event;

    if (SDL_PollEvent(joy_event))
    {
	printf("\namparo")
	if (joy_event->type == SDL_JOYBUTTONDOWN)
	{	printf("\namparo2")	
		if (joy_event->jbutton.button == joy_button)
		{
			printf("\namparo3")
			return (true);
		}
	}
        
    }
    return (false);   //  if no condition returned true	
}

bool Joy::button_repeat_control(Uint8 joy_button)
{

    //if initial delay switch is disabled

    if(!delay)
    {
        if(first_time)// when event switches from none to keydown
        {
            first_time = false;
            return button_press(joy_button);
        }

        Uint32 joy_time    = SDL_GetTicks();
        do
        {
            if(!button_press(joy_button))
            {
                first_time = true;   // if there was a key-up event when time required...
                return (false);       // ... for enable initial delay switch
            }
        }while ((SDL_GetTicks() - joy_time) < REPEAT_BASE_TIME);

        delay = true; // if time loop finished with pressing all the time the desired key
    }

    //if initial delay switch is enabled

    Uint32 joy_time    = SDL_GetTicks();
    do
    {   if(!button_press(joy_button))//if there was a key-up when delay switch is enabled)
        {
            delay = false;
            first_time = true;
            return (false);

        }
    }while ((SDL_GetTicks() - joy_time) < REPEAT_DELAY_TIME);
    return (true);//if there wasn't a key-up when switch enabled
}

