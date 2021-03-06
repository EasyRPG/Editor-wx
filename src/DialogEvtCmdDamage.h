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

#ifndef DIALOGEVTCMDDAMAGE_H
#define DIALOGEVTCMDDAMAGE_H

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>

#ifndef APP_CATALOG
#define APP_CATALOG "appEditor"  // replace with the appropriate catalog name
#endif


// begin wxGlade: ::dependencies
#include <wx/spinctrl.h>
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade


class DialogEvtCmdDamage: public wxDialog {
public:
    // begin wxGlade: DialogEvtCmdDamage::ids
    // end wxGlade

    DialogEvtCmdDamage(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: DialogEvtCmdDamage::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: DialogEvtCmdDamage::attributes
    wxStaticBox* szVariable_staticbox;
    wxStaticBox* szAttack2_staticbox;
    wxStaticBox* szIntelligence_staticbox;
    wxStaticBox* szDefense_staticbox;
    wxStaticBox* szAttack_staticbox;
    wxStaticBox* szTarget_staticbox;
    wxRadioButton* rbtnTargetParty;
    wxRadioButton* rbtnTargetFixed;
    wxChoice* chTargetFixed;
    wxRadioButton* rbtnTargetVariable;
    wxTextCtrl* tcTargetVariable;
    wxButton* btnTargetVariable;
    wxSpinCtrl* spinAttack;
    wxSpinCtrl* spinDefense;
    wxStaticText* stDefense;
    wxSpinCtrl* spinIntelligence;
    wxStaticText* stInteligence;
    wxSpinCtrl* spinAttack2;
    wxCheckBox* chbVariableEnable;
    wxTextCtrl* tcVariable;
    wxButton* btnVariable;
    wxButton* btnOK;
    wxButton* btnCancel;
    wxButton* btnHelp;
    // end wxGlade
}; // wxGlade: end class


#endif // DIALOGEVTCMDDAMAGE_H
