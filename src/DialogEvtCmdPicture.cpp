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
#include "DialogEvtCmdPicture.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdPicture::DialogEvtCmdPicture(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdPicture::DialogEvtCmdPicture
    szPicture2_staticbox = new wxStaticBox(this, wxID_ANY, _("Picture"));
    szPosition_staticbox = new wxStaticBox(this, wxID_ANY, _("Picture position (coordinates)"));
    szIntensity_staticbox = new wxStaticBox(this, wxID_ANY, _("Intensity"));
    szTrasparency_staticbox = new wxStaticBox(this, wxID_ANY, _("Transparency"));
    szAttributes_staticbox = new wxStaticBox(this, wxID_ANY, _("Other picture attributes"));
    szNumber_staticbox = new wxStaticBox(this, wxID_ANY, _("Picture number"));
    spinNumber = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    tcPicture = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnPicture = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    rbtnSpecify = new wxRadioButton(this, wxID_ANY, _("Specify"));
    stSpecifyX = new wxStaticText(this, wxID_ANY, _("X:"));
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
    linePicture = new wxStaticLine(this, wxID_ANY);
    chbScrollMapFix = new wxCheckBox(this, wxID_ANY, _("Scroll map fix"));
    spinIntensity = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stIntensity = new wxStaticText(this, wxID_ANY, _("%"));
    spinTrasparency = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    stTrasparency = new wxStaticText(this, wxID_ANY, _("%"));
    const wxString rbTrasparentColor_choices[] = {
        _("Yes"),
        _("No"),
    };
    rbTrasparentColor = new wxRadioBox(this, wxID_ANY, _("Transparent color"), wxDefaultPosition, wxDefaultSize, 2, rbTrasparentColor_choices, 1, wxRA_SPECIFY_ROWS);
    tcAttributes = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    btnAttributes = new wxButton(this, wxID_ANY, _("..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdPicture::set_properties()
{
    // begin wxGlade: DialogEvtCmdPicture::set_properties
    SetTitle(_("Show picture"));
    spinNumber->SetMinSize(wxSize(90, -1));
    tcPicture->SetMinSize(wxSize(50, -1));
    spinSpecifyX->SetMinSize(wxSize(50, -1));
    spinSpecifyY->SetMinSize(wxSize(50, -1));
    tcVariableX->SetMinSize(wxSize(50, -1));
    tcVariableY->SetMinSize(wxSize(50, -1));
    spinIntensity->SetMinSize(wxSize(50, -1));
    spinTrasparency->SetMinSize(wxSize(70, -1));
    rbTrasparentColor->SetMinSize(wxSize(110, -1));
    rbTrasparentColor->SetSelection(0);
    tcAttributes->SetMinSize(wxSize(50, -1));
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdPicture::do_layout()
{
    // begin wxGlade: DialogEvtCmdPicture::do_layout
    wxBoxSizer* szPicture = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    szAttributes_staticbox->Lower();
    wxStaticBoxSizer* szAttributes = new wxStaticBoxSizer(szAttributes_staticbox, wxHORIZONTAL);
    wxBoxSizer* szMiddle = new wxBoxSizer(wxHORIZONTAL);
    szTrasparency_staticbox->Lower();
    wxStaticBoxSizer* szTrasparency = new wxStaticBoxSizer(szTrasparency_staticbox, wxHORIZONTAL);
    szIntensity_staticbox->Lower();
    wxStaticBoxSizer* szIntensity = new wxStaticBoxSizer(szIntensity_staticbox, wxHORIZONTAL);
    szPosition_staticbox->Lower();
    wxStaticBoxSizer* szPosition = new wxStaticBoxSizer(szPosition_staticbox, wxVERTICAL);
    wxFlexGridSizer* gszPosition = new wxFlexGridSizer(4, 3, 2, 2);
    wxBoxSizer* szVariableY = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szVariableX = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szTop = new wxBoxSizer(wxHORIZONTAL);
    szPicture2_staticbox->Lower();
    wxStaticBoxSizer* szPicture2 = new wxStaticBoxSizer(szPicture2_staticbox, wxHORIZONTAL);
    szNumber_staticbox->Lower();
    wxStaticBoxSizer* szNumber = new wxStaticBoxSizer(szNumber_staticbox, wxHORIZONTAL);
    szNumber->Add(spinNumber, 0, wxALIGN_CENTER_VERTICAL, 0);
    szTop->Add(szNumber, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szPicture2->Add(tcPicture, 1, wxALIGN_CENTER_VERTICAL, 0);
    szPicture2->Add(btnPicture, 0, wxALIGN_CENTER_VERTICAL, 0);
    szTop->Add(szPicture2, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szPicture->Add(szTop, 0, wxEXPAND, 0);
    gszPosition->Add(rbtnSpecify, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0);
    gszPosition->Add(stSpecifyX, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(spinSpecifyX, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxRIGHT, 1);
    gszPosition->Add(0, 0, 1, wxEXPAND, 0);
    gszPosition->Add(stSpecifyY, 0, wxALIGN_CENTER_VERTICAL, 0);
    gszPosition->Add(spinSpecifyY, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxRIGHT, 1);
    gszPosition->Add(rbtnVariable, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0);
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
    szPosition->Add(linePicture, 0, wxBOTTOM|wxEXPAND|wxTOP, 1);
    szPosition->Add(chbScrollMapFix, 0, wxEXPAND|wxTOP, 1);
    szPicture->Add(szPosition, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szIntensity->Add(spinIntensity, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 1);
    szIntensity->Add(stIntensity, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 1);
    szMiddle->Add(szIntensity, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szTrasparency->Add(spinTrasparency, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 1);
    szTrasparency->Add(stTrasparency, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 1);
    szMiddle->Add(szTrasparency, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szMiddle->Add(rbTrasparentColor, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szPicture->Add(szMiddle, 0, wxEXPAND, 0);
    szAttributes->Add(tcAttributes, 1, wxALIGN_CENTER_VERTICAL, 0);
    szAttributes->Add(btnAttributes, 0, wxALIGN_CENTER_VERTICAL, 0);
    szPicture->Add(szAttributes, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szPicture->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szPicture);
    szPicture->Fit(this);
    Layout();
    // end wxGlade
}

