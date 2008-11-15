/*map_scene.cpp, map scene routines.
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

#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "math-sll.h"
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "tools.h"
#include "map.h"
#include "skill.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "actor.h"
#include "scene.h"

void Map_scene::init(Audio *audio, int screen_x, int screen_y, Uint8 *the_scene, Player_team *the_team)
{
	My_team             = the_team;
	My_audio            = audio;
	My_player           = My_team->get_chara(0);
	npc.init_chara();
 	My_team->my_view.x_pos   = 0;
	My_team->my_view.y_pos   = 0;
	npc.set_image("CharSet/Monster1.png");
	My_actor.init_chara();
	My_actor.set_image("CharSet/protagonist1.PNG");
	My_actor.set_xy_position(12, 12);

	npc.set_x(120);
	npc.set_y(120);
	my_net.set_image("Title/malla.png");
	my_net.x_pos     = 0;
	my_net.y_pos     = 0;
	//Loading map data
	my_map.load("Map0001.lmu");
	my_map.my_chipset.generate_from_file("ChipSet/Basis.png");
	My_audio->music_load("Music/Town.mid");
	new_scene       = the_scene;
	moving          = false;
	to_move         = 0;
	my_font.init_font();
}
void Map_scene::update(SDL_Surface*screen) {    // SDL_FillRect(screen, NULL, 0x0);// Clear screen  inutil
	my_map.render(screen, 0, My_team->my_view.x_pos, My_team->my_view.y_pos); //dibuja mapa capa 1 con repecto a la vista
	my_map.render(screen, 1, My_team->my_view.x_pos, My_team->my_view.y_pos);//dibuja mapa capa 2 con repecto a la vista
	My_actor.draw_c(screen);
	npc.add_x(-My_team->my_view.x_pos);
	npc.add_y(-My_team->my_view.y_pos);
	npc.draw_c(screen);
	npc.add_x (My_team->my_view.x_pos);
	npc.add_y (My_team->my_view.y_pos);

	// my_net.draw(screen);
	//ver los datos del mapa

}

void Map_scene::scroll()
{
//active the  scroll
	My_team->my_view.x_pos = My_actor.clamp((int) sll2dbl(My_actor.real_x) + 8 - (240 >> 1), 0, (my_map.map_width << 4) - 240);
	if (!My_actor.outofarea)
	{
        My_actor.x_pos=(int)sll2dbl(My_actor.real_x)  - My_team->my_view.x_pos;
	}
	else
	{
        My_actor.x_pos=(320 >> 1) - 8;
	}
	My_team->my_view.y_pos = My_actor.clamp((int) sll2dbl(My_actor.real_y) - (240 >> 1), 0, (my_map.map_height << 4) - 240);
	if (!My_actor.outofarea)
	{
        My_actor.y_pos=(int)sll2dbl(My_actor.real_y) - My_team->my_view.y_pos;
    } else
    {
        My_actor.y_pos=(240 >> 1);
	}
}
//minimo
void Map_scene::update_key() {

	My_actor.move_on_input();
	scroll();

	if (key_pressed_and_released(KEY_X )) {
			(*My_audio).sound_load("Sound/Cursor1.wav");
			*new_scene = 4;
		}
}


void Map_scene::npc_map() {
	static Uint8    *key_data;
	key_data = SDL_GetKeyState(NULL);
	if ((key_pressed_and_released(KEY_Z )) && (npc.colision((*My_player))))
	{
        Enemy   enemy_mapnpc;

        enemy_mapnpc.set_hp(20);
        enemy_mapnpc.set_max_hp(20);
        enemy_mapnpc.set_mp(200);
        enemy_mapnpc.set_max_mp(200);
        enemy_mapnpc.set_attack(12);
        enemy_mapnpc.set_defense(50);
        enemy_mapnpc.set_speed(25);
        enemy_mapnpc.set_spirit(20);
        (enemy_mapnpc.battler).set_image("Monster/Slime.png");
        (enemy_mapnpc.battler).setcols(1);
        (enemy_mapnpc.battler).setrows(1);
        (enemy_mapnpc.battler).x_pos = 140;
        (enemy_mapnpc.battler).y_pos = 100;
        enemy_mapnpc.set_name("Limo");
        My_team->add_enemy(enemy_mapnpc);
        enemy_mapnpc.set_name("Bat");
        enemy_mapnpc.set_hp(300);
        enemy_mapnpc.set_max_hp(30);
        (enemy_mapnpc.battler).set_image("Monster/Bat.png");
        (enemy_mapnpc.battler).x_pos = 80;
        (enemy_mapnpc.battler).y_pos = 100;
        My_team->add_enemy(enemy_mapnpc);
        enemy_mapnpc.set_hp(35);
        enemy_mapnpc.set_max_hp(35);
        enemy_mapnpc.set_name("Araña");
        (enemy_mapnpc.battler).set_image("Monster/Spider.png");
        (enemy_mapnpc.battler).x_pos = 180;
        (enemy_mapnpc.battler).y_pos = 100;
        My_team->add_enemy(enemy_mapnpc);
        enemy_mapnpc.set_hp(20);
        enemy_mapnpc.set_max_hp(20);
        enemy_mapnpc.set_name("Avispón");
        (enemy_mapnpc.battler).set_image("Monster/Bee.png");
        (enemy_mapnpc.battler).x_pos = 140;
        (enemy_mapnpc.battler).y_pos = 60;
        My_team->add_enemy(enemy_mapnpc);
        *new_scene = 2;
	}
}
void Map_scene::dispose()
{
	my_net.dispose();
//(*player).dispose();
	npc.dispose();
	my_map.my_chipset.dispose();
	alex_face.dispose();
	(*My_audio).stop_music();
}

