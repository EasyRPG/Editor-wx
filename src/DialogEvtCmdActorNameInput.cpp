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
#include "DialogEvtCmdActorNameInput.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdActorNameInput::DialogEvtCmdActorNameInput(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdActorNameInput::DialogEvtCmdActorNameInput
    szOptions_staticbox = new wxStaticBox(this, wxID_ANY, _("Options"));
    szActor_staticbox = new wxStaticBox(this, wxID_ANY, _("Actor"));
    const wxString chActor_choices[] = {
        _("<set by wxGlade>"),
    };
    chActor = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 1, chActor_choices);
    const wxString rbMode_choices[] = {
        _("Hiragana"),
        _("Katakana"),
    };
    rbMode = new wxRadioBox(this, wxID_ANY, _("Initial mode"), wxDefaultPosition, wxDefaultSize, 2, rbMode_choices, 1, wxRA_SPECIFY_ROWS);
    chbShowName = new wxCheckBox(this, wxID_ANY, _("Show initial name"));
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdActorNameInput::set_properties()
{
    // begin wxGlade: DialogEvtCmdActorNameInput::set_properties
    SetTitle(_("Actor name input"));
    chActor->SetMinSize(wxSize(100, -1));
    chActor->SetSelection(0);
    rbMode->SetSelection(0);
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdActorNameInput::do_layout()
{
    // begin wxGlade: DialogEvtCmdActorNameInput::do_layout
    wxBoxSizer* szActorNameInput = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    szOptions_staticbox->Lower();
    wxStaticBoxSizer* szOptions = new wxStaticBoxSizer(szOptions_staticbox, wxHORIZONTAL);
    wxBoxSizer* szTop = new wxBoxSizer(wxHORIZONTAL);
    szActor_staticbox->Lower();
    wxStaticBoxSizer* szActor = new wxStaticBoxSizer(szActor_staticbox, wxHORIZONTAL);
    szActor->Add(chActor, 1, wxALIGN_CENTER_VERTICAL, 0);
    szTop->Add(szActor, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szTop->Add(rbMode, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szActorNameInput->Add(szTop, 0, wxEXPAND, 0);
    szOptions->Add(chbShowName, 1, 0, 0);
    szActorNameInput->Add(szOptions, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szActorNameInput->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szActorNameInput);
    szActorNameInput->Fit(this);
    Layout();
    // end wxGlade
}

