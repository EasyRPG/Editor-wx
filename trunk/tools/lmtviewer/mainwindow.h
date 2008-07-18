/* mainwindow.h, LMT Viewer window frame.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "wx/wx.h"
#include "wx/image.h"
#include "wx/artprov.h"
#include "wx/imaglist.h"
#include "wx/treectrl.h"
#include "wx/ffile.h"
#include <vector>

struct Sound_effect
{
	wxString Name_of_Sound_effect;
	int Fadein;
	int Volume;
	int Tempo;
	int Balance;
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
	std::vector<int> vcEnemyGroup; ///< 0x29 arreglo dos dimensiones con enemigos
	int		intNofsteeps;	///< 0x2C Pasos entre encuentros
					///< 0x33 Datos del área
	int		intAreaX1;
	int		intAreaY1;
	int		intAreaX2;
	int		intAreaY2;
};

class mainwindow: public wxFrame {
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
		std::vector<DataofTree> str_Vector;
		std::vector<long> vc_int_treeorder;
		//Methods
		mainwindow(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);
		bool	loadlmt(const wxString Filename);
	private:
		void	openbutton_click(wxCommandEvent& WXUNUSED(event));
		void	filllmt();
		void	GetNextChunk(wxFFile * Stream);
		void	leafclear(DataofTree * leaf);
	protected:
		wxButton* openbutton;
		wxTreeCtrl* maptree;
};

#endif
