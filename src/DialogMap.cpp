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
#include "DialogMap.h"

// begin wxGlade: ::extracode
// end wxGlade


DialogMap::DialogMap(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER)
{
    // begin wxGlade: DialogMap::DialogMap
    szGraphics_staticbox = new wxStaticBox(this, wxID_ANY, _("Graphics"));
    szSize_staticbox = new wxStaticBox(this, wxID_ANY, _("Size"));
    szLoopTime_staticbox = new wxStaticBox(this, wxID_ANY, _("Loop time"));
    szTroopEncounters_staticbox = new wxStaticBox(this, wxID_ANY, _("Troop encounters"));
    szPanoramaGraphic_staticbox = new wxStaticBox(this, wxID_ANY, _("Panorama graphic"));
    szParallaxOptions_staticbox = new wxStaticBox(this, wxID_ANY, _("Parallax options"));
    szPanorama_staticbox = new wxStaticBox(this, wxID_ANY, _("Panorama"));
    szMapMusic_staticbox = new wxStaticBox(this, wxID_ANY, _("Map music"));
    szBattleBackground_staticbox = new wxStaticBox(this, wxID_ANY, _("Battle background"));
    szName_staticbox = new wxStaticBox(this, wxID_ANY, _("Name"));
    tcName = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    const wxString chGraphics_choices[] = {
        _("<set by wxGlade>"),
    };
    chGraphics = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 1, chGraphics_choices);
    spinSizeWidth = new wxSpinCtrl(this, wxID_ANY, wxT("20"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 20, 500);
    stSize = new wxStaticText(this, wxID_ANY, _("X"));
    spinSizeHeight = new wxSpinCtrl(this, wxID_ANY, wxT("15"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 15, 500);
    const wxString chLoopTime_choices[] = {
        _("<set by wxGlade>"),
    };
    chLoopTime = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 1, chLoopTime_choices);
    lcTroopEncounters = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN|wxLC_REPORT);
    stEncounterSteps = new wxStaticText(this, wxID_ANY, _("Encounter steps"));
    spinEncounterSteps = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    chbUsePanorama = new wxCheckBox(this, wxID_ANY, _("Use panorama"));
    bmpPanoramaGraphic = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN);
    btnPanoramaGraphic = new wxButton(this, wxID_ANY, _("Select..."), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
    chbParallaxHorizontal = new wxCheckBox(this, wxID_ANY, _("Horizontal"));
    chbParallaxHorizontalAutomatic = new wxCheckBox(this, wxID_ANY, _("Automatic"));
    stParallaxHorizontalSpeed = new wxStaticText(this, wxID_ANY, _("Speed"));
    spinParallaxHorizontalSpeed = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    szParallaxSeparator = new wxStaticLine(this, wxID_ANY);
    chbParallaxVertical = new wxCheckBox(this, wxID_ANY, _("Vertical"));
    chbParallaxVerticalAutomatic = new wxCheckBox(this, wxID_ANY, _("Automatic"));
    stParallaxVerticalSpeed = new wxStaticText(this, wxID_ANY, _("Speed"));
    spinParallaxVerticalSpeed = new wxSpinCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100);
    rbtnMapMusicFromParentMap = new wxRadioButton(this, wxID_ANY, _("From parent map"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    rbtnMapMusicNone = new wxRadioButton(this, wxID_ANY, _("None"));
    rbtnMapMusicSelect = new wxRadioButton(this, wxID_ANY, _("Select"));
    tcMapMusicSelect = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    btnMapMusicSelect = new wxButton(this, wxID_ANY, _("..."));
    rbtnBattleBackgroundFromParentMap = new wxRadioButton(this, wxID_ANY, _("From parent map"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    rbtnBattleBackgroundFromTerrain = new wxRadioButton(this, wxID_ANY, _("From terrain"));
    rbtnBattleBackgroundSelect = new wxRadioButton(this, wxID_ANY, _("Select"));
    tcBattleBackgroundSelect = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    btnBattleBackgroundSelect = new wxButton(this, wxID_ANY, _("..."));
    const wxString rbTeleport_choices[] = {
        _("From parent map"),
        _("Allowed"),
        _("Disallowed"),
    };
    rbTeleport = new wxRadioBox(this, wxID_ANY, _("Teleport"), wxDefaultPosition, wxDefaultSize, 3, rbTeleport_choices, 1, wxRA_SPECIFY_COLS);
    const wxString rbEscape_choices[] = {
        _("From parent map"),
        _("Allowed"),
        _("Disallowed"),
    };
    rbEscape = new wxRadioBox(this, wxID_ANY, _("Escape"), wxDefaultPosition, wxDefaultSize, 3, rbEscape_choices, 1, wxRA_SPECIFY_COLS);
    const wxString rbSave_choices[] = {
        _("From parent map"),
        _("Allowed"),
        _("Disallowed"),
    };
    rbSave = new wxRadioBox(this, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 3, rbSave_choices, 1, wxRA_SPECIFY_COLS);
    btnOK = new wxButton(this, wxID_OK, wxEmptyString);
    btnCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);
    btnHelp = new wxButton(this, wxID_HELP, wxEmptyString);

    set_properties();
    do_layout();
    // end wxGlade
}


void DialogMap::set_properties()
{
    // begin wxGlade: DialogMap::set_properties
    SetTitle(_("Map Properties"));
    tcName->SetMinSize(wxSize(50, -1));
    chGraphics->SetMinSize(wxSize(50, -1));
    chGraphics->SetSelection(0);
    spinSizeWidth->SetMinSize(wxSize(50, -1));
    spinSizeHeight->SetMinSize(wxSize(50, -1));
    chLoopTime->SetMinSize(wxSize(50, -1));
    chLoopTime->SetSelection(0);
    lcTroopEncounters->SetMinSize(wxSize(50, -1));
    spinEncounterSteps->SetMinSize(wxSize(50, -1));
    bmpPanoramaGraphic->SetMinSize(wxSize(160, 120));
    spinParallaxHorizontalSpeed->SetMinSize(wxSize(50, -1));
    spinParallaxVerticalSpeed->SetMinSize(wxSize(50, -1));
    tcMapMusicSelect->SetMinSize(wxSize(50, -1));
    btnMapMusicSelect->SetMinSize(wxSize(25, -1));
    tcBattleBackgroundSelect->SetMinSize(wxSize(50, -1));
    btnBattleBackgroundSelect->SetMinSize(wxSize(25, -1));
    rbTeleport->SetSelection(0);
    rbEscape->SetSelection(0);
    rbSave->SetSelection(0);
    btnOK->SetDefault();
    // end wxGlade
}


void DialogMap::do_layout()
{
    // begin wxGlade: DialogMap::do_layout
    wxBoxSizer* szMap = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szTop = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szTopRight = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* szTopRightBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szTopRightMiddle = new wxBoxSizer(wxHORIZONTAL);
    szBattleBackground_staticbox->Lower();
    wxStaticBoxSizer* szBattleBackground = new wxStaticBoxSizer(szBattleBackground_staticbox, wxVERTICAL);
    wxBoxSizer* szBattleBackgroundSelect = new wxBoxSizer(wxHORIZONTAL);
    szMapMusic_staticbox->Lower();
    wxStaticBoxSizer* szMapMusic = new wxStaticBoxSizer(szMapMusic_staticbox, wxVERTICAL);
    wxBoxSizer* szMapMusicSelect = new wxBoxSizer(wxHORIZONTAL);
    szPanorama_staticbox->Lower();
    wxStaticBoxSizer* szPanorama = new wxStaticBoxSizer(szPanorama_staticbox, wxVERTICAL);
    wxBoxSizer* szUsePanorama = new wxBoxSizer(wxHORIZONTAL);
    szParallaxOptions_staticbox->Lower();
    wxStaticBoxSizer* szParallaxOptions = new wxStaticBoxSizer(szParallaxOptions_staticbox, wxVERTICAL);
    wxBoxSizer* szParallaxVerticalSpeed = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szParallaxVerticalAutomatic = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szParallaxHorizontalSpeed = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* szParallaxHorizontalAutomatic = new wxBoxSizer(wxHORIZONTAL);
    szPanoramaGraphic_staticbox->Lower();
    wxStaticBoxSizer* szPanoramaGraphic = new wxStaticBoxSizer(szPanoramaGraphic_staticbox, wxVERTICAL);
    wxBoxSizer* szTopLeft = new wxBoxSizer(wxVERTICAL);
    szTroopEncounters_staticbox->Lower();
    wxStaticBoxSizer* szTroopEncounters = new wxStaticBoxSizer(szTroopEncounters_staticbox, wxVERTICAL);
    wxBoxSizer* szEncounterSteps = new wxBoxSizer(wxHORIZONTAL);
    szLoopTime_staticbox->Lower();
    wxStaticBoxSizer* szLoopTime = new wxStaticBoxSizer(szLoopTime_staticbox, wxHORIZONTAL);
    szSize_staticbox->Lower();
    wxStaticBoxSizer* szSize = new wxStaticBoxSizer(szSize_staticbox, wxHORIZONTAL);
    szGraphics_staticbox->Lower();
    wxStaticBoxSizer* szGraphics = new wxStaticBoxSizer(szGraphics_staticbox, wxHORIZONTAL);
    szName_staticbox->Lower();
    wxStaticBoxSizer* szName = new wxStaticBoxSizer(szName_staticbox, wxHORIZONTAL);
    szName->Add(tcName, 1, 0, 0);
    szTopLeft->Add(szName, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szGraphics->Add(chGraphics, 1, 0, 0);
    szTopLeft->Add(szGraphics, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szSize->Add(spinSizeWidth, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT, 1);
    szSize->Add(stSize, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 1);
    szSize->Add(spinSizeHeight, 1, wxALIGN_CENTER_VERTICAL|wxLEFT, 1);
    szTopLeft->Add(szSize, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szLoopTime->Add(chLoopTime, 1, 0, 0);
    szTopLeft->Add(szLoopTime, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szTroopEncounters->Add(lcTroopEncounters, 1, wxBOTTOM|wxEXPAND, 1);
    szEncounterSteps->Add(stEncounterSteps, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP, 1);
    szEncounterSteps->Add(spinEncounterSteps, 1, wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, 1);
    szTroopEncounters->Add(szEncounterSteps, 0, wxEXPAND, 0);
    szTopLeft->Add(szTroopEncounters, 1, wxBOTTOM|wxEXPAND|wxLEFT|wxRIGHT, 1);
    szTop->Add(szTopLeft, 1, wxEXPAND, 0);
    szPanorama->Add(chbUsePanorama, 0, wxEXPAND, 0);
    szPanoramaGraphic->Add(bmpPanoramaGraphic, 0, wxBOTTOM, 1);
    szPanoramaGraphic->Add(btnPanoramaGraphic, 0, wxALIGN_RIGHT|wxTOP, 1);
    szUsePanorama->Add(szPanoramaGraphic, 0, wxEXPAND|wxRIGHT, 1);
    szParallaxOptions->Add(0, 0, 1, wxEXPAND, 0);
    szParallaxOptions->Add(chbParallaxHorizontal, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxEXPAND, 1);
    szParallaxHorizontalAutomatic->Add(15, 15, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0);
    szParallaxHorizontalAutomatic->Add(chbParallaxHorizontalAutomatic, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxTOP, 1);
    szParallaxOptions->Add(szParallaxHorizontalAutomatic, 0, wxEXPAND, 0);
    szParallaxHorizontalSpeed->Add(stParallaxHorizontalSpeed, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP, 1);
    szParallaxHorizontalSpeed->Add(spinParallaxHorizontalSpeed, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxTOP, 1);
    szParallaxOptions->Add(szParallaxHorizontalSpeed, 0, wxEXPAND, 0);
    szParallaxOptions->Add(0, 0, 1, wxEXPAND, 0);
    szParallaxOptions->Add(szParallaxSeparator, 0, wxBOTTOM|wxEXPAND|wxTOP, 1);
    szParallaxOptions->Add(0, 0, 1, wxEXPAND, 0);
    szParallaxOptions->Add(chbParallaxVertical, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxEXPAND|wxTOP, 1);
    szParallaxVerticalAutomatic->Add(15, 15, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0);
    szParallaxVerticalAutomatic->Add(chbParallaxVerticalAutomatic, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxTOP, 1);
    szParallaxOptions->Add(szParallaxVerticalAutomatic, 0, wxEXPAND, 0);
    szParallaxVerticalSpeed->Add(stParallaxVerticalSpeed, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP, 1);
    szParallaxVerticalSpeed->Add(spinParallaxVerticalSpeed, 1, wxLEFT|wxTOP, 1);
    szParallaxOptions->Add(szParallaxVerticalSpeed, 0, wxEXPAND, 0);
    szParallaxOptions->Add(0, 0, 1, wxEXPAND, 0);
    szUsePanorama->Add(szParallaxOptions, 1, wxEXPAND|wxLEFT, 1);
    szPanorama->Add(szUsePanorama, 0, wxEXPAND, 0);
    szTopRight->Add(szPanorama, 0, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szMapMusic->Add(rbtnMapMusicFromParentMap, 0, wxALL|wxEXPAND, 1);
    szMapMusic->Add(rbtnMapMusicNone, 0, wxALL|wxEXPAND, 1);
    szMapMusic->Add(rbtnMapMusicSelect, 0, wxALL|wxEXPAND, 1);
    szMapMusicSelect->Add(tcMapMusicSelect, 1, wxALIGN_CENTER_VERTICAL, 0);
    szMapMusicSelect->Add(btnMapMusicSelect, 0, 0, 0);
    szMapMusic->Add(szMapMusicSelect, 1, wxEXPAND, 0);
    szTopRightMiddle->Add(szMapMusic, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szBattleBackground->Add(rbtnBattleBackgroundFromParentMap, 0, wxALL|wxEXPAND, 1);
    szBattleBackground->Add(rbtnBattleBackgroundFromTerrain, 0, wxALL|wxEXPAND, 1);
    szBattleBackground->Add(rbtnBattleBackgroundSelect, 0, wxALL|wxEXPAND, 1);
    szBattleBackgroundSelect->Add(tcBattleBackgroundSelect, 1, wxALIGN_CENTER_VERTICAL, 0);
    szBattleBackgroundSelect->Add(btnBattleBackgroundSelect, 0, 0, 0);
    szBattleBackground->Add(szBattleBackgroundSelect, 1, wxEXPAND, 0);
    szTopRightMiddle->Add(szBattleBackground, 1, wxEXPAND|wxLEFT|wxRIGHT, 1);
    szTopRight->Add(szTopRightMiddle, 0, wxEXPAND, 0);
    szTopRightBottom->Add(rbTeleport, 1, wxBOTTOM|wxLEFT|wxRIGHT, 1);
    szTopRightBottom->Add(rbEscape, 1, wxBOTTOM|wxLEFT|wxRIGHT, 1);
    szTopRightBottom->Add(rbSave, 1, wxBOTTOM|wxLEFT|wxRIGHT, 1);
    szTopRight->Add(szTopRightBottom, 0, wxEXPAND, 0);
    szTop->Add(szTopRight, 0, wxEXPAND, 0);
    szMap->Add(szTop, 1, wxEXPAND, 0);
    szBottom->Add(btnOK, 0, wxALL, 1);
    szBottom->Add(btnCancel, 0, wxALL, 1);
    szBottom->Add(btnHelp, 0, wxALL, 1);
    szMap->Add(szBottom, 0, wxALIGN_RIGHT|wxBOTTOM|wxRIGHT, 3);
    SetSizer(szMap);
    szMap->Fit(this);
    Layout();
    // end wxGlade
}
