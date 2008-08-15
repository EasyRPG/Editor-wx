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
	FILE		* file;
	std::string	header;
	char		* dummy;
	int		remaining_nodes;
	int		node;
	int		vehicle_chunk_id;
	int		vehicle_chunk_size;

	file = fopen(filename.c_str(), "rb");
	//check if the file is valid, if not...
	if(file == null)
	{
	    printf("The file %s is not valid, make sure the file exists and you have read privileges on it.\n");
        return false;
	}
	//Read header
	header = read_string(file);
	if(header != "LcfMapTree")
	{
		printf("Reading error: File is not a valid RPG2000 map tree.\n");
		fclose(file);
		return false;
	}
	//Read number of nodes
	total_nodes = read_int(file);
	//Read tree
	read_tree(file);
	fread(dummy, 1, 1, file); //00 end of block
	//Read tree order
	remaining_nodes = total_nodes;
	while(remaining_nodes--)
	{
		node = read_int(file);
		tree_order.push_back(node);
	}
	//Read vehicles (if any)
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
		vehicle_chunk_id	= read_int(file);
		vehicle_chunk_size	= read_int(file);
		switch(vehicle_chunk_id)
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
			case 0: //0x00
				if (vehicle_chunk_size != 0)
				{
					printf("WARNING: Unexpected byte after end of block. Size: %d\n", vehicle_chunk_size);
				}
				break;
			default:
				printf("WARNING: Unknown vehicle block ID: %d (size: %d)\n", vehicle_chunk_id, vehicle_chunk_size);
				// skip unknown vehicle_chunk_id case
				while(vehicle_chunk_size--)
				{
					fread(dummy, 1, 1, file);
					printf("	Byte read: %s\n", dummy);
				}
				break;
		}
	}
	fclose(file);
	return true;
}

void lmt::clear(node * node)
{
	(*node).name			= "";
	(*node).parent_id		= 0;
	(*node).depth			= 0;
	(*node).type			= 0;
	(*node).scrollbar_x		= 0;
	(*node).scrollbar_y		= 0;
	(*node).expanded		= 0;
	(*node).bgm			= 0;
	(*node).bgm_file.name		= "";
	(*node).bgm_file.fade_in	= 0;
	(*node).bgm_file.volume		= 100;
	(*node).bgm_file.tempo		= 100;
	(*node).bgm_file.balance	= 50;
	(*node).battle			= 0;
	(*node).battle_file		= "";
	(*node).teleport		= 0;
	(*node).escape			= 0;
	(*node).save			= 0;
	(*node).encounter.clear();
	(*node).encounter_steps		= 0;
}

void lmt::read_tree(FILE * file)
{
	int enemygroups		= 0;
	int idgroup		= 0;
	int enemy		= 0;
	int current_node	= 0;
	node			node;
	char			* dummy;
	int			node_chunk_id;
	int			node_chunk_size;

	read_int(file);
	clear(&node);
	// Loop while we haven't reached the end of the file
	while(current_node < total_nodes)
	{
		node_chunk_id	= read_int(file); // lectura de tipo del pedazo
		node_chunk_size	= read_int(file); // lectura de su tamaño
		switch(node_chunk_id) // segun el tipo
		{
			case 1:
				node.name		= read_string(file, node_chunk_size);
				break;
			case 2:
				node.parent_id		= read_int(file);
				break;
			case 3:
				node.depth		= read_int(file);
				break;
			case 4: //
				node.type		= read_int(file);
				break;
			case 5:
				node.scrollbar_x	= read_int(file);
				break;
			case 6:
				node.scrollbar_y	= read_int(file);
				break;
			case 7:
				node.expanded		= read_int(file);
				break;
			case 11: //0x0B
				node.bgm		= read_int(file);
				break;
			case 12:
				while(node_chunk_id != 0) //FIXME esta utilizando la misma variable para un bucle anidado
				{
					node_chunk_id = read_int(file);
					if(node_chunk_id != 0)
					{
						node_chunk_size = read_int(file);
					}
					switch(node_chunk_id)
					{
						case 0x01:
							node.bgm_file.name	= read_string(file, node_chunk_size);
							break;
						case 0x02:
							node.bgm_file.fade_in	= read_int(file);
							break;
						case 0x03:
							node.bgm_file.volume	= read_int(file);
							break;
						case 0x04:
							node.bgm_file.tempo	= read_int(file);
							break;
						case 0x05:
							node.bgm_file.balance	= read_int(file);
							break;
						case 0x00:
							break;
						default:
							printf("WARNING: Unknown BGM block ID: %d (size: %d)\n", node_chunk_id, node_chunk_size);
							// skip unknown vehicle_chunk_id case
							while(node_chunk_size--)
							{
								fread(dummy, 1, 1, file);
								printf("	Byte read: %s\n", dummy);
							}
							break;
					}
				}
				break;
			case 21: //0x15
				node.battle		= read_int(file);
				break;
			case 22: //0x16
				node.battle_file	= read_string(file, node_chunk_size);
				break;
			case 31: //0x1F
				node.teleport		= read_int(file);
				break;
			case 32: //0x20
				node.escape		= read_int(file);
				break;
			case 33: //0x21
				node.save		= read_int(file);
				break;
			case 41: //0x29
				enemygroups	= read_int(file); // numero de grupos
				idgroup = 0;
				while(idgroup < enemygroups)
				{
					idgroup		= read_int(file); //id de dato
					// no se para que escribieron los dos primeros enteros pero el 3ro es el id de grupo
					// probablemente quedo incompleto el rm2k
							read_int(file);
							read_int(file);
					enemy		= read_int(file);
					node.encounter.push_back(enemy);
					read_int(file); //fin de bloque
				}
				break;
			case 44: //0x2C
				node.encounter_steps = read_int(file);
				break;
			case 51: //0x33 Area data
				fread(&(node.area_start_x),	4, 1, file);
				fread(&(node.area_start_y),	4, 1, file);
				fread(&(node.area_end_x),	4, 1, file);
				fread(&(node.area_end_y),	4, 1, file);
				tree_list.push_back(node);
				break;
			case 0: //End of block
				clear(&node);
				current_node++;
				break;
			default:
				printf("WARNING: Unknown node block ID: %d (size: %d)\n", node_chunk_id, node_chunk_size);
				// skip unknown vehicle_chunk_id case
				while(node_chunk_size--)
				{
					fread(dummy, 1, 1, file);
					printf("	Byte read: %s\n", dummy);
				}
				break;
		}
	}
}

void lmt::print() // muestra de informacion del mapa
{
	int current_node;
	unsigned int i;
	printf("==================================================================\n");
	printf("Map tree\n");
	for(current_node = 0; current_node < total_nodes; current_node++)
	{
		printf("------------------------------------------------------------------\n");
		printf("Name:								%s\n", tree_list[current_node].name.c_str());
		printf("Parent ID:							%d\n", tree_list[current_node].parent_id);
		printf("Depth:								%d\n", tree_list[current_node].depth);
		printf("Type (0=root, 1=map, 2=area):					%d\n", tree_list[current_node].type);
		printf("Scrollbars:							%d,%d\n", tree_list[current_node].scrollbar_x, tree_list[current_node].scrollbar_y);
		printf("Is expanded?:							%d\n", tree_list[current_node].expanded);
		printf("Has BGM? (0=inherit, 1=don't change, 2=specify):		%d\n", tree_list[current_node].bgm);
		printf("BGM name:							%s\n", tree_list[current_node].bgm_file.name.c_str());
		printf("BGM fade in:							%d\n", tree_list[current_node].bgm_file.fade_in);
		printf("BGM volume:							%d\n", tree_list[current_node].bgm_file.volume);
		printf("BGM tempo:							%d\n", tree_list[current_node].bgm_file.tempo);
		printf("BGM balance:							%d\n", tree_list[current_node].bgm_file.balance);
		printf("Has battle background? (0=inherit, 1=don't change, 2=specify):	%d\n", tree_list[current_node].battle);
		printf("battle baground name:						%s\n", tree_list[current_node].battle_file.c_str());
		printf("Teleport options (0=inherit, 1=don't change, 2=specify):	%d\n", tree_list[current_node].teleport);
		printf("Escape options (0=inherit, 1=don't change, 2=specify):		%d\n", tree_list[current_node].escape);
		printf("Save options (0=inherit, 1=don't change, 2=specify):		%d\n", tree_list[current_node].save);
		for(i = 0; i < tree_list[current_node].encounter.size(); i++)
		{
			printf("Enemy encounter:						%d\n", tree_list[current_node].encounter[i]);
		}
		printf("Encounter steps:						%d\n", tree_list[current_node].encounter_steps);
		printf("Area coordinates:						%d,%d-%d,%d\n", tree_list[current_node].area_start_x, tree_list[current_node].area_start_y, tree_list[current_node].area_end_y, tree_list[current_node].area_end_y);
	}
	printf("==================================================================\n");
	printf("End of tree. Data after the tree:\n");
	printf("------------------------------------------------------------------\n");
	printf("Branch order:							");
	for(current_node = 0; current_node < (total_nodes - 1); current_node++)
	{
		printf("%d ", tree_order[current_node]);
	}
	printf("\nSelected branch:						%d\n", tree_order[current_node]);
	printf("------------------------------------------------------------------\n");
	printf("Party map ID:							%d\n", party_map_id);
	printf("Party X:							%d\n", party_x);
	printf("Party Y:							%d\n", party_y);
	printf("Skiff map ID:							%d\n", skiff_map_id);
	printf("Skiff X:							%d\n", skiff_x);
	printf("Skiff Y:							%d\n", skiff_y);
	printf("Boat map ID:							%d\n", boat_map_id);
	printf("Boat X:								%d\n", boat_x);
	printf("Boat Y:								%d\n", boat_y);
	printf("Airship map ID:							%d\n", airship_map_id);
	printf("Airship X:							%d\n", airship_x);
	printf("Airship Y:							%d\n", airship_y);
}
