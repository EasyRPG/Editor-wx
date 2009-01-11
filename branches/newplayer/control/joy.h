/* joy.h, joysticks control
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

class Joy
{
    private:
        SDL_Event    *joy_event;
        SDL_Joystick *joy;
        Uint32       REPEAT_BASE_TIME;
        Uint32       REPEAT_DELAY_TIME;
        bool         first_time;
        bool         delay;
	/* Keeps tracking of the enabled Joysticks */
	static int n_joy;

    public:
        /* Checks if there is at least, one available Joystick.
	      * If so, it enables the Joystick subsystem.
	      * This class method should be called before creating
	      * a Joy to use. */
         static bool joy_on();

        /* Initialize Joystick.
	      * Joysticks are numbered from 0 to n in SDL. */
        Joy(int n);

	     /* Close Joystick */
        ~Joy();

        /* Joy button handling */
        bool        button_press(Uint8 joy_button);
        bool        button_action(Uint8 joy_button, bool repeat);
        bool        button_repeat_control(Uint8 joy_button);

        /* Joy axis handling */
        bool	    axis_action(Uint8 joy_axis, Sint8 axis_value, bool repeat);
        bool        axis_repeat_control(Uint8 joy_axis, Sint8 axis_value);
        bool        axis_press(Uint8 joy_axis, Sint8 axis_value);
};

