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
#include "DialogEvtCmdShake.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdShake::DialogEvtCmdShake(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdShake::DialogEvtCmdShake
    szSpeed_staticbox = new wxStaticBox(this, wxID_ANY, _("Speed"));
    szTime_staticbox = new wxStaticBox(this, wxID_ANY, _("Shaking time"));
    szOptions_staticbox = new wxStaticBox(this, wxID_ANY, _("Options"));
    szStrength_staticbox = new wxStaticBox(this, wxID_ANY, _("Shaking strength"));
    slStrength = new wxSlider(this, wxID_ANY, 4, 0, 8, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_BOTTOM|wxSL_HORIZONTAL);
    stStrengthLower = new wxStaticText(this, wxID_ANY, _("Lower"));
    szStrengthNormal = new wxStaticText(this, wxID_ANY, _("Normal"));
    stStrengthHigher = new wxStaticText(this, wxID_ANY, _("Higher"));
    slSpeed = new wxSlider(this, wxID_ANY, 4, 0, 8, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS|wxSL_BOTTOM|wxSL_HORIZONTAL);
    stSpeedSlower = new wxStaticText(this, wxID_ANY, _("Slower"));
    stSpeedNormal = new wxStaticText(this, wxID_ANY, _("Normal"));
    stSpeedFaster = new wxStaticText(this, wxID_ANY, _("Faster"));
    spinTime = new wxSpinCtrl(this, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stTime = new wxStaticText(this, wxID_ANY, _("x0.1 sec."));
    chbWait = new wxCheckBox(this, wxID_ANY, _("Wait until end"));
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdShake::set_properties()
{
    // begin wxGlade: DialogEvtCmdShake::set_properties
    SetTitle(_("Shake screen"));
    spinTime->SetMinSize(wxSize(50, -1));
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdShake::do_layout()
{
    // begin wxGlade: DialogEvtCmdShake::do_layout
    wxBoxSizer* szShake = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szMiddle = new wxBoxSizer(wxHORIZONTAL);
    szOptions_staticbox->Lower();
    wxStaticBoxSizer* szOptions = new wxStaticBoxSizer(szOptions_staticbox, wxHORIZONTAL);
    szTime_staticbox->Lower();
    wxStaticBoxSizer* szTime = new wxStaticBoxSizer(szTime_staticbox, wxHORIZONTAL);
    wxBoxSizer* szTop = new wxBoxSizer(wxHORIZONTAL);
    szSpeed_staticbox->Lower();
    wxStaticBoxSizer* szSpeed = new wxStaticBoxSizer(szSpeed_staticbox, wxVERTICAL);
    wxBoxSizer* szSpeedBottom = new wxBoxSizer(wxHORIZONTAL);
    szStrength_staticbox->Lower();
    wxStaticBoxSizer* szStrength = new wxStaticBoxSizer(szStrength_staticbox, wxVERTICAL);
    wxBoxSizer* szStrenghtBottom = new wxBoxSizer(wxHORIZONTAL);
    szStrength->Add(slStrength, 0, wxEXPAND, 0);
    szStrenghtBottom->Add(stStrengthLower, 0, wxALIGN_CENTER_VERTICAL, 0);
    szStrenghtBottom->Add(2, 0, 1, wxEXPAND, 0);
    szStrenghtBottom->Add(szStrengthNormal, 0, wxALIGN_CENTER_VERTICAL, 0);
    szStrenghtBottom->Add(2, 0, 1, wxEXPAND, 0);
    szStrenghtBottom->Add(stStrengthHigher, 0, wxALIGN_CENTER_VERTICAL, 0);
    szStrength->Add(szStrenghtBottom, 1, wxEXPAND, 0);
    szTop->Add(szStrength, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szSpeed->Add(slSpeed, 0, wxEXPAND, 0);
    szSpeedBottom->Add(stSpeedSlower, 0, wxALIGN_CENTER_VERTICAL, 0);
    szSpeedBottom->Add(2, 0, 1, wxEXPAND, 0);
    szSpeedBottom->Add(stSpeedNormal, 0, wxALIGN_CENTER_VERTICAL, 0);
    szSpeedBottom->Add(2, 0, 1, wxEXPAND, 0);
    szSpeedBottom->Add(stSpeedFaster, 0, wxALIGN_CENTER_VERTICAL, 0);
    szSpeed->Add(szSpeedBottom, 1, wxEXPAND, 0);
    szTop->Add(szSpeed, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szShake->Add(szTop, 0, wxEXPAND, 0);
    szTime->Add(spinTime, 0, wxRIGHT, 1);
    szTime->Add(stTime, 0, wxLEFT, 1);
    szMiddle->Add(szTime, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szOptions->Add(chbWait, 1, 0, 0);
    szMiddle->Add(szOptions, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szShake->Add(szMiddle, 0, wxEXPAND, 0);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szShake->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szShake);
    szShake->Fit(this);
    Layout();
    // end wxGlade
}

