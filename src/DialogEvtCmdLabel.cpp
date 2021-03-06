// -*- C++ -*-
//
// generated by wxGlade not found
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#include <wx/wx.h>
#include "DialogEvtCmdLabel.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdLabel::DialogEvtCmdLabel(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdLabel::DialogEvtCmdLabel
    szNumber_staticbox = new wxStaticBox(this, wxID_ANY, _("Label number"));
    spinNumber = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdLabel::set_properties()
{
    // begin wxGlade: DialogEvtCmdLabel::set_properties
    SetTitle(_("Set label"));
    spinNumber->SetMinSize(wxSize(50, -1));
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdLabel::do_layout()
{
    // begin wxGlade: DialogEvtCmdLabel::do_layout
    wxBoxSizer* szLabel = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    szNumber_staticbox->Lower();
    wxStaticBoxSizer* szNumber = new wxStaticBoxSizer(szNumber_staticbox, wxHORIZONTAL);
    szNumber->Add(spinNumber, 1, wxALIGN_CENTER_VERTICAL, 0);
    szLabel->Add(szNumber, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szLabel->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szLabel);
    szLabel->Fit(this);
    Layout();
    // end wxGlade
}

