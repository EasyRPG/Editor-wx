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
#include "DialogEvtCmdPlayVideo.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdPlayVideo::DialogEvtCmdPlayVideo(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdPlayVideo::DialogEvtCmdPlayVideo
    szSize_staticbox = new wxStaticBox(this, wxID_ANY, _("Size in window"));
    szPosition_staticbox = new wxStaticBox(this, wxID_ANY, _("Move to position (coordinates)"));
    szFile_staticbox = new wxStaticBox(this, wxID_ANY, _("Video file"));
    stVideo = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnVideo = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    spinSizeX = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stSize = new wxStaticText(this, wxID_ANY, _("X"));
    spinSizeY = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    rbtnSpecify = new wxRadioButton(this, wxID_ANY, _("Specify"));
    szSpecifyX = new wxStaticText(this, wxID_ANY, _("X:"));
    spinSpecifyX = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stSpecifyY = new wxStaticText(this, wxID_ANY, _("Y:"));
    spinSpecifyY = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    rbtnVariable = new wxRadioButton(this, wxID_ANY, _("Variable"));
    stVariableX = new wxStaticText(this, wxID_ANY, _("X:"));
    tcVariableX = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnVariableX = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    stVariableY = new wxStaticText(this, wxID_ANY, _("Y:"));
    tcVariableY = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnVariableY = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdPlayVideo::set_properties()
{
    // begin wxGlade: DialogEvtCmdPlayVideo::set_properties
    SetTitle(_("Play video"));
    stVideo->SetMinSize(wxSize(50, -1));
    spinSizeX->SetMinSize(wxSize(50, -1));
    spinSizeY->SetMinSize(wxSize(50, -1));
    spinSpecifyX->SetMinSize(wxSize(50, -1));
    spinSpecifyY->SetMinSize(wxSize(50, -1));
    tcVariableX->SetMinSize(wxSize(50, -1));
    tcVariableY->SetMinSize(wxSize(50, -1));
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdPlayVideo::do_layout()
{
    // begin wxGlade: DialogEvtCmdPlayVideo::do_layout
    wxBoxSizer* szPlayVideo = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    szPosition_staticbox->Lower();
    wxStaticBoxSizer* szPosition = new wxStaticBoxSizer(szPosition_staticbox, wxVERTICAL);
    wxFlexGridSizer* gszPosition = new wxFlexGridSizer(4, 3, 2, 2);
    wxBoxSizer* szVariableY = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szVariableX = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szTop = new wxBoxSizer(wxHORIZONTAL);
    szSize_staticbox->Lower();
    wxStaticBoxSizer* szSize = new wxStaticBoxSizer(szSize_staticbox, wxHORIZONTAL);
    szFile_staticbox->Lower();
    wxStaticBoxSizer* szFile = new wxStaticBoxSizer(szFile_staticbox, wxHORIZONTAL);
    szFile->Add(stVideo, 1, wxALIGN_CENTER_VERTICAL, 0);
    szFile->Add(btnVideo, 0, wxALIGN_CENTER_VERTICAL, 0);
    szTop->Add(szFile, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szSize->Add(spinSizeX, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT, 1);
    szSize->Add(stSize, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 1);
    szSize->Add(spinSizeY, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 1);
    szTop->Add(szSize, 0, wxEXPAND, 0);
    szPlayVideo->Add(szTop, 0, wxEXPAND, 0);
    gszPosition->Add(rbtnSpecify, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(szSpecifyX, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(spinSpecifyX, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxRIGHT, 1);
    gszPosition->Add(0, 0, 1, wxEXPAND, 0);
    gszPosition->Add(stSpecifyY, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(spinSpecifyY, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxRIGHT, 1);
    gszPosition->Add(rbtnVariable, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(stVariableX, 0, wxALIGN_CENTER_VERTICAL, 0);
    szVariableX->Add(tcVariableX, 1, wxALIGN_CENTER_VERTICAL, 0);
    szVariableX->Add(btnVariableX, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(szVariableX, 1, wxEXPAND, 0);
    gszPosition->Add(0, 0, 1, wxEXPAND, 0);
    gszPosition->Add(stVariableY, 0, wxALIGN_CENTER_VERTICAL, 0);
    szVariableY->Add(tcVariableY, 1, wxALIGN_CENTER_VERTICAL, 0);
    szVariableY->Add(btnVariableY, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(szVariableY, 1, wxEXPAND, 0);
    gszPosition->AddGrowableCol(2);
    szPosition->Add(gszPosition, 1, wxBOTTOM|wxEXPAND, 1);
    szPlayVideo->Add(szPosition, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szPlayVideo->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szPlayVideo);
    szPlayVideo->Fit(this);
    Layout();
    // end wxGlade
}

