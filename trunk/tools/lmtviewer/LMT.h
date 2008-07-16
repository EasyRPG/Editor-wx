/* LMT.h, LcfMapTree RPG Maker 2000/2003 structure format.
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

#ifndef LMT_H
#define LMT_H

#include "wx/wx.h"
#include <vector>

struct Sound_effect
{
	wxString Name_of_Sound_effect;
	int Fadein;
	int Volume;
	int Tempo;
	int Balance;
};

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
	CHUNK_AREA		= 0x33,	///< Coordenadas del area
	CHUNK_MAP_END_OF_BLOCK	= 0x00
};

struct DataofTree
{
	wxString	strName;	///< 0x01 nombre del mapa
	int		intIdMapF;	///< 0x02 ID del mapa padre
	int		intDepth;	///< 0x03 Profundidad del árbol
	int		intFlagMA;	///< 0x04 Bandera de mapa o área
	int		intXbar;	///< 0x05 Barra de desplazamiento  X del mapa
	int		intYbar;	///< 0x06 Barra de desplazamiento Y del mapa
	int		intSon;		///< 0x07 Tiene subrama (hijo)
	int		intMusic;	///< 0x0B Música de fondo
	Sound_effect	stcMusic;	///< 0x0C Música de fondo (archivo) String
	int		intBatle;	///< 0x15 Fondo de batalla
	wxString	strBatle;	///< 0x16 Fondo de batalla (archivo) String
	int		intTelepor;	///< 0x1F Teletransporte
	int		intScape;	///< 0x20 Escapar Entero
	int		intSave;	///< 0x21 Guardar Entero
	std::vector < int > vcEnemyGroup; ///< 0x29 arreglo dos dimensiones con enemigos
	int		intNofsteeps;	///< 0x2C Pasos entre encuentros
					///< 0x33 Datos del área
	int		intAreaX1;
	int		intAreaY1;
	int		intAreaX2;
	int		intAreaY2;
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

class LMT
{
	public:
		int 	intPartymapId;	///< 0x01 Party start map
		int	intPartymapX;	///< 0x02 Party start X
		int	intPartymapY;	///< 0x03 Party start Y
		int	intSkiffId;	///< 0x0B Skiff start map
		int	intSkiffX;	///< 0x0C Skiff start X
		int	intSkiffY;	///< 0x0D Skiff start Y
		int	intBoatId;	///< 0x15 Boat start map
		int	intBoatX;	///< 0x16 Boat start X
		int	intBoatY;	///< 0x17 Boat start Y
		int	intAirshipId;	///< 0x1F Airship start map
		int	intAirshipX;	///< 0x20 Airship start X
		int	intAirshipY;	///< 0x21 Airship start Y
		unsigned long	treesize;
		std::vector <DataofTree> str_Vector;
		std::vector <long> vc_int_treeorder;
		// Methods
		bool	Load(const wxString Filename);
		void	ShowInformation();
	private:
		void	GetNextChunk(wxFFile * Stream);
		void	leafclear(DataofTree * leaf);
};

#endif
