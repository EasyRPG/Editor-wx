/* LMT.cpp, LMT.h, LcfMapTree RPG Maker 2000/2003 structure format.
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

#include "wx/wx.h"
#include "wx/ffile.h"
#include <vector>
#include "tools.h"
#include "LMT.h"

bool LMT::Load(const wxString Filename)
{
	wxByte Void;
	tChunk ChunkInfo;
	// Open map file to read
	wxFFile * Stream;
	Stream = new wxFFile(Filename, _T("rb")); // fopen()
	wxString Header = ReadString(Stream); // lectura de cabecera
	if (wxStrcmp(Header, _T("LcfMapTree"))) // comparacion con cabecera del mapa
	{
		wxMessageBox(_("File is not a valid RPG Maker 2000/2003 map tree"), _("Error reading RPG_RT.lmt data"), wxICON_ERROR);
		Stream->Close();
		return false;
	}
	treesize = ReadCompressedInteger(Stream);
	GetNextChunk(Stream);
	//Initialize/clear player and vehicle special events
	intPartymapId = 0;
	intPartymapX = 0;
	intPartymapY = 0;
	intSkiffId = 0;
	intSkiffX = 0;
	intSkiffY = 0;
	intBoatId = 0;
	intBoatX = 0;
	intBoatY = 0;
	intAirshipId = 0;
	intAirshipX = 0;
	intAirshipY = 0;

	Stream->Read(&Void, 1); // 00 final de bloque
	// orden en el que deve ser mostrado el arbol
	long data = treesize;
	long dat;
	while(data--) // datos de como debe ser mostrado el arbol
	{
		dat = ReadCompressedInteger(Stream);
		vc_int_treeorder.push_back(dat);
	}
	while(Stream->Eof())
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
				while(ChunkInfo.Length--) Stream->Read(&Void, 1);
				break;
		}
	}
	Stream->Close();
	return true;
}
void LMT::leafclear(DataofTree * leaf)
{
	(*leaf).strName		= _T("");	///< 0x01 nombre del mapa
	(*leaf).intIdMapF	= 0;	///< 0x02 ID del mapa padre
	(*leaf).intDepth	= 0;	///< 0x03 Profundidad del árbol
	(*leaf).intFlagMA	= 0;	///< 0x04 Bandera de mapa o área
	(*leaf).intXbar		= 0;	///< 0x05 Barra de desplazamiento  X del mapa
	(*leaf).intYbar		= 0;	///< 0x06 Barra de desplazamiento Y del mapa
	(*leaf).intSon		= 0;	///< 0x07 Tiene subrama (hijo)
	(*leaf).intMusic	= 0;	///< 0x0B Música de fondo
	(*leaf).stcMusic.Name_of_Sound_effect	= _T("");	///< 0x0C Música de fondo (archivo) String
	(*leaf).stcMusic.Fadein	= 0;
	(*leaf).stcMusic.Volume	= 100;
	(*leaf).stcMusic.Tempo	= 100;
	(*leaf).stcMusic.Balance= 50;
	(*leaf).intBatle	= 0;	///< 0x15 Fondo de batalla
	(*leaf).strBatle	= _T("");	///< 0x16 Fondo de batalla (archivo) String
	(*leaf).intTelepor	= 0;	///< 0x1F Teletransporte
	(*leaf).intScape	= 0;	///< 0x20 Escapar
	(*leaf).intSave		= 0;	///< 0x21 Guardar
	(*leaf).vcEnemyGroup.clear();	///< 0x29 grupo de enemigos
	(*leaf).intNofsteeps	= 0;	///< 0x2C Pasos entre encuentros
}
void LMT::GetNextChunk(wxFFile * Stream)
{
	int enemygroups=0,idgroup=0,enemy=0;
	unsigned long nodes=0, temp=0;
	ReadCompressedInteger(Stream);
	tChunk ChunkInfo; // informacion del pedazo leido
	wxByte Void;
	DataofTree leaf;
	//initialize/clear map data
	leafclear(&leaf);
	wxPrintf(_T("Tree size: %d\n"), treesize);
	while(nodes < treesize)
	{
		ChunkInfo.ID		= ReadCompressedInteger(Stream); // lectura de tipo del pedazo
		wxPrintf(_T("Chunk ID: %d, "), ChunkInfo.ID);
		ChunkInfo.Length	= ReadCompressedInteger(Stream); // lectura de su tamaño
		wxPrintf(_T("length: %d\n"), ChunkInfo.Length);
		switch(ChunkInfo.ID) // segun el tipo
		{
			case CHUNK_NAME: //0x01
				leaf.strName	= ReadString(Stream, ChunkInfo.Length);
//				wxPrintf(_T(" 1 (0x01) Name: %s\n"), leaf.strName.c_str());
				break;
			case CHUNK_IDF: //0x02
				leaf.intIdMapF	= ReadCompressedInteger(Stream);
//				wxPrintf(_T(" 2 (0x02) Parent ID: %d\n"), leaf.intIdMapF);
				break;
			case CHUNK_DEPTH: //0x03
				leaf.intDepth	= ReadCompressedInteger(Stream);
//				wxPrintf(_T(" 3 (0x03) Depth: %d\n"), leaf.intDepth);
				break;
			case CHUNK_FAREA: //0x04
				leaf.intFlagMA	= ReadCompressedInteger(Stream);
//				wxPrintf(_T(" 4 (0x04) Root, map, area?: %d\n"), leaf.intFlagMA);
				break;
			case CHUNK_XBAR: //0x05
				leaf.intXbar	= ReadCompressedInteger(Stream);
//				wxPrintf(_T(" 5 (0x05) Scrollbar X: %d\n"), leaf.intYbar);
				break;
			case CHUNK_YBAR: //0x06
				leaf.intYbar	= ReadCompressedInteger(Stream);
//				wxPrintf(_T(" 6 (0x06) Scrollbar Y: %d\n"), leaf.intYbar);
				break;
			case CHUNK_SON: //0x07
				leaf.intSon	= ReadCompressedInteger(Stream);
//				wxPrintf(_T(" 7 (0x07) Has child Expanded tree? FIXME: %d\n"), leaf.intSon);
				break;
			case CHUNK_FMUSIC: //0x0B (11)
				leaf.intMusic	= ReadCompressedInteger(Stream);
//				wxPrintf(_T("11 (0x0B) Music ID: %d\n"), leaf.intMusic);
				break;
			case CHUNK_SMUSIC: //0x0C (12)
				while (ChunkInfo.ID != 0)
				{
					ChunkInfo.ID = ReadCompressedInteger(Stream); // lectura de tipo del pedazo
//					wxPrintf(_T("12 (0x0C) Struct Music Chunk ID: %d\n"), ChunkInfo.ID);
					if(ChunkInfo.ID != 0)
						ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño//						wxPrintf(_T("12 (0x0C) Struct Music Chunk Length: %d\n"), ChunkInfo.Length);
					switch(ChunkInfo.ID)// segun el tipo
					{
						case 0x01:
							leaf.stcMusic.Name_of_Sound_effect = ReadString(Stream, ChunkInfo.Length);
//							wxPrintf(_T("          File: %s\n"), leaf.stcMusic.Name_of_Sound_effect.c_str());
							break;
						case 0x02:
							leaf.stcMusic.Fadein = ReadCompressedInteger(Stream);
//							wxPrintf(_T("          Fade in: %d\n"), leaf.stcMusic.Fadein);
							break;
						case 0x03:
							leaf.stcMusic.Volume = ReadCompressedInteger(Stream);
//							wxPrintf(_T("          Volume: %d\n"), leaf.stcMusic.Volume);
							break;
						case 0x04:
							leaf.stcMusic.Tempo = ReadCompressedInteger(Stream);
//							wxPrintf(_T("          Tempo: %d\n"), leaf.stcMusic.Tempo);
							break;
						case 0x05:
							leaf.stcMusic.Balance = ReadCompressedInteger(Stream);
							wxPrintf(_T("          Balance: %d\n"), leaf.stcMusic.Balance);
							break;
						case 0x00:
							wxPrintf(_T("          DEBUG INFO: End of chunk\n"));
							break;
						default:
							while(ChunkInfo.Length--)
								Stream->Read(&Void, 1);
							break;
					}
				}
				break;
			case CHUNK_FBATLE: //0x15 (21)
				leaf.intBatle	= ReadCompressedInteger(Stream);
				wxPrintf(_T("21 (0x15) Battle background: %d\n"), leaf.intBatle);
				break;
			case CHUNK_SBATLE: //0x16 (22)
				leaf.strBatle	= ReadString(Stream, ChunkInfo.Length);
				wxPrintf(_T("22 (0x16) Battle background file: %s\n"), leaf.strBatle.c_str());
				break;
			case CHUNK_FTELEP: //0x1F (31)
				leaf.intTelepor	= ReadCompressedInteger(Stream);
				wxPrintf(_T("31 (0x1F) Teleport: %d\n"), leaf.intTelepor);
				break;
			case CHUNK_FESCAPE: //0x20 (32)
				leaf.intScape	= ReadCompressedInteger(Stream);
				wxPrintf(_T("32 (0x20) Escape: %d\n"), leaf.intScape);
				break;
			case CHUNK_FSAVE: //0x21 (33)
				leaf.intSave	= ReadCompressedInteger(Stream);
				wxPrintf(_T("33 (0x21) Save: %d\n"), leaf.intSave);
				break;
			case CHUNK_AENEMYS: //0x29 (41)
				enemygroups	= ReadCompressedInteger(Stream); // numero de grupos
				wxPrintf(_T("41 (0x29) Enemy groups: %d\n"), enemygroups);
				idgroup = 0;
				while(idgroup < enemygroups)
					{
						idgroup		= ReadCompressedInteger(Stream); //id de dato
						wxPrintf(_T("          ID group: %d\n"), idgroup);
						// no se para que escribieron los dos primeros enteros pero el 3ro es el id de grupo
						// probablemente quedo incompleto el rm2k
						wxPrintf(_T("          DEBUG: First Dummy Integer: %d\n"), ReadCompressedInteger(Stream));
						wxPrintf(_T("          DEBUG: Second Dummy Integer: %d\n"), ReadCompressedInteger(Stream));
						enemy		= ReadCompressedInteger(Stream);
						wxPrintf(_T("          Enemy: %d\n"), enemy);
						leaf.vcEnemyGroup.push_back(enemy);
						wxPrintf(_T("          DEBUG: END Integer: %d\n"), ReadCompressedInteger(Stream));//fin de bloque
					}
				break;
			case CHUNK_FNUMSTEP: //0x2C (44)
				leaf.intNofsteeps = ReadCompressedInteger(Stream);
				wxPrintf(_T("44 (0x2C) Steps: %d\n"), leaf.intNofsteeps);
				break;
			case CHUNK_MAP_END_OF_BLOCK: //0x00
				break;
			case CHUNK_AREA: //0x33 (51)
				// 4 datos estrictamente de 4 bytes
				Stream->Read(&(leaf.intAreaX1), 4);
//				wxPrintf(_T("Area X1: %d\n"), leaf.intAreaX1);
				Stream->Read(&(leaf.intAreaY1), 4);
//				wxPrintf(_T("Area Y1: %d\n"), leaf.intAreaY1);
				Stream->Read(&(leaf.intAreaX2), 4);
//				wxPrintf(_T("Area X2: %d\n"), leaf.intAreaX2);
				Stream->Read(&(leaf.intAreaY2), 4);
//				wxPrintf(_T("Chunk area Y2: %d\n"), leaf.intAreaY2);
				str_Vector.push_back(leaf);
				leafclear(&leaf);
				nodes++;
//				wxPrintf(_T("DEBUG INFO (area block): Nodes: %d\n"), nodes);
				while(nodes!=temp) // sirve para quitar el fin del chunk y el id del siguiente
					temp = ReadCompressedInteger(Stream);
//					wxPrintf(_T("DEBUG INFO (area block): End temp var: %d\n"), temp);
				break;
				wxPrintf(_T("------------------------------------\n"));
				wxGetchar();
			default:
				// saltate un pedazo del tamaño de la longitud
				while(ChunkInfo.Length--)
					Stream->Read(&Void, 1);
				wxPrintf(_T("LENGHT--: %d. Void wasted data: %d\n"), ChunkInfo.Length, Void);
				break;
		}
	}
}
void LMT::ShowInformation() // muestra de informacion del mapa
{
	unsigned long j, i;
	for (j=0; j < treesize; j++)
	{
		wxPrintf(_T("Nombre:				%s\n"), str_Vector[j].strName.c_str());
		wxPrintf(_T("ID del mapa padre:			%d\n"), str_Vector[j].intIdMapF);
		wxPrintf(_T("Profundidad:			%d\n"), str_Vector[j].intDepth);
		wxPrintf(_T("Tipo (0=raiz, 1=mapa, 2=area):	%d\n"), str_Vector[j].intFlagMA);
		wxPrintf(_T("Barras de desplazamiento:		X = %d, Y = %d\n"), str_Vector[j].intXbar, str_Vector[j].intYbar);
		wxPrintf(_T("Tiene subrama?:			%d\n"), str_Vector[j].intSon);
		wxPrintf(_T("Tiene musica de fondo?:		%d\n"), str_Vector[j].intMusic);
		wxPrintf(_T("Nombre musica:			%s\n"), str_Vector[j].stcMusic.Name_of_Sound_effect.c_str());
		wxPrintf(_T("Fade in musica:			%d\n"), str_Vector[j].stcMusic.Fadein);
		wxPrintf(_T("Volumen musica:			%d\n"), str_Vector[j].stcMusic.Volume);
		wxPrintf(_T("Tempo musica:			%d\n"), str_Vector[j].stcMusic.Tempo);
		wxPrintf(_T("Balance musica:			%d\n"), str_Vector[j].stcMusic.Balance);
		wxPrintf(_T("Tiene fondo de batalla?:		%d\n"), str_Vector[j].intBatle);
		wxPrintf(_T("Nombre fondo:			%s\n"), str_Vector[j].strBatle.c_str());
		wxPrintf(_T("Permite teletrasporte?		%d\n"), str_Vector[j].intTelepor);
		wxPrintf(_T("Permite guardar?:			%d\n"), str_Vector[j].intScape);
		for(i=0; i < str_Vector[j].vcEnemyGroup.size(); i++)
		{
			wxPrintf(_T("Grupo enemigo:			%d\n"), str_Vector[j].vcEnemyGroup[i]);
		}
		wxPrintf(_T("Pasos para encuentro enemigo:	%d\n"), str_Vector[j].intNofsteeps);
		wxPrintf(_T("Inicio de area:			X = %d, Y = %d\n"), str_Vector[j].intAreaX1, str_Vector[j].intAreaY1);
		wxPrintf(_T("Fin de area:			X = %d, Y = %d\n"), str_Vector[j].intAreaX2,str_Vector[j].intAreaY2);
	}
	wxPrintf(_T("ID party:				%d\n"), intPartymapId);
	wxPrintf(_T("Party X:				%d\n"), intPartymapX);
	wxPrintf(_T("party Y:				%d\n"), intPartymapY);
	wxPrintf(_T("ID Skiff:				%d\n"), intSkiffId);
	wxPrintf(_T("Skiff X:				%d\n"), intSkiffX);
	wxPrintf(_T("Skiff Y:				%d\n"), intSkiffY);
	wxPrintf(_T("id Boat:				%d\n"), intBoatId);
	wxPrintf(_T("Boat X:				%d\n"), intBoatX);
	wxPrintf(_T("Boat Y:				%d\n"), intBoatY);
	wxPrintf(_T("ID Airship:			%d\n"), intAirshipId);
	wxPrintf(_T("Airship X:				%d\n"), intAirshipX);
	wxPrintf(_T("Airship Y:				%d\n"), intAirshipY);
	wxPrintf(_T("Orden de las hojas:	"));
	for(j = 0; j < (treesize - 1); j++)
	{
		wxPrintf(_T("%d "),vc_int_treeorder[j]);
	}
	wxPrintf(_T("\nHoja seleccionada:		%d\n"), vc_int_treeorder[j]);
}

