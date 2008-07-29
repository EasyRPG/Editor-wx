/* lmt.cpp, LcfMapTree reader class.
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
#include <string>
#include <vector>
#include "tools.h"
#include "lmt.h"

bool lmt::load(std::string filename)
{
	FILE * file;
	std::string header;
	block vehicle;
	unsigned char dummy_byte;

	file = fopen(filename.c_str(), "rb");
	header = read_string(file); // lectura de cabecera
	if (header != "LcfMapTree") // comparacion con cabecera del mapa
	{
		printf("Reading error: File is not a valid RPG2000 map tree\n");
		fclose(file);
		return false;
	}
	size = read_int(file);
	read_tree(file);
	fread(&dummy_byte, 1, 1, file); //00 final de bloque
	//Tree order block
	int tree = size;
	int leaf;
	while(tree--) // datos de como debe ser mostrado el arbol
	{
		leaf = read_int(file);
		order.push_back(leaf);
	}
	// Initialize
	party_map_id	= 0;
	party_x		= 0;
	party_y		= 0;
	skiff_map_id	= 0;
	skiff_x		= 0;
	skiff_y		= 0;
	boat_map_id	= 0;
	boat_x		= 0;
	boat_y		= 0;
	airship_map_id	= 0;
	airship_x	= 0;
	airship_y	= 0;
	while(!feof(file))
	{
		vehicle.id	 = read_int(file); // lectura de tipo del pedazo
		vehicle.size = read_int(file); // lectura de su tamaño
		switch(vehicle.id) // segun el tipo
		{
			case 1: //0x01
				party_map_id	= read_int(file);
				break;
			case 2: //0x02
				party_x		= read_int(file);
				break;
			case 3: //0x03
				party_y		= read_int(file);
				break;
			case 11: //0x0B
				skiff_map_id	= read_int(file);
				break;
			case 12: //0x0C
				skiff_x		= read_int(file);
				break;
			case 13: //0x0D
				skiff_y		= read_int(file);
				break;
			case 21: //0x15
				boat_map_id	= read_int(file);
				break;
			case 22: //0x16
				boat_x		= read_int(file);
				break;
			case 23: //0x17
				boat_y		= read_int(file);
				break;
			case 31: //0x1F
				airship_map_id	= read_int(file);
				break;
			case 32: //0x20
				airship_x	= read_int(file);
				break;
			case 33: //0x21
				airship_y	= read_int(file);
				break;
			default:
				// saltate un pedazo del tamaño de la longitud
				while(vehicle.size--)
				{
					fread(&dummy_byte, 1, 1, file);
				}
				break;
		}
	}
	fclose(file);
	return true;
}
void lmt::clear(item * leaf)
{
	(*leaf).name			= "";
	(*leaf).parent_id		= 0;
	(*leaf).depth			= 0;
	(*leaf).type			= 0;
	(*leaf).scrollbar_x		= 0;
	(*leaf).scrollbar_y		= 0;
	(*leaf).expanded		= 0;
	(*leaf).bgm			= 0;
	(*leaf).bgm_file.name		= "";
	(*leaf).bgm_file.fade_in	= 0;
	(*leaf).bgm_file.volume		= 100;
	(*leaf).bgm_file.tempo		= 100;
	(*leaf).bgm_file.balance	= 50;
	(*leaf).battle			= 0;
	(*leaf).battle_file		= "";
	(*leaf).teleport		= 0;
	(*leaf).escape			= 0;
	(*leaf).save			= 0;
	(*leaf).encounter.clear();
	(*leaf).encounter_steps		= 0;
}
void lmt::read_tree(FILE * file)
{
	int enemygroups	= 0;
	int idgroup	= 0;
	int enemy	= 0;
	int nodes	= 0;
	int temp	= 0;
	read_int(file);
	block branch;
	item leaf;
	unsigned char dummy_byte;
	clear(&leaf);
	// Loop while we haven't reached the end of the file
	while(nodes < size)
	{
		branch.id		= read_int(file); // lectura de tipo del pedazo
		branch.size	= read_int(file); // lectura de su tamaño
		switch(branch.id) // segun el tipo
		{
			case 1:
				leaf.name		= read_string(file, branch.size);
				break;
			case 2:
				leaf.parent_id		= read_int(file);
				break;
			case 3:
				leaf.depth		= read_int(file);
				break;
			case 4: //
				leaf.type		= read_int(file);
				break;
			case 5:
				leaf.scrollbar_x	= read_int(file);
				break;
			case 6:
				leaf.scrollbar_y	= read_int(file);
				break;
			case 7:
				leaf.expanded		= read_int(file);
				break;
			case 11: //0x0B
				leaf.bgm		= read_int(file);
				break;
			case 12:
				while (branch.id != 0)
				{
					branch.id = read_int(file);
					if(branch.id != 0)
					{
						branch.size = read_int(file);
					}					switch(branch.id)
					{
						case 0x01:
							leaf.bgm_file.name	= read_string(file, branch.size);
							break;
						case 0x02:
							leaf.bgm_file.fade_in	= read_int(file);
							break;
						case 0x03:
							leaf.bgm_file.volume	= read_int(file);
							break;
						case 0x04:
							leaf.bgm_file.tempo	= read_int(file);
							break;
						case 0x05:
							leaf.bgm_file.balance	= read_int(file);
							break;
						case 0x00:
							break;
						default:
							while(branch.size--)
							{
								fread(&dummy_byte, 1, 1, file);
							}
							break;
					}
				}
				break;
			case 21: //0x15
				leaf.battle		= read_int(file);
				break;
			case 22: //0x16
				leaf.battle_file	= read_string(file, branch.size);
				break;
			case 31: //0x1F
				leaf.teleport		= read_int(file);
				break;
			case 32: //0x20
				leaf.escape		= read_int(file);
				break;
			case 33: //0x21
				leaf.save		= read_int(file);
				break;
			case 41: //0x29
				enemygroups		= read_int(file); // numero de grupos
				idgroup = 0;
				while(idgroup < enemygroups)
				{
					idgroup		= read_int(file); //id de dato
					// no se para que escribieron los dos primeros enteros pero el 3ro es el id de grupo
					// probablemente quedo incompleto el rm2k
							read_int(file);
							read_int(file);
					enemy		= read_int(file);
					leaf.encounter.push_back(enemy);
					read_int(file); //fin de bloque
				}
				break;
			case 44: //0x2C
				leaf.encounter_steps = read_int(file);
				break;
			case 51: //0x33 Area data
				fread(&(leaf.area_start_x),	4, 1, file);
				fread(&(leaf.area_start_y),	4, 1, file);
				fread(&(leaf.area_end_x),	4, 1, file);
				fread(&(leaf.area_end_y),	4, 1, file);
				list.push_back(leaf);
				clear(&leaf);
				nodes++;
				while(nodes != temp) // sirve para quitar el fin del chunk y el id del siguiente
				temp = read_int(file);
				break;
			case 0: //End of block
				break;
			default:
				// saltate un pedazo del tamaño de la longitud
				while(branch.size--) fread(&dummy_byte, 1, 1, file);
				break;
		}
	}
}
void lmt::print() // muestra de informacion del mapa
{
	int j;
	unsigned int i;
	printf("==========================================================\n");
	printf("Listado de mapas\n");
	for (j=0; j < size; j++)
	{
		printf("----------------------------------------------------------\n");
		printf("Name:							%s\n", list[j].name.c_str());
		printf("Parent ID:						%d\n", list[j].parent_id);
		printf("Depth:							%d\n", list[j].depth);
		printf("Type (0=root, 1=map, 2=area):				%d\n", list[j].type);
		printf("Scrollbars:						X = %d, Y = %d\n", list[j].scrollbar_x, list[j].scrollbar_y);
		printf("Is expanded?:						%d\n", list[j].expanded);
		printf("Has BGM? (0=inherit, 1=don't change, 2=specify):	%d\n", list[j].bgm);
		printf("BGM name:						%s\n", list[j].bgm_file.name.c_str());
		printf("BGM fade in:						%d\n", list[j].bgm_file.fade_in);
		printf("BGM volume:						%d\n", list[j].bgm_file.volume);
		printf("BGM tempo:						%d\n", list[j].bgm_file.tempo);
		printf("BGM balance:						%d\n", list[j].bgm_file.balance);
		printf("Has battle background?:					%d\n", list[j].battle);
		printf("battle baground name:					%s\n", list[j].battle_file.c_str());
		printf("Teleport options (0=inherit, 1=don't change, 2=specify):%d\n", list[j].teleport);
		printf("Escape options (0=inherit, 1=don't change, 2=specify):	%d\n", list[j].escape);
		printf("Permite guardar?:					%d\n", list[j].save);
		for(i = 0; i < list[j].encounter.size(); i++)
		{
			printf("Grupo enemigo:						%d\n", list[j].encounter[i]);
		}
		printf("Pasos para encuentro enemigo:				%d\n", list[j].encounter_steps);
		printf("Inicio de area:						X = %d, Y = %d\n", list[j].area_start_x, list[j].area_start_y);
		printf("Fin de area:						X = %d, Y = %d\n", list[j].area_end_y, list[j].area_end_y);
	}
	printf("==========================================================\n");
	printf("End of tree. Data after the tree:\n");
	printf("----------------------------------------------------------\n");
	printf("Branch order:					");
	for(j = 0; j < (size - 1); j++)
	{
		printf("%d ", order[j]);
	}
	printf("\Selected branch:					%d\n", order[j]);
	printf("----------------------------------------------------------\n");
	printf("Party map ID:						%d\n", party_map_id);
	printf("Party X:						%d\n", party_x);
	printf("Party Y:						%d\n", party_y);
	printf("Skiff map ID:						%d\n", skiff_map_id);
	printf("Skiff X:						%d\n", skiff_x);
	printf("Skiff Y:						%d\n", skiff_y);
	printf("Boat map ID:						%d\n", boat_map_id);
	printf("Boat X:							%d\n", boat_x);
	printf("Boat Y:							%d\n", boat_y);
	printf("Airship map ID:						%d\n", airship_map_id);
	printf("Airship X:						%d\n", airship_x);
	printf("Airship Y:						%d\n", airship_y);
}

