#include "main.h"
#include "mainwindow.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	mainwindow* mymainwindow = new mainwindow(NULL, wxID_ANY, wxEmptyString);
	SetTopWindow(mymainwindow);
	mymainwindow->Show();
	return true;
}

