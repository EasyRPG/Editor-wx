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

#ifndef DIALOGEVTCMDPARAMETER_H
#define DIALOGEVTCMDPARAMETER_H

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


class DialogEvtCmdParameter: public wxDialog {
public:
    // begin wxGlade: DialogEvtCmdParameter::ids
    // end wxGlade

    DialogEvtCmdParameter(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: DialogEvtCmdParameter::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: DialogEvtCmdParameter::attributes
    wxStaticBox* szOperand_staticbox;
    wxStaticBox* szType_staticbox;
    wxStaticBox* szTarget_staticbox;
    wxRadioButton* rbtnTargetParty;
    wxRadioButton* rbtnTargetFixed;
    wxChoice* chTargetFixed;
    wxRadioButton* rbtnTargetVariable;
    wxTextCtrl* tcTargetVariable;
    wxButton* btnTargetVariable;
    wxRadioBox* rbOperation;
    wxChoice* chType;
    wxRadioButton* rbtnOperandConstant;
    wxSpinCtrl* spinOperandConstant;
    wxRadioButton* rbtnOperandVar;
    wxTextCtrl* tcOperandVariable;
    wxButton* btnOperandVariable;
    wxButton* btnOK;
    wxButton* btnCancel;
    wxButton* btnHelp;
    // end wxGlade
}; // wxGlade: end class


#endif // DIALOGEVTCMDPARAMETER_H
