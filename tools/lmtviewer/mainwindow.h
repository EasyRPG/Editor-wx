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
		void openbutton_click(wxCommandEvent& event);
	protected:
		wxButton* openbutton;
		wxTreeCtrl* maptree;
};

#endif

