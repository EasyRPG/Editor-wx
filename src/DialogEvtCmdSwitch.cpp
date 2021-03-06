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
#include "DialogEvtCmdSwitch.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdSwitch::DialogEvtCmdSwitch(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdSwitch::DialogEvtCmdSwitch
    szSwitch2_staticbox = new wxStaticBox(this, wxID_ANY, _("Switch"));
    rbtnSwitch = new wxRadioButton(this, wxID_ANY, _("Switch"));
    tcSwitch = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnSwitch = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    rbtnRange = new wxRadioButton(this, wxID_ANY, _("Range from"));
    spinRange1 = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stRange = new wxStaticText(this, wxID_ANY, _("to"));
    spinRange2 = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    rbtnVariable = new wxRadioButton(this, wxID_ANY, _("Variable"));
    tcVariable = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnVariable = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    const wxString rbOperation_choices[] = {
        _("Enable"),
        _("Disable"),
        _("Toggle"),
    };
    rbOperation = new wxRadioBox(this, wxID_ANY, _("Operation"), wxDefaultPosition, wxDefaultSize, 3, rbOperation_choices, 1, wxRA_SPECIFY_ROWS);
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdSwitch::set_properties()
{
    // begin wxGlade: DialogEvtCmdSwitch::set_properties
    SetTitle(_("Switch operations"));
    tcSwitch->SetMinSize(wxSize(50, -1));
    spinRange1->SetMinSize(wxSize(50, -1));
    spinRange2->SetMinSize(wxSize(50, -1));
    tcVariable->SetMinSize(wxSize(50, -1));
    rbOperation->SetSelection(0);
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdSwitch::do_layout()
{
    // begin wxGlade: DialogEvtCmdSwitch::do_layout
    wxBoxSizer* szSwitch = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    szSwitch2_staticbox->Lower();
    wxStaticBoxSizer* szSwitch2 = new wxStaticBoxSizer(szSwitch2_staticbox, wxHORIZONTAL);
    wxFlexGridSizer* gszSwitch = new wxFlexGridSizer(3, 2, 2, 2);
    wxBoxSizer* szVariable = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szRange = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szSwitch3 = new wxBoxSizer(wxHORIZONTAL);
    gszSwitch->Add(rbtnSwitch, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0);
    szSwitch3->Add(tcSwitch, 1, wxALIGN_CENTER_VERTICAL, 0);
    szSwitch3->Add(btnSwitch, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszSwitch->Add(szSwitch3, 1, wxEXPAND, 0);
    gszSwitch->Add(rbtnRange, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0);
    szRange->Add(spinRange1, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 1);
    szRange->Add(stRange, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 1);
    szRange->Add(spinRange2, 1, wxALIGN_CENTER_VERTICAL|wxLEFT, 1);
    gszSwitch->Add(szRange, 1, wxEXPAND, 0);
    gszSwitch->Add(rbtnVariable, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0);
    szVariable->Add(tcVariable, 1, wxALIGN_CENTER_VERTICAL, 0);
    szVariable->Add(btnVariable, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszSwitch->Add(szVariable, 1, wxEXPAND, 0);
    gszSwitch->AddGrowableRow(0);
    gszSwitch->AddGrowableRow(1);
    gszSwitch->AddGrowableRow(2);
    gszSwitch->AddGrowableCol(1);
    szSwitch2->Add(gszSwitch, 1, wxEXPAND, 0);
    szSwitch->Add(szSwitch2, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szSwitch->Add(rbOperation, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBottom->Add(btnOK, 0, wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALL, 1);
    szSwitch->Add(szBottom, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szSwitch);
    szSwitch->Fit(this);
    Layout();
    // end wxGlade
}

