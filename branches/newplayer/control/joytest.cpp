/* joytest.cpp, test for joypads and joysticks handling routines

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

/*
Atencion: El test va asi

Compilad este archivo(automaticamente(creo) buscará el de cabecera), y abridlo _por consola_,
no por navegador de archivos o 'ejecutar' Teneis que tener enchufado el joypad o joystick en cuestion
y pulsar un boton cualquiera del mando teniendo activa la ventana de la pantalla gris, si va bien tiene que salir un mensaje _por consola_
(por eso hay que abrirlo por consola, estoy muy bajo para renderizar texto en pantalla para un test,
al pulsar boton cambiar a la consola) si todo sale bien cuando pulseis por ejemplo el boton 2
(en teoría el de la derecha de los 4 botones que estan en la parte derecha del mando
(en caso que el mando sea tipo SNES o tipo playstation)) saldrá un mensaje poniendo 'Boton 2 -> ¡funciona!', eso es lo que debe salir para todos los botones
y los ejes

Este archivo se autodestruirá cuando funcione como se espera, en su lugar para el Easy RPG se empleará el joy.cpp. Notificadme
si funciona o si no da el resultado esperado mediante jabber(negativo@jabberes.org), por correo(rubenvn@gmail.com), o por el foro de easyrpg.
*/

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


bool Joy::axis_action(Uint8 joy_axis, Sint8 axis_value, bool repeat)
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

bool Joy::axis_press(Uint8 joy_axis, Sint8 axis_value)
{
    SDL_Event *joy_event;

    if (SDL_PollEvent(joy_event))
    {
        printf("Hay un evento");
        if (joy_event->type == SDL_JOYAXISMOTION)
        {
            printf("del tipo eje de joypad/joystick");
            if (axis_value < 0)     //  if value is up or left
            {
                printf("el valor de su eje debe ser negativo");
                if (joy_event->jaxis.axis == joy_axis)
                {
                    printf("Y lo es");

                    if(joy_event->jaxis.value <= axis_value)
                    {
                        printf("Y su eje es el %d");
                        return(true);
                    }
                }
            }
            if (axis_value > 0)
            {
                printf("el valor de su eje debe ser positivo");
                if (joy_event->jaxis.axis == joy_axis)
                {
                    printf("Y lo es");
                    if (joy_event->jaxis.value >= axis_value)
                    {
                        printf("Y su eje es el eje pedido");
                        return(true);
                    }
                }
            }
        }
    }
    return(false);   //  if no condition returned true
}


bool Joy::axis_repeat_control(Uint8 joy_axis, Sint8 axis_value)
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
        printf("Hay un evento");
        if (joy_event->type == SDL_JOYBUTTONDOWN)
        {
            printf("Del tipo boton de mando");
            if (joy_event->jbutton.button == joy_button)
            {
                printf("Su codigo es %d y hasta aqui ha llegado el evento", joy_button);
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

int main()
{

    if (Joy::joy_on())
    {
       Joy joystick(0);
       int joymode;
       joymode = scanf("Boton[cualquier numero salvo el 0] o eje[0]?");
       if (joymode)
       {
            Uint8 joy_input;
            do
            {
                joy_input = scanf("Boton?");
                if (joy_input > 3)
                {
                    printf("error, solo se permiten numeros del 0 al 3(hay mas pero con esos basta");
                }
            }
            while (joy_input > 3);
       }
       else
       {
           Uint8 joy_input;
           do
           {
               joy_input = scanf("Eje?");
               if (joy_input > 1)
               {
                   printf("error, solo se permiten numeros del 0 al 1(hay mas pero con esos basta)");
               }
           }
           while (joy_input > 1);

           Sint8 joy_axisvalue;
           do
            {
                joy_axisvalue = scanf("valor(0 = positivo, 1 = negativo)?");
                if (joy_axisvalue > 1)
                {
                    printf("error, solo se permiten numeros del 0 al 1");
                }
            }
            while (joy_axisvalue > 1);
            bool exit_program;
            exit_program = false;
            if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
            {
                printf("Error initializating any/some SDL subsystem(s)");
                exit_program = true;
            }
            SDL_Surface *screen;
            screen = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE);
            if (screen == NULL)
            {
                printf("Error initializating screen");
                exit_program = true;
            }
            SDL_WM_SetCaption ("Window title pending", NULL);


            while (!exit_program)
            {
                if (joymode != 0)
                {
                    if (joystick.button_action(joy_input, false))
                    {
                        exit_program = true;
                    }
                }
                else
                {
                    if (joystick.axis_action(joy_input, joy_axisvalue, false))
                    {
                        exit_program = true;
                    }
                }
            }
        }
    }
    else
    {
            printf("\nError, joystick/joypad no conectado\n");
    }
}
