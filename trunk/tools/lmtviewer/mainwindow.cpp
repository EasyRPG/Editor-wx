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

mainwindow::mainwindow(wxWindow * parent, int id, const wxString & title, const wxPoint & pos, const wxSize & size, long WXUNUSED(style)):
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
	imageList->Add(wxIcon(_T("shell32.dll;3"), wxBITMAP_TYPE_ICO, 16, 16)); // 3 is closed folder
	imageList->Add(wxIcon(_T("shell32.dll;4"), wxBITMAP_TYPE_ICO, 16, 16)); // 4 is opened folder
	imageList->Add(wxIcon(_T("shell32.dll;0"), wxBITMAP_TYPE_ICO, 16, 16)); // 0 is normal file
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
		wxString filename = openlmtwindow->GetPath();
		if(load(filename))
		{
			filllmt();
		}
	}
}

bool mainwindow::load(wxString filename)
{
	wxFFile		* file;
	wxString	header;
	wxByte		dummy;
	int		remaining_nodes;
	int		node;
	int		vehicle_chunk_id;
	int		vehicle_chunk_size;

	file = new wxFFile(filename, _T("rb")); // fopen()
	header = read_string(file); // lectura de cabecera
	if (wxStrcmp(header, _T("LcfMapTree"))) // comparacion con cabecera del mapa
	{
		wxMessageBox(_("File is not a valid RPG Maker 2000/2003 map tree"), _("Error reading RPG_RT.lmt data"), wxICON_ERROR);
		file->Close();
		return false;
	}
	//Read number of nodes
	total_nodes = read_int(file);
	//Read tree
	read_tree(file);
	file->Read(&dummy, 1); //00 end of block
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
	while(!file->Eof())
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
				break;
			default:
				// skip unknown vehicle_chunk_id case
				while(vehicle_chunk_size--)
				{
					file->Read(&dummy, 1);
				}
				break;
		}
	}
	file->Close();
	return true;
}


void mainwindow::clear(node * node)
{
	(*node).name			= _T("");
	(*node).parent_id		= 0;
	(*node).depth			= 0;
	(*node).type			= 0;
	(*node).scrollbar_x		= 0;
	(*node).scrollbar_y		= 0;
	(*node).expanded		= 0;
	(*node).bgm			= 0;
	(*node).bgm_file.name		= _T("");
	(*node).bgm_file.fade_in	= 0;
	(*node).bgm_file.volume		= 100;
	(*node).bgm_file.tempo		= 100;
	(*node).bgm_file.balance	= 50;
	(*node).battle			= 0;
	(*node).battle_file		= _T("");
	(*node).teleport		= 0;
	(*node).escape			= 0;
	(*node).save			= 0;
	(*node).encounter.clear();
	(*node).encounter_steps		= 0;
}


void mainwindow::read_tree(wxFFile * file)
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
	tree_list.clear();
	tree_order.clear();
	clear(&node);
	while(current_node < total_nodes)
	{
		node_chunk_id	= read_int(file);
		node_chunk_size	= read_int(file);
		switch(node_chunk_id)
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
							// skip unknown vehicle_chunk_id case
							while(node_chunk_size--)
							{
								file->Read(&dummy, 1);
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
				file->Read(&(node.area_start_x), 4);
				file->Read(&(node.area_start_y), 4);
				file->Read(&(node.area_end_x), 4);
				file->Read(&(node.area_end_y), 4);
				tree_list.push_back(node);
				break;
			case 0: //End of block
				clear(&node);
				current_node++;
				break;
			default:
				// skip unknown vehicle_chunk_id case
				while(node_chunk_size--)
				{
					file->Read(&dummy, 1);
				}
				break;
		}
	}
}

void mainwindow::filllmt()
{
	maptree->DeleteAllItems();
	int current_node;
	wxTreeItemId root = maptree->AddRoot(tree_list[0].name, 1, 0);
	for (current_node = 1; current_node < total_nodes; current_node++)
	{
		maptree->AppendItem(root, tree_list[current_node].name, 2);
	}
	maptree->ExpandAll();
}
