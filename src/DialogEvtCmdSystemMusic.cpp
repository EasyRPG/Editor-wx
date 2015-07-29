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
#include "DialogEvtCmdSystemMusic.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdSystemMusic::DialogEvtCmdSystemMusic(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdSystemMusic::DialogEvtCmdSystemMusic
    szMusic_staticbox = new wxStaticBox(this, wxID_ANY, _("Music"));
    szSystemMusic2_staticbox = new wxStaticBox(this, wxID_ANY, _("Music type"));
    const wxString chSystemMusic_choices[] = {
        _("<set by wxGlade>"),
    };
    chSystemMusic = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 1, chSystemMusic_choices);
    tcMusic = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnMusic = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdSystemMusic::set_properties()
{
    // begin wxGlade: DialogEvtCmdSystemMusic::set_properties
    SetTitle(_("Change system music"));
    chSystemMusic->SetMinSize(wxSize(50, -1));
    chSystemMusic->SetSelection(0);
    tcMusic->SetMinSize(wxSize(50, -1));
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdSystemMusic::do_layout()
{
    // begin wxGlade: DialogEvtCmdSystemMusic::do_layout
    wxBoxSizer* szSystemMusic = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szTop = new wxBoxSizer(wxHORIZONTAL);
    szMusic_staticbox->Lower();
    wxStaticBoxSizer* szMusic = new wxStaticBoxSizer(szMusic_staticbox, wxHORIZONTAL);
    szSystemMusic2_staticbox->Lower();
    wxStaticBoxSizer* szSystemMusic2 = new wxStaticBoxSizer(szSystemMusic2_staticbox, wxHORIZONTAL);
    szSystemMusic2->Add(chSystemMusic, 1, wxALIGN_CENTER_VERTICAL, 0);
    szTop->Add(szSystemMusic2, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szMusic->Add(tcMusic, 1, wxALIGN_CENTER_VERTICAL, 0);
    szMusic->Add(btnMusic, 0, wxALIGN_CENTER_VERTICAL, 0);
    szTop->Add(szMusic, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szSystemMusic->Add(szTop, 1, wxEXPAND, 0);
    szBottom->Add(btnOK, 0, wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALL, 1);
    szSystemMusic->Add(szBottom, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szSystemMusic);
    szSystemMusic->Fit(this);
    Layout();
    // end wxGlade
}
