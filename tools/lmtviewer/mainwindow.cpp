/* mainwindow.cpp, LMT Viewer window frame.
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

#include "mainwindow.h"
#include "tools.h"
#include <vector>

mainwindow::mainwindow(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long WXUNUSED(style)):
	wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
	openbutton = new wxButton(this, wxID_OPEN, wxEmptyString);
	maptree = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(208,-1), wxTR_HAS_BUTTONS|wxTR_DEFAULT_STYLE|wxSUNKEN_BORDER);

	//Using native stock icons for treectrl for nice looking
	//wxArtProvider does not load native Win32 icons, so we will get from our own technique
#ifdef __WXMSW__
	//Win32 TreeCtrl works only with 16x16 images
	wxImageList* imageList = new wxImageList(16, 16);
	// The number next filename and semicolon is the resource index number
	// The returned bitmap is an icon, not resource icon due previous resource index selection
	// 16x16 is desired size,  gets the 16x16 icon version instead of 32x32
	imageList->Add(wxIcon(wxT("shell32.dll;3"), wxBITMAP_TYPE_ICO, 16, 16)); // 3 is closed folder
	imageList->Add(wxIcon(wxT("shell32.dll;4"), wxBITMAP_TYPE_ICO, 16, 16)); // 4 is opened folder
	imageList->Add(wxIcon(wxT("shell32.dll;0"), wxBITMAP_TYPE_ICO, 16, 16)); // 0 is normal file
#else
	wxImageList* imageList = new wxImageList;
	imageList->Add(wxArtProvider::GetBitmap(wxART_FOLDER));
	imageList->Add(wxArtProvider::GetBitmap(wxART_FILE_OPEN));
	imageList->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE));
#endif
	maptree->AssignImageList(imageList);
	//Properties
	SetTitle(_("LMT Viewer"));
	//Layout
	wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);
	mainsizer->Add(openbutton, 0, wxEXPAND, 0);
	mainsizer->Add(maptree, 1, wxEXPAND, 0);
	SetSizer(mainsizer);
	mainsizer->Fit(this);
	Layout();
	//Events
	Connect(wxID_OPEN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainwindow::openbutton_click));
}

void mainwindow::openbutton_click(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog * openlmtwindow = new wxFileDialog(this);
	openlmtwindow->SetMessage(_("Select LcfMapTree file"));
#ifdef __WXGTK__
	// GTK+ is file name case sensitive
	openlmtwindow->SetWildcard(_("LMT files (*.lmt)|*.[lL][mM][tT]"));
#else
	openlmtwindow->SetWildcard(_("LMT files (*.lmt)|*.lmt"));
#endif
	if (openlmtwindow->ShowModal() == wxID_OK)
	{
		wxString fileName = openlmtwindow->GetPath();
		if(loadlmt(fileName))
		{
			filllmt();
		}
	}
}

bool mainwindow::loadlmt(wxString Filename)
{
	wxByte Void = 0;
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
	Stream->Read(&Void, 1); // 00 final de bloque

	// orden en el que deve ser mostrado el arbol
	int data = treesize;
	int dat;
	while(data--) // datos de como debe ser mostrado el arbol
	{
		dat = ReadCompressedInteger(Stream);
		vc_int_treeorder.push_back(dat);
	}
	while(!Stream->Eof())
	{
		ChunkInfo.ID	 = ReadCompressedInteger(Stream); // lectura de tipo del pedazo
		ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño
		switch(ChunkInfo.ID) // segun el tipo
		{
			case 0x01: //Start party map ID
				intPartymapId	= ReadCompressedInteger(Stream);
				break;
			case 0x02: //Start party X position
				intPartymapX	= ReadCompressedInteger(Stream);
				break;
			case 0x03: //Start party Y position
				intPartymapY	= ReadCompressedInteger(Stream);
				break;
			case 0x0B: //Skiff map ID
				intSkiffId	= ReadCompressedInteger(Stream);
				break;
			case 0x0C: //Skiff X position
				intSkiffX	= ReadCompressedInteger(Stream);
				break;
			case 0x0D: //Skiff Y position
				intSkiffY	= ReadCompressedInteger(Stream);
				break;
			case 0x15: //Boat map ID
				intBoatId	= ReadCompressedInteger(Stream);
				break;
			case 0x16: //Boat X position
				intBoatX	= ReadCompressedInteger(Stream);
				break;
			case 0x17: //Boat Y position
				intBoatY	= ReadCompressedInteger(Stream);
				break;
			case 0x1F: //Airship map ID
				 intAirshipId	= ReadCompressedInteger(Stream);
				break;
			case 0x20: //Airshop X position
				intAirshipX	= ReadCompressedInteger(Stream);
				break;
			case 0x21: //Airship Y location
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

void mainwindow::leafclear(DataofTree * leaf)
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

void mainwindow::GetNextChunk(wxFFile * Stream)
{
	int enemygroups=0,idgroup=0,enemy=0;
	unsigned int nodes=0, temp=0;
	ReadCompressedInteger(Stream);
	tChunk ChunkInfo; // informacion del pedazo leido
	wxByte Void = 0;
	DataofTree leaf;
	str_Vector.clear();
	//initialize/clear map data
	leafclear(&leaf);
	while(nodes < treesize)
	{
		ChunkInfo.ID		= ReadCompressedInteger(Stream); // lectura de tipo del pedazo
		ChunkInfo.Length	= ReadCompressedInteger(Stream); // lectura de su tamaño
		switch(ChunkInfo.ID) // segun el tipo
		{
			case 0x01: //Name
				leaf.strName	= ReadString(Stream, ChunkInfo.Length);
				break;
			case 0x02: //Parent ID
				leaf.intIdMapF	= ReadCompressedInteger(Stream);
				break;
			case 0x03: //Indent depth
				leaf.intDepth	= ReadCompressedInteger(Stream);
				break;
			case 0x04: //Root=0, map=1 or area=2
				leaf.intFlagMA	= ReadCompressedInteger(Stream);
				break;
			case 0x05: //Horizontal scroll bar position
				leaf.intXbar	= ReadCompressedInteger(Stream);
				break;
			case 0x06: //Vertical scroll bar position
				leaf.intYbar	= ReadCompressedInteger(Stream);
				break;
			case 0x07: //Is expanded
				leaf.intSon	= ReadCompressedInteger(Stream);
				break;
			case 0x0B: //Background music 0=Inherit, 1=Do not change, 2=specify
				leaf.intMusic	= ReadCompressedInteger(Stream);
				break;
			case 0x0C: //Background music file
				while (ChunkInfo.ID != 0)
				{
					ChunkInfo.ID = ReadCompressedInteger(Stream); // lectura de tipo del pedazo
					if(ChunkInfo.ID != 0)
						ChunkInfo.Length = ReadCompressedInteger(Stream); // lectura de su tamaño
					switch(ChunkInfo.ID)// segun el tipo
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
							while(ChunkInfo.Length--)
							{
								Stream->Read(&Void, 1);
							}
							break;
					}
				}
				break;
			case 0x15: //Battle background 0=Inherit, 1=Do not change, 2=specify
				leaf.intBatle	= ReadCompressedInteger(Stream);
				break;
			case 0x16: //Battle background file
				leaf.strBatle	= ReadString(Stream, ChunkInfo.Length);
				break;
			case 0x1F: //Teleport 0=Inherit, 1=Allow, 2=Disallow
				leaf.intTelepor	= ReadCompressedInteger(Stream);
				break;
			case 0x20: //Escape 0=Inherit, 1=Allow, 2=Disallow
				leaf.intScape	= ReadCompressedInteger(Stream);
				break;
			case 0x21: //Save 0=Inherit, 1=Allow, 2=Disallow
				leaf.intSave	= ReadCompressedInteger(Stream);
				break;
			case 0x29: //Enemy groups
				enemygroups	= ReadCompressedInteger(Stream); // numero de grupos
				idgroup = 0;
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
			case 0x2C: //Number of steps between enemy encounters
				leaf.intNofsteeps = ReadCompressedInteger(Stream);
				break;
			case 0x00: //0x00
				break;
			case 0x33: //Area data
				Stream->Read(&(leaf.intAreaX1), 4);
				Stream->Read(&(leaf.intAreaY1), 4);
				Stream->Read(&(leaf.intAreaX2), 4);
				Stream->Read(&(leaf.intAreaY2), 4);
				str_Vector.push_back(leaf);
				leafclear(&leaf);
				nodes++;
				while(nodes!=temp) // sirve para quitar el fin del chunk y el id del siguiente
				{
					temp = ReadCompressedInteger(Stream);
				}
				break;
			default:
				// saltate un pedazo del tamaño de la longitud
				while(ChunkInfo.Length--)
				{
					Stream->Read(&Void, 1);
				}
				break;
		}
	}
}

void mainwindow::filllmt()
{
	maptree->DeleteAllItems();
	unsigned long i;
	wxTreeItemId root = maptree->AddRoot(str_Vector[0].strName, 1, 0);
	for (i=1; i < treesize; i++)
	{
		maptree->AppendItem(root, str_Vector[i].strName, 2);
	}
	maptree->ExpandAll();
}
