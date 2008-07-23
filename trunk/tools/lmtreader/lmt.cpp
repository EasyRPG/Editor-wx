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

enum eLMTChunks
{
	CHUNK_NAME		= 0x01,	///< nombre del mapa
	CHUNK_IDF		= 0x02,	///< ID del mapa padre 
	CHUNK_DEPTH		= 0x03,	///< Profundidad del árbol 
	CHUNK_FAREA		= 0x04,	///< Bandera de mapa o área 
	CHUNK_XBAR		= 0x05,	///< Barra de desplazamiento  X del mapa
	CHUNK_YBAR		= 0x06,	///< Barra de desplazamiento Y del mapa
	CHUNK_SON		= 0x07,	///< Tiene subrama (hijo)
	CHUNK_FMUSIC		= 0x0B,	///< Música de fondo
	CHUNK_SMUSIC		= 0x0C,	///< Música de fondo (archivo) String
	CHUNK_FBATLE		= 0x15,	///< Fondo de batalla 
	CHUNK_SBATLE		= 0x16,	///< Fondo de batalla (archivo) String
	CHUNK_FTELEP		= 0x1F,	///< Teletransporte
	CHUNK_FESCAPE		= 0x20,	///< posibilidad de escape en batalla
	CHUNK_FSAVE		= 0x21,	///< posiblilidad de gravar
	CHUNK_AENEMYS		= 0x29,	///< Encuentros enemigos
	CHUNK_FNUMSTEP		= 0x2C,	///< Numero de pasos entre encuentros
	CHUNK_MAP_END_OF_BLOCK	= 0x00
};
enum eLMTChunks2 
{
	CHUNK_PartymapId	= 0x01,	///< Party start map
	CHUNK_PartymapX		= 0x02,	///< Party start X
	CHUNK_PartymapY		= 0x03,	///< Party start Y
	CHUNK_SkiffId		= 0x0B,	///< Skiff start map
	CHUNK_SkiffX		= 0x0C,	///< Skiff start X
	CHUNK_SkiffY		= 0x0D,	///< Skiff start Y
	CHUNK_BoatId		= 0x15,	///< Boat start map
	CHUNK_BoatX		= 0x16,	///< Boat start X
	CHUNK_BoatY		= 0x17,	///< Boat start Y
	CHUNK_AirshipId		= 0x1F,	///< Airship start map
	CHUNK_AirshipX		= 0x20,	///< Airship start X
	CHUNK_AirshipY		= 0x21	///< Airship start Y
};
bool lmt::load(std::string filename)
{
	unsigned char Void;
	tChunk ChunkInfo;
	// Open map file to read
	FILE * file;// apertura de archivo
	file = fopen(filename.c_str(), "rb");
	std::string header = read_string(file); // lectura de cabecera
	if (header != "LcfMapTree") // comparacion con cabecera del mapa
	{
		printf("Reading error: File is not a valid RPG2000 map tree\n");
		fclose(file);
		return false;
	}
	size = read_int(file);
	read_tree(file);
	fread(&Void, sizeof(char), 1, file);//00 final de bloque
	//orden en el que deve ser mostrado el arbol
	int data = size;
	int dat;
	while(data--) // datos de como deve ser mostrado el arbol
	{
		dat = read_int(file);
		order.push_back(dat);
	}
	// Initialize
	start_map_id	= 0;
	start_x		= 0;
	start_y		= 0;
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
		ChunkInfo.ID	 = read_int(file); // lectura de tipo del pedazo
		ChunkInfo.Length = read_int(file); // lectura de su tamaño
		switch(ChunkInfo.ID) // segun el tipo
		{
			case CHUNK_PartymapId:
				start_map_id	= read_int(file);
				break;
			case CHUNK_PartymapX:
				start_x		= read_int(file);
				break;
			case CHUNK_PartymapY:
				start_y		= read_int(file);
				break;
			case CHUNK_SkiffId:
				skiff_map_id	= read_int(file);
				break;
			case CHUNK_SkiffX:
				skiff_x		= read_int(file);
				break;
			case CHUNK_SkiffY:
				skiff_y		= read_int(file);
				break;
			case CHUNK_BoatId:
				boat_map_id	= read_int(file);
				break;
			case CHUNK_BoatX:
				boat_x		= read_int(file);
				break;
			case CHUNK_BoatY:
				boat_y		= read_int(file);
				break;
			case CHUNK_AirshipId:
				 airship_map_id	= read_int(file);
				break;
			case CHUNK_AirshipX:
				airship_x	= read_int(file);
				break;
			case CHUNK_AirshipY:
				airship_y	= read_int(file);
				break;
			default:
				// saltate un pedazo del tamaño de la longitud
				while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, file);
				break;
		}
	}
	fclose(file);
	return true;
}
void lmt::clear(item * leaf)
{
	(*leaf).name			= "";	///< 0x01 nombre del mapa
	(*leaf).parent_id		= 0;	///< 0x02 ID del mapa padre 
	(*leaf).depth			= 0;	///< 0x03 Profundidad del árbol 
	(*leaf).type			= 0;	///< 0x04 Bandera de mapa o área 
	(*leaf).scrollbar_x		= 0;	///< 0x05 Barra de desplazamiento  X del mapa
	(*leaf).scrollbar_y		= 0;	///< 0x06 Barra de desplazamiento Y del mapa
	(*leaf).expanded		= 0;	///< 0x07 Tiene subrama (hijo)
	(*leaf).bgm			= 0;	///< 0x0B Música de fondo 
	(*leaf).bgm_file.name		= "";	///< 0x0C Música de fondo (archivo) String
	(*leaf).bgm_file.fade_in	= 0;
	(*leaf).bgm_file.volume		= 100;
	(*leaf).bgm_file.tempo		= 100;
	(*leaf).bgm_file.balance	= 50;
	(*leaf).battle			= 0;	///< 0x15 Fondo de batalla 
	(*leaf).battle_file		= "";	///< 0x16 Fondo de batalla (archivo) String
	(*leaf).teleport		= 0;	///< 0x1F Teletransporte
	(*leaf).escape			= 0;	///< 0x20 Escapar
	(*leaf).save			= 0;	///< 0x21 Guardar
	(*leaf).encounter.clear();		///< 0x29 grupo de enemigos
	(*leaf).encounter_steps		= 0;	///< 0x2C Pasos entre encuentros
}
void lmt::read_tree(FILE * file)
{
	int enemygroups	= 0;
	int idgroup	= 0;
	int enemy	= 0;
	int nodes	= 0;
	int temp	= 0;
	read_int(file);
	tChunk ChunkInfo; // informacion del pedazo leido
	unsigned char Void;
	item leaf;
	clear(&leaf);
	// Loop while we haven't reached the end of the file
	while(nodes < size)
	{
		ChunkInfo.ID		= read_int(file); // lectura de tipo del pedazo
		ChunkInfo.Length	= read_int(file); // lectura de su tamaño
		switch(ChunkInfo.ID) // segun el tipo
		{
			case CHUNK_NAME:
				leaf.name		= read_string(file, ChunkInfo.Length);
				break;
			case CHUNK_IDF:
				leaf.parent_id		= read_int(file);
				break;
			case CHUNK_DEPTH:
				leaf.depth		= read_int(file);
				break;
			case CHUNK_FAREA:
				leaf.type		= read_int(file);
				break;
			case CHUNK_XBAR:
				leaf.scrollbar_x	= read_int(file);
				break;
			case CHUNK_YBAR:
				leaf.scrollbar_y	= read_int(file);
				break;
			case CHUNK_SON:
				leaf.expanded		= read_int(file);
				break;
			case CHUNK_FMUSIC:
				leaf.bgm		= read_int(file); 
				break;
			case CHUNK_SMUSIC:
				while (ChunkInfo.ID != 0)
				{
					ChunkInfo.ID = read_int(file); // lectura de tipo del pedazo
					if(ChunkInfo.ID!=0)
						ChunkInfo.Length = read_int(file); // lectura de su tamaño					switch(ChunkInfo.ID)// segun el tipo
					{
						case 0x01:
							leaf.bgm_file.name	= read_string(file, ChunkInfo.Length);
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
							while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, file);
							break;
					}
				}
				break;
			case CHUNK_FBATLE:
				leaf.battle		= read_int(file);
				break;
			case CHUNK_SBATLE:
				leaf.battle_file	= read_string(file, ChunkInfo.Length);
				break;
			case CHUNK_FTELEP:
				leaf.teleport		= read_int(file);
				break;
			case CHUNK_FESCAPE:
				leaf.escape		= read_int(file);
				break;
			case CHUNK_FSAVE:
				leaf.save		= read_int(file);
				break;
			case CHUNK_AENEMYS:
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
			case CHUNK_FNUMSTEP:
				leaf.encounter_steps = read_int(file);
				break;
			case CHUNK_MAP_END_OF_BLOCK:
				break;
			case 51: //0x33 Area data
				fread(&(leaf.area_start_x), (sizeof(int)), 1, file);
				fread(&(leaf.area_start_y), (sizeof(int)), 1, file);
				fread(&(leaf.area_end_x), (sizeof(int)), 1, file);
				fread(&(leaf.area_end_y), (sizeof(int)), 1, file);
				list.push_back(leaf);
				clear(&leaf);
				nodes++;
				while(nodes != temp) // sirve para quitar el fin del chunk y el id del siguiente
				temp = read_int(file);
				break;
			default:
				// saltate un pedazo del tamaño de la longitud
				while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, file);
				break;
		}
	}
}
void lmt::print() // muestra de informacion del mapa
{
	int j;
	unsigned int i;
	printf("=============================================\n");
	printf("Listado de mapas\n");
	for (j=0; j < size; j++)
	{
		printf("----------------------------------------------\n");
		printf("Nombre:				%s\n", list[j].name.c_str());
		printf("ID del mapa padre:		%d\n", list[j].parent_id);
		printf("Profundidad:			%d\n", list[j].depth);
		printf("Tipo (0=raiz, 1=mapa, 2=area):	%d\n", list[j].type);
		printf("Barras de desplazamiento:	X = %d, Y = %d\n", list[j].scrollbar_x, list[j].scrollbar_y);
		printf("Rama expandida?:		%d\n", list[j].expanded);
		printf("Tiene musica de fondo?:		%d\n", list[j].bgm);
		printf("Nombre musica:			%s\n", list[j].bgm_file.name.c_str());
		printf("Fade in musica:			%d\n", list[j].bgm_file.fade_in);
		printf("Volumen musica:			%d\n", list[j].bgm_file.volume);
		printf("Tempo musica:			%d\n", list[j].bgm_file.tempo);
		printf("Balance musica:			%d\n", list[j].bgm_file.balance);
		printf("Tiene fondo de batalla?:	%d\n", list[j].battle);
		printf("Nombre fondo:			%s\n", list[j].battle_file.c_str());
		printf("Permite teletrasporte?		%d\n", list[j].teleport);
		printf("Permite escapar?:		%d\n", list[j].escape);
		printf("Permite guardar?:		%d\n", list[j].save);
		for(i = 0; i < list[j].encounter.size(); i++)
		{
			printf("Grupo enemigo:			%d\n", list[j].encounter[i]);
		}
		printf("Pasos para encuentro enemigo:	%d\n", list[j].encounter_steps);
		printf("Inicio de area:			X = %d, Y = %d\n", list[j].area_start_x, list[j].area_start_y);
		printf("Fin de area:			X = %d, Y = %d\n", list[j].area_end_y, list[j].area_end_y);
	}
	printf("==============================================\n");
	printf("Fin del listado de mapas. Datos del final:\n");
	printf("----------------------------------------------\n");
	printf("Orden de las hojas:		");
	for(j = 0; j < (size - 1); j++)
	{
		printf("%d ", order[j]);
	}
	printf("\nHoja seleccionada:		%d\n", order[j]);
	printf("----------------------------------------------\n");
	printf("Start party map ID:		%d\n", start_map_id);
	printf("Start party X:			%d\n", start_x);
	printf("party Y:			%d\n", start_y);
	printf("Skiff map ID:			%d\n", skiff_map_id);
	printf("Skiff X:			%d\n", skiff_x);
	printf("Skiff Y:			%d\n", skiff_y);
	printf("Boat map ID:			%d\n", boat_map_id);
	printf("Boat X:				%d\n", boat_x);
	printf("Boat Y:				%d\n", boat_y);
	printf("Airship map ID:			%d\n", airship_map_id);
	printf("Airship X:			%d\n", airship_x);
	printf("Airship Y:			%d\n", airship_y);
}

