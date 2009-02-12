/*Map_scene.cpp, Map_Scene routines.
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

#include "Map_scene.h"

void Map_Scene::init(Audio *audio, int SCREEN_X, int SCREEN_Y, unsigned char *TheScene, Player_Team *TheTeam)
{
    myteam = TheTeam;
    myaudio = audio;
    SCREEN_SIZE_X = SCREEN_X;
    SCREEN_SIZE_Y = SCREEN_Y;
    player = myteam->get_chara(0);
    NScene = TheScene;
    load_map();
}

void Map_Scene::load_map()
{
    int Map_id;
    Map_id=  myteam->actual_map;
    actual_map=Map_id;
    myteam->view.x = 0;
    myteam->view.y = 0;

    std::string system_string;
    system_string.append("CharSet/");
    system_string.append(myteam->data2.heros[0].strGraphicfile);
    system_string.append(".png");
    Actor.init_Chara();
    Actor.setimg((char *)system_string.c_str(), myteam->data2.heros[0].intGraphicindex);

    system_string.clear();
    system_string.append("Map");

    if (Map_id<1000)
        system_string.append("0");
    if (Map_id<100)
        system_string.append("0");
    if (Map_id<10)
        system_string.append("0");

    std::stringstream ss;
    ss << Map_id;

    system_string.append(ss.str());
    system_string.append(".lmu");
    // ===[ LOADING MAP DATA ]==============================================
    Map.Load((char *)system_string.c_str(), &data);
    //Map.ShowInformation(&data);

    system_string.clear();
    system_string.append("ChipSet/");
    system_string.append(myteam->data2.Tilesets[(unsigned int) data.ChipsetID - 1].strGraphic);
    system_string.append(".png");
    pre_chip.GenerateFromFile((char *) system_string.c_str());

    chip.init(pre_chip.ChipsetSurface, &data, &myteam->data2.Tilesets[(unsigned int) data.ChipsetID - 1] );

    Events = &data.vcEvents;
    init_npc();
    Actor.setposXY(myteam->actual_x_map,myteam->actual_y_map, &chip,&Charas_nps,NScene,myteam);
    Actor.set_dir(myteam->actual_dir);

    myaudio->load("Music/Town.mid");
    myaudio->play(-1);
    Control::set_delay(0);
    Control::set_in_delay(0);
    Control::in_map = true;
    Ev_management.init(myaudio,NScene,myteam,Events,&Charas_nps,&Actor,&data,&chip);
    Mov_management.init(&Charas_nps,&Actor,&data,&chip);
}


void Map_Scene::init_npc()
{
    unsigned int i;
    std::string system_string;
    Chara npc;
    npc.init_Chara();
    SDL_Surface *temp2;
//printf("data stuck %d",i);

    for (i = 0; i < Events->size(); i++)
    {
        //printf("data stuck %d",i);
        system_string.clear();
        system_string.append("CharSet/");
        system_string.append(data.vcEvents[i].vcPage[0].CharsetName);
        system_string.append(".png");
        if (!system_string.compare("CharSet/.png"))
        {
            temp2 = CreateSurface(24, 32);
            chip.RenderTile(temp2, 4, 16, data.vcEvents[i].vcPage[0].CharsetID + 0x2710, 0);
            npc.set_surface(temp2);
            npc.dir = 0;
            npc.frame = 1;
        }
        else
        {
            npc.setimg((char *) system_string.c_str(), data.vcEvents[i].vcPage[0].CharsetID);
            npc.dir = data.vcEvents[i].vcPage[0].Facing_direction;
            npc.frame = data.vcEvents[i].vcPage[0].Animation_frame;
        }
        npc.move_dir=data.vcEvents[i].vcPage[0].Movement_type;
        if (npc.move_dir==2)
            npc.move_dir=0;
        npc.move_frec=data.vcEvents[i].vcPage[0].Movement_frequency;
        npc.anim_frec=data.vcEvents[i].vcPage[0].Movement_speed;
        npc.layer=data.vcEvents[i].vcPage[0].Event_height;
        npc.setposXY(data.vcEvents[i].X_position, data.vcEvents[i].Y_position);
        Charas_nps.push_back(npc);

    }
}



void Map_Scene::update(SDL_Surface *Screen)
{
    //WE shuold use layers!!
    SDL_FillRect(Screen, NULL, 0x0);// Clear screen  inutil
    unsigned int i;

    chip.Render(Screen, 0, myteam->view.x, myteam->view.y); //dibuja mapa capa 1 con repecto a la vista
    chip.Render(Screen, 1, myteam->view.x, myteam->view.y);//dibuja mapa capa 2 con repecto a la vista

    for (i = 0; i < Charas_nps.size(); i++)
    {
        Charas_nps[i].addx(- myteam->view.x);
        Charas_nps[i].addy(- myteam->view.y);
        if (Charas_nps[i].layer == 0)
            Charas_nps[i].drawc(Screen);
        if ((Charas_nps[i].layer == 1) && (Charas_nps[i].GridY <= Actor.GridY))
            Charas_nps[i].drawc(Screen);
    }

    Actor.drawc(Screen);

    for (i = 0; i < Charas_nps.size(); i++)
    {
        if (Charas_nps[i].layer == 2)
            Charas_nps[i].drawc(Screen);
        if ((Charas_nps[i].layer== 1) && (Charas_nps[i].GridY > Actor.GridY))
            Charas_nps[i].drawc(Screen);
    }

    for (i = 0; i < Charas_nps.size(); i++)
    {
        Charas_nps[i].addx(+ myteam->view.x);
        Charas_nps[i].addy(+ myteam->view.y);
    }

    Ev_management.update(Screen);
}


void Map_Scene::Scroll()
{
    myteam->view.x = Actor.Clamp((int) sll2dbl(Actor.realX) + 20 - (SCREEN_SIZE_X >> 1), 0, (chip.data->MapWidth << 4) - SCREEN_SIZE_X);
    if (!Actor.outofarea)
    {
        Actor.x = (int) sll2dbl(Actor.realX) - myteam->view.x;
    }
    else
    {
        Actor.x = (SCREEN_SIZE_X >> 1) - 20;
    }

    myteam->view.y= Actor.Clamp((int) sll2dbl(Actor.realY) + 24 - (SCREEN_SIZE_Y >> 1), 0, (chip.data->MapHeight << 4) - SCREEN_SIZE_Y);
    if (!Actor.outofarea)
    {
        Actor.y = (int) sll2dbl(Actor.realY) - myteam->view.y ;
    }
    else
    {
        Actor.y = (SCREEN_SIZE_Y >> 1) - 24;
    }
}


void Map_Scene::updatekey()
{
    unsigned int i;
    Actor.MoveOnInput();
    Scroll();
    for (i = 0; i < Charas_nps.size(); i++)
    {
        if (!Charas_nps[i].move(Charas_nps[i].move_dir))
        {
            if ( Charas_nps[i].move_frec_check())//till time to move
            {
                Charas_nps[i].move_dir= Mov_management.get_dir(i);

                switch (Charas_nps[i].move_dir)
                {
                case DIRECTION_UP:
                    Charas_nps[i].GridY-=1;
                    break;
                case DIRECTION_DOWN:
                    Charas_nps[i].GridY+=1;
                    break;
                case DIRECTION_LEFT:
                    Charas_nps[i].GridX-=1;
                    break;
                case DIRECTION_RIGHT:
                    Charas_nps[i].GridX+=1;
                    break;
                }

                Charas_nps[i].state=true;
            }
        }
        if (((data.vcEvents[i].vcPage[0].Animation_type==1)||(data.vcEvents[i].vcPage[0].Animation_type==3))&&data.vcEvents[i].vcPage[0].Movement_type==0)
            Charas_nps[i].frameupdate();
        if (data.vcEvents[i].vcPage[0].Animation_type==5)
        {
            Charas_nps[i].nomalanimation=false;
            Charas_nps[i].rotationupdate();
        }
    }
    mapnpc();
}


void Map_Scene::mapnpc()
{
    unsigned int event_id,comand_id;
    Event_comand * comand;
    for (event_id=0;event_id< Charas_nps.size();event_id++)
    {
        if (Actor.tried_to_talk &&(Actor.npc_subcolision(event_id)))
        {
                printf(" x %d",data.vcEvents[event_id].vcPage[0].vcEvent_comand.size());
                printf("total %d",data.vcEvents.size());

                for(comand_id=0 ;comand_id<data.vcEvents[event_id].vcPage[0].vcEvent_comand.size(); comand_id++)
                {
                    comand=data.vcEvents[event_id].vcPage[0].vcEvent_comand[comand_id];
                    printf("id %d",comand->Comand);
                    comand_id =Ev_management.exec_comand(comand,event_id,comand_id);
                    if(actual_map!=myteam->actual_map)
                    {
                        dispose();
                        load_map();
                        break;
                        break;
                    }

                }
            Actor.tried_to_talk=false;
        }
    }

}
void Map_Scene::dispose()
{
    unsigned int i;
    for (i = 0; i < Charas_nps.size(); i++)
    {
        Charas_nps[i].dispose();
    }
    data.clear_events();
    Actor.dispose();
    Charas_nps.clear();
    pre_chip.dispose();
    myaudio->stop();
}
