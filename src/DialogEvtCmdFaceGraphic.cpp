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
#include "DialogEvtCmdFaceGraphic.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogEvtCmdFaceGraphic::DialogEvtCmdFaceGraphic(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogEvtCmdFaceGraphic::DialogEvtCmdFaceGraphic
    szOptions_staticbox = new wxStaticBox(this, wxID_ANY, _("Options"));
    szFaceGraphic2_staticbox = new wxStaticBox(this, wxID_ANY, _("Face graphic"));
    bmpFaceGraphic = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    btnSelect = new wxButton(this, wxID_ANY, _("Select..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    btnDelete = new wxButton(this, wxID_DELETE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    const wxString rbPosition_choices[] = {
        _("Left"),
        _("Right"),
    };
    rbPosition = new wxRadioBox(this, wxID_ANY, _("Position"), wxDefaultPosition, wxDefaultSize, 2, rbPosition_choices, 1, wxRA_SPECIFY_COLS);
    chbHorizontalMirror = new wxCheckBox(this, wxID_ANY, _("Horizontal mirror"));
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogEvtCmdFaceGraphic::set_properties()
{
    // begin wxGlade: DialogEvtCmdFaceGraphic::set_properties
    SetTitle(_("Show face graphic"));
    bmpFaceGraphic->SetMinSize(wxSize(96, 96));
    rbPosition->SetSelection(0);
    btnOK->SetDefault();
    // end wxGlade
}


void DialogEvtCmdFaceGraphic::do_layout()
{
    // begin wxGlade: DialogEvtCmdFaceGraphic::do_layout
    wxBoxSizer* szFaceGraphic = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    szOptions_staticbox->Lower();
    wxStaticBoxSizer* szOptions = new wxStaticBoxSizer(szOptions_staticbox, wxHORIZONTAL);
    wxBoxSizer* szTop = new wxBoxSizer(wxHORIZONTAL);
    szFaceGraphic2_staticbox->Lower();
    wxStaticBoxSizer* szFaceGraphic2 = new wxStaticBoxSizer(szFaceGraphic2_staticbox, wxHORIZONTAL);
    wxBoxSizer* szFaceGraphicOptions = new wxBoxSizer(wxVERTICAL);
    szFaceGraphic2->Add(bmpFaceGraphic, 0, wxRIGHT, 1);
    szFaceGraphicOptions->Add(btnSelect, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxTOP, 1);
    szFaceGraphicOptions->Add(btnDelete, 0, wxEXPAND|wxLEFT|wxTOP, 1);
    szFaceGraphic2->Add(szFaceGraphicOptions, 0, wxALIGN_BOTTOM, 0);
    szTop->Add(szFaceGraphic2, 1, wxLEFT|wxRIGHT, 1);
    szTop->Add(rbPosition, 0, wxLEFT|wxRIGHT, 1);
    szFaceGraphic->Add(szTop, 0, wxEXPAND, 0);
    szOptions->Add(chbHorizontalMirror, 1, wxALL, 1);
    szFaceGraphic->Add(szOptions, 0, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBottom->Add(btnOK, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALIGN_BOTTOM|wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALIGN_BOTTOM|wxALL, 1);
    szFaceGraphic->Add(szBottom, 1, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szFaceGraphic);
    szFaceGraphic->Fit(this);
    Layout();
    // end wxGlade
}

