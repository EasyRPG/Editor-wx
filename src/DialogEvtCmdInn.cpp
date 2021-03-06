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
#include "DialogEvtCmdInn.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdInn::DialogEvtCmdInn(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdInn::DialogEvtCmdInn
    szPrice_staticbox = new wxStaticBox(this, wxID_ANY, _("Stay price"));
    SzOptions_staticbox = new wxStaticBox(this, wxID_ANY, _("Options"));
    szMessage_staticbox = new wxStaticBox(this, wxID_ANY, _("Inn message type"));
    const wxString chMessage_choices[] = {
        _("<set by wxGlade>"),
    };
    chMessage = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 1, chMessage_choices);
    spin_ctrl_1 = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    ChkCondition = new wxCheckBox(this, wxID_ANY, _("Create condition"));
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdInn::set_properties()
{
    // begin wxGlade: DialogEvtCmdInn::set_properties
    SetTitle(_("Visit inn"));
    chMessage->SetMinSize(wxSize(50, -1));
    chMessage->SetSelection(0);
    spin_ctrl_1->SetMinSize(wxSize(50, -1));
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdInn::do_layout()
{
    // begin wxGlade: DialogEvtCmdInn::do_layout
    wxBoxSizer* szInn = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szMiddle = new wxBoxSizer(wxHORIZONTAL);
    SzOptions_staticbox->Lower();
    wxStaticBoxSizer* SzOptions = new wxStaticBoxSizer(SzOptions_staticbox, wxHORIZONTAL);
    szPrice_staticbox->Lower();
    wxStaticBoxSizer* szPrice = new wxStaticBoxSizer(szPrice_staticbox, wxHORIZONTAL);
    szMessage_staticbox->Lower();
    wxStaticBoxSizer* szMessage = new wxStaticBoxSizer(szMessage_staticbox, wxHORIZONTAL);
    szMessage->Add(chMessage, 1, wxALIGN_CENTER_VERTICAL, 0);
    szInn->Add(szMessage, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szPrice->Add(spin_ctrl_1, 1, wxALIGN_CENTER_VERTICAL, 0);
    szMiddle->Add(szPrice, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    SzOptions->Add(ChkCondition, 1, wxALIGN_CENTER_VERTICAL, 0);
    szMiddle->Add(SzOptions, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szInn->Add(szMiddle, 0, wxEXPAND, 0);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szInn->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szInn);
    szInn->Fit(this);
    Layout();
    // end wxGlade
}

