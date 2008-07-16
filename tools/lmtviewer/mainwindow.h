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

class mainwindow: public wxFrame {
	public:
		mainwindow(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);
	private:
		void set_properties();
		void do_layout();
		void openbutton_click(wxCommandEvent& WXUNUSED(event));
	protected:
		wxButton* openbutton;
		wxTreeCtrl* maptree;
};

#endif

