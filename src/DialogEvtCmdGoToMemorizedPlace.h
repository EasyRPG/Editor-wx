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

#ifndef DIALOGEVTCMDGOTOMEMORIZEDPLACE_H
#define DIALOGEVTCMDGOTOMEMORIZEDPLACE_H

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>

#ifndef APP_CATALOG
#define APP_CATALOG "appEditor"  // replace with the appropriate catalog name
#endif


// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade


class DialogEvtCmdGoToMemorizedPlace: public wxDialog {
public:
    // begin wxGlade: DialogEvtCmdGoToMemorizedPlace::ids
    // end wxGlade

    DialogEvtCmdGoToMemorizedPlace(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: DialogEvtCmdGoToMemorizedPlace::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: DialogEvtCmdGoToMemorizedPlace::attributes
    wxStaticBox* szVariable_staticbox;
    wxStaticText* stVariableMapID;
    wxTextCtrl* tcVariableMapID;
    wxButton* btnVariableMapID;
    wxStaticText* stVariableX;
    wxTextCtrl* tcVariableX;
    wxButton* btnVariableX;
    wxStaticText* stVariableY;
    wxTextCtrl* tcVariableY;
    wxButton* btnVariableY;
    wxButton* btnOK;
    wxButton* btnCancel;
    wxButton* btnHelp;
    // end wxGlade
}; // wxGlade: end class


#endif // DIALOGEVTCMDGOTOMEMORIZEDPLACE_H
