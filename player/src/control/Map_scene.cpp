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
    myteam->view.x = 0;
    myteam->view.y = 0;
    NScene = TheScene;
    load_map(TheTeam->actual_map,TheTeam->actual_x_map,TheTeam->actual_y_map);

}

void Map_Scene::load_map(int Map_id,int  X,int Y)
{
    std::string system_string;
    system_string.append("CharSet/");
    system_string.append(myteam->data2.heros[0].strGraphicfile);
    system_string.append(".png");
    Actor.init_Chara();
    Actor.setimg((char *)system_string.c_str(), 5);

    system_string.clear();
    system_string.append("Map");

if(Map_id<1000)
    system_string.append("0");
if(Map_id<100)
    system_string.append("0");
if(Map_id<10)
    system_string.append("0");

    std::stringstream ss;
    ss << Map_id;

    system_string.append(ss.str());
    system_string.append(".lmu");
    printf("map %s",system_string.c_str());
    // ===[ LOADING MAP DATA ]==============================================
    Map.Load((char *)system_string.c_str(), &data);
    Map.ShowInformation(&data);

    system_string.clear();
    system_string.append("ChipSet/");
    system_string.append(myteam->data2.Tilesets[(unsigned int) data.ChipsetID - 1].strGraphic);
    system_string.append(".png");
    pre_chip.GenerateFromFile((char *) system_string.c_str());

    chip.init(pre_chip.ChipsetSurface, &data, &myteam->data2.Tilesets[(unsigned int) data.ChipsetID - 1] );

    Events = &data.vcEvents;
    init_npc();
    Actor.setposXY(X, Y, &chip,&Charas_nps);


    myaudio->load("Music/Town.mid");
    fuente.init_Font();
    myaudio->play(-1);
    Control::set_delay(0);
    Control::set_in_delay(0);
    Control::in_map = true;

}


void Map_Scene::init_npc()
{
    unsigned int i;
    std::string system_string;
    Chara npc;
    npc.init_Chara();
    SDL_Surface *temp2;

    for (i = 0; i < Events->size(); i++)
    {
        system_string.clear();
        system_string.append("CharSet/");
        system_string.append(data.vcEvents[i].vcPage[0].CharsetName);
        system_string.append(".png");
        printf("qj %s", (char *) system_string.c_str());

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
        if(npc.move_dir==2)
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
    // SDL_FillRect(Screen, NULL, 0x0);// Clear screen  inutil
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


bool Map_Scene::npc_colision(int x, int y,int e)
{
    unsigned int i;
    for (i = 0; i < Charas_nps.size(); i++)
    {
        if(i!=(unsigned)e)
        if(( Charas_nps[i].GridX==x) &&(Charas_nps[i].GridY==y))
            //if(Charas_nps[i].layer==1)
                return(false);
    }
    if(( Actor.GridX==x) &&(Actor.GridY==y))
        return(false);
    return(true);
}
int Map_Scene::get_dir(int i)
{
    int temp,z;
    if (data.vcEvents[i].vcPage[0].Movement_type==0)//do not move
        return(5);
    if (data.vcEvents[i].vcPage[0].Movement_type==1)// random
    {
        temp=rand()%4;
        for(z=0;z<4;z++)
        {
        switch (temp)
        {
        case DIRECTION_UP:
        if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
            return(temp);
             break;
        case DIRECTION_DOWN:
        if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
            return(temp);
             break;
        case DIRECTION_LEFT:
        if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
            return(temp);
             break;
        case DIRECTION_RIGHT:
        if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
            return(temp);
             break;
        }
            temp=(temp+1)%4;
        }
        return(5);
    }
    if (data.vcEvents[i].vcPage[0].Movement_type==2)// up down
    {
        if (Charas_nps[i].move_dir==0x00)
        {
            if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
                return(0x00);
            else
            if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
                return(0x01);
        }
        else
        {
            if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
                return(0x01);
            else
            if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
                return(0x00);
        }
        return(5);//default
    }
    if (data.vcEvents[i].vcPage[0].Movement_type==3)// left right
    {
        if (Charas_nps[i].move_dir==0x03)
        {
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
                return(0x03);
            else
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
                return(0x02);
        }
        else
        {
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
                return(0x02);
            else
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
                return(0x03);
        }
        return(5);//default
    }

    if (data.vcEvents[i].vcPage[0].Movement_type==4)// go to the hero
    {
        if(Charas_nps[i].GridX<Actor.GridX)
        {
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
                return(0x03);
        }
        if(Charas_nps[i].GridX>Actor.GridX)
        {
         if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
                return(0x02);
        }
        if(Charas_nps[i].GridY<Actor.GridY)
        {
            if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
                return(0x01);
        }
        if(Charas_nps[i].GridY>Actor.GridY)
        {
             if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
                return(0x00);
        }
        temp=rand()%4;
        for(z=0;z<4;z++)
        {
            switch (temp)
            {
            case DIRECTION_UP:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
                return(temp);
             break;
            case DIRECTION_DOWN:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
                return(temp);
             break;
            case DIRECTION_LEFT:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
                return(temp);
             break;
            case DIRECTION_RIGHT:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
            return(temp);
             break;
            }
        temp=(temp+1)%4;
        }
        return(5);
    }



    if (data.vcEvents[i].vcPage[0].Movement_type==5)// run frome the hero
    {
        if(Charas_nps[i].GridX<Actor.GridX)
        {
         if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
                return(0x02);

        }
        if(Charas_nps[i].GridX>Actor.GridX)
        {
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
                return(0x03);
        }
        if(Charas_nps[i].GridY<Actor.GridY)
        {
             if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
                return(0x00);
        }
        if(Charas_nps[i].GridY>Actor.GridY)
        {
            if ((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
                return(0x01);
        }
        temp=rand()%4;
        for(z=0;z<4;z++)
        {
            switch (temp)
            {
            case DIRECTION_UP:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
                return(temp);
             break;
            case DIRECTION_DOWN:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
                return(temp);
             break;
            case DIRECTION_LEFT:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
                return(temp);
             break;
            case DIRECTION_RIGHT:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
            return(temp);
             break;
            }
        temp=(temp+1)%4;
        }
        return(5);
    }


    if (data.vcEvents[i].vcPage[0].Movement_type==6)// use the stack
    {
        temp=data.vcEvents[i].vcPage[0].vcPage_Moves.vcMovement_commands[Charas_nps[i].actual_move].Comand;
        Charas_nps[i].actual_move= ((Charas_nps[i].actual_move+1)%data.vcEvents[i].vcPage[0].vcPage_Moves.Movement_length);
        switch (temp)
            {
            case 0:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_UP))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY-1),i)))
                return(DIRECTION_UP);
             break;
            case 2:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_DOWN))&&(npc_colision(Charas_nps[i].GridX, (Charas_nps[i].GridY+1),i)))
                return(DIRECTION_DOWN);
             break;
            case 3:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_LEFT))&&(npc_colision((Charas_nps[i].GridX-1), Charas_nps[i].GridY,i)))
                return(DIRECTION_LEFT);
             break;
            case 1:
            if((chip.CollisionAt(Charas_nps[i].GridX,Charas_nps[i].GridY,DIRECTION_RIGHT))&&(npc_colision((Charas_nps[i].GridX+1), Charas_nps[i].GridY,i)))
            return(DIRECTION_RIGHT);
             break;
            }
    }

    return(5);
}

void Map_Scene::updatekey()
{
    unsigned int i;
    Actor.MoveOnInput();
    Scroll();
    for (i = 0; i < Events->size(); i++)
    {
        if (!Charas_nps[i].move(Charas_nps[i].move_dir))
        {
            if ( Charas_nps[i].move_frec_check())//till time to move
            {
                Charas_nps[i].move_dir=get_dir(i);

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

    if (Key_press_and_realsed(LMK_X))
    {
        //(*myaudio).load("Sound/Cursor1.wav");
        *NScene = 4;
    }
}


void Map_Scene::mapnpc()
{
    static unsigned char *keyData;

    keyData = SDL_GetKeyState(NULL);
    /*
    if ((Key_press_and_realsed(LMK_Z )) &&(npc.colision((*player))))
    {
    	Enemy enemigo;
    	enemigo.set_HP(20);
    	enemigo.set_MaxHP(20);
    	enemigo.set_MP(200);
    	enemigo.set_MaxMP(200);
    	enemigo.set_Attack(12);
    	enemigo.set_Defense(50);
    	enemigo.set_Speed(25);
    	enemigo.set_Spirit(20);
    	(enemigo.Batler).setimg("Monster/Slime.png");
    	(enemigo.Batler).setcols(1);
    	(enemigo.Batler).setrows(1);
    	(enemigo.Batler).x=140;
    	(enemigo.Batler).y=100;
    	enemigo.set_name("Limo");
    	(*myteam).add_enemy(enemigo);
    	enemigo.set_name("Murici");
    	enemigo.set_HP(300);
    	enemigo.set_MaxHP(30);
    	(enemigo.Batler).setimg("Monster/Bat.png");
    	(enemigo.Batler).x=80;
    	(enemigo.Batler).y=100;
    	(*myteam).add_enemy(enemigo);
    	enemigo.set_HP(35);
    	enemigo.set_MaxHP(35);
    	enemigo.set_name("Ara�a");
    	(enemigo.Batler).setimg("Monster/Spider.png");
    	(enemigo.Batler).x=180;
    	(enemigo.Batler).y=100;
    	(*myteam).add_enemy(enemigo);
    	enemigo.set_HP(20);
    	enemigo.set_MaxHP(20);
    	enemigo.set_name("Avisp�n");
    	(enemigo.Batler).setimg("Monster/Bee.png");
    	(enemigo.Batler).x=140;
    	(enemigo.Batler).y=60;
    	(*myteam).add_enemy(enemigo);
    	* NScene=2;
    }*/
}

void Map_Scene::dispose()
{
    unsigned int i;

    red.dispose();
    //(*player).dispose();
    for (i = 0; i < Charas_nps.size(); i++)
    {
        Charas_nps[i].dispose();
    }

    myteam->actual_x_map=Actor.GridX;
    myteam->actual_y_map=Actor.GridY;
    Actor.dispose();
    Charas_nps.clear();
    pre_chip.dispose();
    alexface.dispose();
    myaudio->stop();
}
