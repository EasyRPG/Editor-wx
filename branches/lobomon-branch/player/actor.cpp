/*actor.cpp, actor routines.
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

//extern CWorld  *World; //cuando exista
#include "SDL.h"
#include "math-sll.h"
#include "sprite.h"
#include "actor.h"
#include "deltatime.h"
extern Delta_time My_actor_system_time;

/*
metodos faltantes

World->CollisionAt(grid_x, grid_y+1, WORLD_COLLISION_FROM_UP)



*/
#define ACTOR_STATE_IDLE        0x00
#define ACTOR_STATE_MOVING      0x01

#define ACTOR_DIRECTION_UP      0x00
#define ACTOR_DIRECTION_DOWN    0x01
#define ACTOR_DIRECTION_LEFT    0x02
#define ACTOR_DIRECTION_RIGHT   0x03

#define ACTOR_FLAGS_FREEZE      0x01

#define ACTOR_SPEED_SLOW        2.0f



int Actor::clamp(int value, int min, int max)
{
    if (value<min)//mark when is out of range under development
    {
        outofarea = false;
        return (min);
    }
    else
        if (value>max)
        {
            outofarea = false;
            return (max);
        }
        else
        {
            outofarea = true;
            return (value);
        }

    return ((value<min)? min:(value>max)? max:value);
}
int Actor::min(int value, int max)
{
    return ((value>max)? max:value);
}

sll Actor::min_f(float value, float max)
{
    return ((value>=max)? max:value);
}

sll Actor::clamp_f(float value, float min, float max)
{
    return ((value<min)? min:(value>=max)? max:value);
}

void Actor::set_xy_position(int x_pos,int y_pos)
{
    realX=(sll)x_pos;
    realY=(sll)y_pos;
}

void Actor::move_on_input()
{
    // In case the method was called and the actor is put on freeze
    // (for example, on message display or game pause)
    if (flags & ACTOR_FLAGS_FREEZE) return;
    // Depending on current actor state, select between accepting input
    // and Motion
    switch (state)
    {
    case ACTOR_STATE_IDLE:
        Uint8 *key_data;
        key_data = SDL_GetKeyState(NULL);
        if ( key_data[SDLK_UP]  )
        {
            // && World->CollisionAt(grid_x, grid_y-1, WORLD_COLLISION_FROM_DOWN)==false) {
            state            = ACTOR_STATE_MOVING;
            Motion.direction = ACTOR_DIRECTION_UP;
            actor_direction = 0;
            Motion.distance  = 0;
        }
        else if (key_data[SDLK_DOWN]  )
        {
            // && World->CollisionAt(grid_x, grid_y+1, WORLD_COLLISION_FROM_UP)==false) {
            state            = ACTOR_STATE_MOVING;
            Motion.direction = ACTOR_DIRECTION_DOWN;
            actor_direction = 2;
            Motion.distance  = 0;
        }
        else if ( key_data[SDLK_LEFT] )
        {
            // && World->CollisionAt(grid_x-1, grid_y, WORLD_COLLISION_FROM_RIGHT)==false) {
            state               = ACTOR_STATE_MOVING;
            Motion.direction    = ACTOR_DIRECTION_LEFT;
            actor_direction                 = 3;
            Motion.distance     = 0;
        }
        else if ( key_data[SDLK_RIGHT] )
        {
            //&& World->CollisionAt(grid_x+1, grid_y, WORLD_COLLISION_FROM_LEFT)==false) {
            state               = ACTOR_STATE_MOVING;
            Motion.direction    = ACTOR_DIRECTION_RIGHT;
            actor_direction     = 1;
            Motion.distance     = 0;
        }
        else
        {
            frame = 0;
        }
// 	    grid_x=(x_pos)>>4; grid_y=(y_pos)>>4;// Calculate Grid x_pos and Grid y_pos
        break;
    case ACTOR_STATE_MOVING:
        // Calculate how many pixels has the actor travelled  and how many's left
        Motion.delta    = clamp_f(ACTOR_SPEED_SLOW*My_actor_system_time.delta_time, 0, 16 - Motion.distance); // clamp_f(value, min, max)
        Motion.distance = min_f(Motion.distance + ACTOR_SPEED_SLOW * My_actor_system_time.delta_time, 16.0f);//min_f(distancia + movimiento, maximo )
        frame_update();
        // Change position of character by adding the delta
        switch (Motion.direction)
        {
        case ACTOR_DIRECTION_UP:
            realY = sllsub(realY, Motion.delta);
            break;
        case ACTOR_DIRECTION_DOWN:
            realY = slladd(realY, Motion.delta);
            break;
        case ACTOR_DIRECTION_LEFT:
            realX = sllsub(realX, Motion.delta);
            break;
        case ACTOR_DIRECTION_RIGHT:
            realX = slladd(realX, Motion.delta);
            break;
        }

        if (Motion.distance == 16.0f) state = ACTOR_STATE_IDLE;
        break;
    }
}
