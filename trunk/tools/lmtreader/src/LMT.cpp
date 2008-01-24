#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "tools.h"
#include "LMT.h"

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
bool LMT::Load(std::string Filename)
{
	unsigned char Void;
	tChunk ChunkInfo;
	// Open map file to read
	FILE * Stream;// apertura de archivo
	Stream = fopen(Filename.c_str(), "rb");
	std::string Header = ReadString(Stream); // lectura de cabecera
	if (Header != "LcfMapTree") // comparacion con cabecera del mapa
	{
		printf("Reading error: File is not a valid RPG2000 map tree\n");
		fclose(Stream);
		return false;
	}
	treesize = ReadCompressedInteger(Stream);
	GetNextChunk(Stream);
	fread(&Void, sizeof(char), 1, Stream);//00 final de bloque
	//ReadString(Stream, treesize);//Party to encounter caracteres que aun no entiendo, hay uno por cada hoja del mapa
	//orden en el que deve ser mostrado el arbol
	int data = treesize;
	int dat;
	while(data--) // datos de como deve ser mostrado el arbol
	{
		dat = ReadCompressedInteger(Stream);
		vc_int_treeorder.push_back(dat);
	}
	while(!feof(Stream))
	{
		ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo
		ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño
		switch(ChunkInfo.ID) // segun el tipo
		{
			case CHUNK_PartymapId:
				intPartymapId	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_PartymapX:
				intPartymapX	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_PartymapY:
				intPartymapY	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_SkiffId:
				intSkiffId	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_SkiffX:
				intSkiffX	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_SkiffY:
				intSkiffY	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_BoatId:
				intBoatId	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_BoatX:
				intBoatX	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_BoatY:
				intBoatY	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_AirshipId:
				 intAirshipId	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_AirshipX:
				intAirshipX	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_AirshipY:
				intAirshipY	= ReadCompressedInteger(Stream);
				break;
			default:
				// saltate un pedazo del tamaño de la longitud
				while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
				break;
		}
	}
	fclose(Stream);
	return true;
}
void LMT::leafclear( DataofTree * leaf)
{
	(*leaf).strName		= "";	///< 0x01 nombre del mapa
	(*leaf).intIdMapF	= 0;	///< 0x02 ID del mapa padre 
	(*leaf).intDepth	= 0;	///< 0x03 Profundidad del árbol 
	(*leaf).intFlagMA	= 0;	///< 0x04 Bandera de mapa o área 
	(*leaf).intXbar		= 0;	///< 0x05 Barra de desplazamiento  X del mapa
	(*leaf).intYbar		= 0;	///< 0x06 Barra de desplazamiento Y del mapa
	(*leaf).intSon		= 0;	///< 0x07 Tiene subrama (hijo)
	(*leaf).intMusic	= 0;	///< 0x0B Música de fondo 
	(*leaf).stcMusic.Name_of_Sound_effect	= "";	///< 0x0C Música de fondo (archivo) String
	(*leaf).stcMusic.Fadein=0;
	(*leaf).stcMusic.Volume=100;
	(*leaf).stcMusic.Tempo=100;
	(*leaf).stcMusic.Balance=50;
	(*leaf).intBatle	= 0;	///< 0x15 Fondo de batalla 
	(*leaf).strBatle	= "";	///< 0x16 Fondo de batalla (archivo) String
	(*leaf).intTelepor	= 0;	///< 0x1F Teletransporte
	(*leaf).intScape	= 0;	///< 0x20 Escapar
	(*leaf).intSave		= 0;	///< 0x21 Guardar
	(*leaf).vcEnemyGroup.clear();	///< 0x29 grupo de enemigos
	(*leaf).intNofsteeps	= 0;	///< 0x2C Pasos entre encuentros
}
	void LMT::GetNextChunk(FILE * Stream)
{
	 int enemygroups=0,idgroup=0,enemy=0;
	 unsigned int nodes=0, temp=0;
		ReadCompressedInteger(Stream);
		tChunk ChunkInfo; // informacion del pedazo leido
		unsigned char Void;
		DataofTree leaf;
		leafclear(&leaf);
		// Loop while we haven't reached the end of the file
		while(nodes < treesize)
		{
			ChunkInfo.ID		= ReadCompressedInteger(Stream); // lectura de tipo del pedazo
			ChunkInfo.Length	= ReadCompressedInteger(Stream); // lectura de su tamaño
			switch(ChunkInfo.ID) // segun el tipo
			{
				case CHUNK_NAME:
					leaf.strName	= ReadString(Stream, ChunkInfo.Length);
					break;
				case CHUNK_IDF:
					leaf.intIdMapF	= ReadCompressedInteger(Stream);
					break;
				case CHUNK_DEPTH:
					leaf.intDepth	= ReadCompressedInteger(Stream);
					break;
				case CHUNK_FAREA:
					leaf.intFlagMA	= ReadCompressedInteger(Stream);
					break;
				case CHUNK_XBAR:
					leaf.intXbar	= ReadCompressedInteger(Stream);
					break;
				case CHUNK_YBAR:
					leaf.intYbar	= ReadCompressedInteger(Stream);
					break;
				case CHUNK_SON:
					leaf.intSon	= ReadCompressedInteger(Stream);
					break;
				case CHUNK_FMUSIC:
					leaf.intMusic	= ReadCompressedInteger(Stream); 
					break;
				case CHUNK_SMUSIC:
					while (ChunkInfo.ID!=0)  
					{
						ChunkInfo.ID = ReadCompressedInteger(Stream); // lectura de tipo del pedazo
						if(ChunkInfo.ID!=0)
							ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño						switch(ChunkInfo.ID)// segun el tipo
						{
							case 0x01:
								leaf.stcMusic.Name_of_Sound_effect = ReadString(Stream, ChunkInfo.Length);
								break;
							case 0x02:
								leaf.stcMusic.Fadein = ReadCompressedInteger(Stream);
								break;
							case 0x03:
								leaf.stcMusic.Volume = ReadCompressedInteger(Stream);
								break;
							case 0x04:
								leaf.stcMusic.Tempo = ReadCompressedInteger(Stream);
								break;
							case 0x05:
								leaf.stcMusic.Balance = ReadCompressedInteger(Stream);
								break;
							case 0x00:
								break;
							default:
								while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
								break;
						}
					}
					break;
			case CHUNK_FBATLE:
				leaf.intBatle	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_SBATLE:
				leaf.strBatle	= ReadString(Stream, ChunkInfo.Length);
				break;
			case CHUNK_FTELEP:
				leaf.intTelepor	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_FESCAPE:
				leaf.intScape	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_FSAVE:
				leaf.intSave	= ReadCompressedInteger(Stream);
				break;
			case CHUNK_AENEMYS:
				enemygroups	= ReadCompressedInteger(Stream); // numero de grupos
				while(idgroup < enemygroups)
				{
					idgroup		= ReadCompressedInteger(Stream); //id de dato
					// no se para que escribieron los dos primeros enteros pero el 3ro es el id de grupo
					// probablemente quedo incompleto el rm2k
							ReadCompressedInteger(Stream);
							ReadCompressedInteger(Stream);
					enemy		= ReadCompressedInteger(Stream);
					leaf.vcEnemyGroup.push_back(enemy);
					ReadCompressedInteger(Stream); //fin de bloque
				}
				break; 
			case CHUNK_FNUMSTEP:
				leaf.intNofsteeps = ReadCompressedInteger(Stream);
				break;
			case CHUNK_MAP_END_OF_BLOCK:
				break;
			case 51:
				// 4 datos estrictamente de 4 bytes
				fread(&(leaf.intAreaX1), (sizeof(int)), 1, Stream);
				fread(&(leaf.intAreaY1), (sizeof(int)), 1, Stream);
				fread(&(leaf.intAreaX2), (sizeof(int)), 1, Stream);
				fread(&(leaf.intAreaY2), (sizeof(int)), 1, Stream);
				str_Vector.push_back(leaf);
				leafclear(&leaf);
				nodes++;
				while(nodes!=temp) // sirve para quitar el fin del chunk y el id del siguiente
				temp = ReadCompressedInteger(Stream);
				break;
			default:
				// saltate un pedazo del tamaño de la longitud
				while(ChunkInfo.Length--) fread(&Void, sizeof(char), 1, Stream);
				break;
		}
	}
}
void LMT::ShowInformation() // muestra de informacion del mapa
{
	unsigned int j, i;
	for (j=0; j < treesize; j++)
	{
		printf("Nombre:				%s\n", str_Vector[j].strName.c_str());
		printf("ID del mapa padre:		%d\n", str_Vector[j].intIdMapF);
		printf("Profundidad:			%d\n", str_Vector[j].intDepth);
		printf("Tipo (0=raiz, 1=mapa, 2=area):	%d\n", str_Vector[j].intFlagMA);
		printf("Barras de desplazamiento:	X = %d, Y = %d\n", str_Vector[j].intXbar, str_Vector[j].intYbar);
		printf("Tiene subrama?:			%d\n", str_Vector[j].intSon);
		printf("Tiene musica de fondo?:		%d\n", str_Vector[j].intMusic);
		printf("Nombre musica:			%s\n", str_Vector[j].stcMusic.Name_of_Sound_effect.c_str());
		printf("Fade in musica:			%d\n", str_Vector[j].stcMusic.Fadein);
		printf("Volumen musica:			%d\n", str_Vector[j].stcMusic.Volume);
		printf("Tempo musica:			%d\n", str_Vector[j].stcMusic.Tempo);
		printf("Balance musica:			%d\n", str_Vector[j].stcMusic.Balance);
		printf("Tiene fondo de batalla?:	%d\n", str_Vector[j].intBatle);
		printf("Nombre fondo:			%s\n", str_Vector[j].strBatle.c_str());
		printf("Permite teletrasporte?		%d\n", str_Vector[j].intTelepor);
		printf("Permite guardar?:		%d\n", str_Vector[j].intScape);
		for(i=0; i < str_Vector[j].vcEnemyGroup.size(); i++)
		{
			printf("Grupo enemigo:			%d\n", str_Vector[j].vcEnemyGroup[i]);
		}
		printf("Pasos para encuentro enemigo:	%d\n", str_Vector[j].intNofsteeps);
		printf("Inicio de area:			X = %d, Y = %d\n", str_Vector[j].intAreaX1, str_Vector[j].intAreaY1);
		printf("Fin de area:			X = %d, Y = %d\n", str_Vector[j].intAreaX2,str_Vector[j].intAreaY2);
	}
	printf("ID party:			%d\n", intPartymapId);
	printf("Party X:			%d\n", intPartymapX);
	printf("party Y:			%d\n", intPartymapY);
	printf("ID Skiff:			%d\n", intSkiffId);
	printf("Skiff X:			%d\n", intSkiffX);
	printf("Skiff Y:			%d\n", intSkiffY);
	printf("id Boat:			%d\n", intBoatId);
	printf("Boat X:				%d\n", intBoatX);
	printf("Boat Y:				%d\n", intBoatY);
	printf("ID Airship:			%d\n", intAirshipId);
	printf("Airship X:			%d\n", intAirshipX);
	printf("Airship Y:			%d\n", intAirshipY);
	printf("Orden de las hojas:		");
	for(j = 0; j < (treesize - 1); j++)
	{
		printf("%d ",vc_int_treeorder[j]);
	}
	printf("\nHoja seleccionada:		%d\n", vc_int_treeorder[j]);
}

