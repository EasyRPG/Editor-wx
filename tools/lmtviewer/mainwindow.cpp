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
#include "LMT.h"


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

	//Sample fill, this will be replaced with LMT data in the future
	wxTreeItemId root = maptree->AddRoot(_("Raiz"), 1, 0);
	maptree->AppendItem(root, _("Rama 1"), 2);
	maptree->AppendItem(root, _("Rama 2"), 2);
	maptree->AppendItem(root, _("Rama 3"), 2);
	maptree->ExpandAll();
	//wxGlade generated methods, I love it
	set_properties();
	do_layout();

	//Events
	Connect(wxID_OPEN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainwindow::openbutton_click));
}

void mainwindow::set_properties()
{
	SetTitle(_("LMT Viewer"));
}

void mainwindow::do_layout()
{
	wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);
	mainsizer->Add(openbutton, 0, wxEXPAND, 0);
	mainsizer->Add(maptree, 1, wxEXPAND, 0);
	SetSizer(mainsizer);
	mainsizer->Fit(this);
	Layout();
}

void mainwindow::openbutton_click(wxCommandEvent& WXUNUSED(event))
{
	LMT MYLMT;
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
		if(MYLMT.Load(fileName))
		{
			MYLMT.ShowInformation();
		}
	}
}

