/*stats_menu_scene.cpp, stats My_menu scene routines.
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
#include "sprite.h"
#include "key.h"
#include "font.h"
#include "audio.h"
#include "map.h"
#include "skill.h"
#include "item.h"
#include "enemy.h"
#include "player.h"
#include "math-sll.h"
#include "actor.h"
#include "scene.h"

void Status_scene::init(Audio *the_audio, bool *run,Uint8 *the_scene,Player_team *the_team)
{
    My_team     = the_team;
    My_audio    = the_audio;
    Status_vit.init(200, 80, 120, 0);
    Status.init(200, 80, 120, 80);
    my_weapons.init(200, 80, 120, 160);
    Profession.init(120, 240, 0, 0);
    int         i = My_team->select;
    int         space = 17;
    char        string_buffer[255];

    sprintf(string_buffer, "Hp             %d / %d", (*My_team->get_hp(i)), (*My_team->get_max_hp(i)));
    Status_vit.add_text(string_buffer, 10, 10);
    sprintf(string_buffer, "Mp             %d / %d", (*My_team->get_mp(i)), (*My_team->get_max_mp(i)));
    Status_vit.add_text(string_buffer, 10, 10 + (1 * space));
    sprintf(string_buffer, "Exp            %d / %d", (*My_team->get_exp(i)), (*My_team->get_max_exp(i)));
    Status_vit.add_text(string_buffer, 10, 10 + (2 * space));

    sprintf(string_buffer, "Fuerza        %d ", (*My_team->get_attack(i)));
    Status.add_text(string_buffer, 10, 5);
    sprintf(string_buffer, "Defenza       %d ", (*My_team->get_defense(i)));
    Status.add_text(string_buffer, 10, 5 + (1 * space));
    sprintf(string_buffer, "Intelecto     %d ", (*My_team->get_spirit(i)));
    Status.add_text(string_buffer, 10 ,5 + (2 * space));
    sprintf(string_buffer, "Agilidad      %d ", (*My_team->get_speed(i)));
    Status.add_text(string_buffer, 10, 5 + (3 * space));
    space = 40;
    Profession.add_sprite((My_team->get_faceset(i)),10,10);
    Profession.add_text("name", 10, 30 + (1 * space));
    Profession.add_text((My_team->get_name(i)),50,30+(1*space) + 16);
    Profession.add_text("Profesión", 10, 30 + (2 * space));
    Profession.add_text((My_team->get_job(i)), 50, 30 + (2 * space) + 16);
    Profession.add_text("Estado", 10, 30 + (3 * space));
    Profession.add_text("Normal", 50, 30 + (3 * space) + 16);//falta el casteo del entero
    Profession.add_text("Nivel", 10, 30 + (4 * space));
    sprintf(string_buffer, "%d ", (*My_team->get_level(i)));

    Profession.add_text(string_buffer, 50, 30 + (4 * space) + 16);//falta el casteo del entero
    space = 14;
    my_weapons.add_text((*(My_team->get_weapon(i))).get_name(), 75, 5);
    my_weapons.add_text((*(My_team->get_shield(i))).get_name(), 75, 5 + (1 * space));
    my_weapons.add_text((*(My_team->get_armor(i))).get_name(), 75, 5 + (2 * space));
    my_weapons.add_text((*(My_team->get_helmet(i))).get_name(), 75, 5 + (3 * space));
    my_weapons.add_text((*(My_team->get_accessory(i))).get_name(), 75, 5 + (4 * space));

    my_weapons.add_text("Weapon", 10, 5);
    my_weapons.add_text("shield", 10, 5 + (1 * space));
    my_weapons.add_text("Armor", 10, 5 + (2 * space));
    my_weapons.add_text("helm", 10, 5 + (3 * space));
    my_weapons.add_text("Others", 10, 5 + (4 * space));

    delay       = 0;
    running     = run;
    new_scene   = the_scene;
}

void Status_scene::update(SDL_Surface *screen)
{
    if (delay == 0)
    {
        Status.draw(screen);
        Status_vit.draw(screen);
        Profession.draw(screen);
        my_weapons.draw(screen);
        delay++;
    }



}

void Status_scene::update_key()
{
    if (key_pressed_and_released(KEY_X))
    {
        (*My_audio).sound_load("../Sound/Cansel2.wav");
        *new_scene = 4;
    }
}
void Status_scene::dispose()
{
    Status.dispose();
    Status_vit.dispose();
    Profession.dispose();
    my_weapons.dispose();
}
