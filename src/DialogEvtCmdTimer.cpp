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
#include "DialogEvtCmdTimer.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdTimer::DialogEvtCmdTimer(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdTimer::DialogEvtCmdTimer
    szOptions_staticbox = new wxStaticBox(this, wxID_ANY, _("Options"));
    szOperation_staticbox = new wxStaticBox(this, wxID_ANY, _("Operation"));
    const wxString rbOperation_choices[] = {
        _("Set value"),
        _("Start"),
        _("Stop"),
    };
    rbOperation = new wxRadioBox(this, wxID_ANY, _("Operation"), wxDefaultPosition, wxDefaultSize, 3, rbOperation_choices, 1, wxRA_SPECIFY_ROWS);
    rbtnSet = new wxRadioButton(this, wxID_ANY, _("Set"));
    spinMinutes = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stMinutes = new wxStaticText(this, wxID_ANY, _("minutes"));
    spinSeconds = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stSeconds = new wxStaticText(this, wxID_ANY, _("seconds"));
    rbtnVariable = new wxRadioButton(this, wxID_ANY, _("By variable"));
    tcVariable = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnVariable = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    chbShowScreen = new wxCheckBox(this, wxID_ANY, _("Show in screen"));
    chbShowBattle = new wxCheckBox(this, wxID_ANY, _("show in battle"));
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdTimer::set_properties()
{
    // begin wxGlade: DialogEvtCmdTimer::set_properties
    SetTitle(_("Timer operations"));
    rbOperation->SetSelection(0);
    spinMinutes->SetMinSize(wxSize(50, -1));
    spinSeconds->SetMinSize(wxSize(50, -1));
    tcVariable->SetMinSize(wxSize(50, -1));
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdTimer::do_layout()
{
    // begin wxGlade: DialogEvtCmdTimer::do_layout
    wxBoxSizer* szTimer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    szOptions_staticbox->Lower();
    wxStaticBoxSizer* szOptions = new wxStaticBoxSizer(szOptions_staticbox, wxHORIZONTAL);
    szOperation_staticbox->Lower();
    wxStaticBoxSizer* szOperation = new wxStaticBoxSizer(szOperation_staticbox, wxVERTICAL);
    wxBoxSizer* szVariable = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szSet = new wxBoxSizer(wxHORIZONTAL);
    szTimer->Add(rbOperation, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szSet->Add(rbtnSet, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxRIGHT, 1);
    szSet->Add(spinMinutes, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxRIGHT, 1);
    szSet->Add(stMinutes, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxRIGHT, 1);
    szSet->Add(spinSeconds, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxRIGHT, 1);
    szSet->Add(stSeconds, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT, 1);
    szOperation->Add(szSet, 1, wxEXPAND, 0);
    szVariable->Add(rbtnVariable, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP, 1);
    szVariable->Add(tcVariable, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 1);
    szVariable->Add(btnVariable, 0, wxALIGN_CENTER_VERTICAL|wxTOP, 1);
    szOperation->Add(szVariable, 1, wxEXPAND, 0);
    szTimer->Add(szOperation, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szOptions->Add(chbShowScreen, 1, wxRIGHT, 0);
    szOptions->Add(chbShowBattle, 1, wxLEFT, 0);
    szTimer->Add(szOptions, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szTimer->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szTimer);
    szTimer->Fit(this);
    Layout();
    // end wxGlade
}

