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

#ifndef DIALOGEVTCMDPANORAMA_H
#define DIALOGEVTCMDPANORAMA_H

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>

#ifndef APP_CATALOG
#define APP_CATALOG "appEditor"  // replace with the appropriate catalog name
#endif


// begin wxGlade: ::dependencies
#include <wx/spinctrl.h>
#include <wx/statline.h>
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade


class DialogEvtCmdPanorama: public wxDialog {
public:
    // begin wxGlade: DialogEvtCmdPanorama::ids
    // end wxGlade

    DialogEvtCmdPanorama(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: DialogEvtCmdPanorama::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: DialogEvtCmdPanorama::attributes
    wxStaticBox* szOptions_staticbox;
    wxStaticBox* szBackground_staticbox;
    wxStaticBitmap* bmpBackground;
    wxButton* btnBackground;
    wxCheckBox* btnHScroll;
    wxCheckBox* chbHScrollAuto;
    wxStaticText* stHScrollSpeed;
    wxSpinCtrl* spinHScrollSpeed;
    wxStaticLine* lineOptions;
    wxCheckBox* btnVScroll;
    wxCheckBox* chbVScrollAuto;
    wxStaticText* stVcrollSpeed;
    wxSpinCtrl* spinVScrollSpeed;
    wxButton* btnOK;
    wxButton* btnCancel;
    wxButton* btnHelp;
    // end wxGlade
}; // wxGlade: end class


#endif // DIALOGEVTCMDPANORAMA_H
