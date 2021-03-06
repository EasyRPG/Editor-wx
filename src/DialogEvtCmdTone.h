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

#ifndef DIALOGEVTCMDTONE_H
#define DIALOGEVTCMDTONE_H

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


class DialogEvtCmdTone: public wxDialog {
public:
    // begin wxGlade: DialogEvtCmdTone::ids
    // end wxGlade

    DialogEvtCmdTone(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:
    // begin wxGlade: DialogEvtCmdTone::methods
    void set_properties();
    void do_layout();
    // end wxGlade

protected:
    // begin wxGlade: DialogEvtCmdTone::attributes
    wxStaticBox* szOptions_staticbox;
    wxStaticBox* szTime_staticbox;
    wxStaticBox* szTone2_staticbox;
    wxStaticBox* szPreview_staticbox;
    wxStaticText* st0Percent;
    wxStaticText* st100Percent;
    wxStaticText* st200Percent;
    wxStaticText* stRed;
    wxSlider* slRed;
    wxSpinCtrl* spinRed;
    wxStaticText* stRedPercent;
    wxStaticText* stGreen;
    wxSlider* slGreen;
    wxSpinCtrl* spinGreen;
    wxStaticText* stGreenPercent;
    wxStaticText* stBlue;
    wxSlider* slBlue;
    wxSpinCtrl* spinBlue;
    wxStaticText* stBluePercent;
    wxStaticText* stSaturation;
    wxSlider* slSaturation;
    wxSpinCtrl* spinSaturation;
    wxStaticText* stSaturationPercent;
    wxStaticBitmap* bmpPreview;
    wxSpinCtrl* SpinTime;
    wxStaticText* stTime;
    wxCheckBox* chbWait;
    wxButton* btnOK;
    wxButton* btnCancel;
    wxButton* btnHelp;
    // end wxGlade
}; // wxGlade: end class


#endif // DIALOGEVTCMDTONE_H
