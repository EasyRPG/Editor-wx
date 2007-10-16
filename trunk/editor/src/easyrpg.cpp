/* easyrpg.cpp, EasyRPG wxWidgets tests before applying wxglade/easyrpg.wxg
   Copyright (C) 2007 EasyRPG Project <http://easyrpg.sourceforge.net/>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "wx/wx.h"
#include "wx/intl.h"
#include "wx/artprov.h"

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "easyrpg.xpm"
#endif

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	wxLocale easyrpgLocale;
};

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title);
	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);
private:
	DECLARE_EVENT_TABLE()
};

enum
{
	//Menu items
	MenuitemCompressGameData,

	MenuitemCurrentLayerAndBelow,
	MenuitemAllLayers,
	MenuitemDimOtherLayers,

	MenuitemLayer1,
	MenuitemLayer2,
	MenuitemLayer3,
	MenuitemEvents,

	MenuitemPencil,
	MenuitemRectangle,
	MenuitemEllipse,
	MenuitemFloodFill,
	MenuitemSelect,

	Menuitem11,
	Menuitem12,
	Menuitem14,

	MenuitemDatabase,
	MenuitemMaterialbase,
	MenuitemScriptEditor,
	MenuitemSoundTest,
	MenuitemOptions,

	MenuitemPlaytest,
	MenuitemChangeTitle,
	MenuitemSelectRTP,
	MenuitemOpenGameFolder,

	MenuitemNewProject = wxID_NEW,
	MenuitemOpenProject = wxID_OPEN,
	MenuitemCloseProject = wxID_CLOSE,
	MenuitemSaveProject = wxID_SAVE,
	MenuitemUndo = wxID_UNDO,
	MenuitemCut = wxID_CUT,
	MenuitemCopy = wxID_COPY,
	MenuitemPaste = wxID_PASTE,
	MenuitemDelete = wxID_DELETE,
	MenuitemContents = wxID_HELP_CONTENTS,
	MenuitemQuit = wxID_EXIT,
	MenuitemAbout = wxID_ABOUT
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(MenuitemAbout, MyFrame::OnAbout)
	EVT_MENU(MenuitemQuit,  MyFrame::OnQuit)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxLocale::AddCatalogLookupPathPrefix(wxT("."));
	easyrpgLocale.AddCatalog(wxT("easyrpg"));
	//Frame title
	MyFrame *frame = new MyFrame(_("EasyRPG"));
	frame->Show(true);
	return true;
}

// Frame
MyFrame::MyFrame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title)
{
	SetIcon(wxICON(easyrpg));

	//Menu bar
	wxMenu *fileMenu = new wxMenu;
	fileMenu->Append(MenuitemNewProject, _("&New Project...\tCtrl-N"), _("Create a new project"));
	fileMenu->Append(MenuitemOpenProject, _("&Open Project\tCtrl-O"), _("Open an existing project"));
	fileMenu->Append(MenuitemCloseProject, _("&Close Project"), _("Close the current project"));
	fileMenu->Append(MenuitemSaveProject, _("&Save Project\tCtrl-S"), _("Save the current project"));
	fileMenu->AppendSeparator();
	fileMenu->Append(MenuitemCompressGameData, _("Co&mpress Game Data..."), _("Compress game data and create a distributable file"));
	fileMenu->AppendSeparator();
	fileMenu->Append(MenuitemQuit, _("E&xit EasyRPG"), _("Exit EasyRPG"));
	wxMenu *editMenu = new wxMenu;
	editMenu->Append(MenuitemUndo, _("&Undo\tCtrl-Z"), _("Undo the last action"));
	editMenu->AppendSeparator();
	editMenu->Append(MenuitemCut, _("Cu&t\tCtrl-X"), _("Cut the selection and put it on the Clipboard"));
	editMenu->Append(MenuitemCopy, _("&Copy\tCtrl-C"), _("Copy the selection and put it on the Clipboard"));
	editMenu->Append(MenuitemPaste, _("&Paste\tCtrl-V"), _("Insert Clipboard contents"));
	editMenu->Append(MenuitemDelete, _("&Delete\tDel"), _("Erase the selection"));
	wxMenu *viewMenu = new wxMenu;
	viewMenu->Append(MenuitemCurrentLayerAndBelow, _("&Current Layer and Below\tF2"), _("Display layer currently being edited and the layer below"));
	viewMenu->Append(MenuitemAllLayers, _("&All Layers\tF3"), _("Show all layers"));
	viewMenu->AppendSeparator();
	viewMenu->Append(MenuitemDimOtherLayers, _("&Dim Other Layers\tF4"), _("Dim all but the layer currently being edited"));
	wxMenu *modeMenu = new wxMenu;
	modeMenu->Append(MenuitemLayer1, _("Layer &1\tF5"), _("Switche to layer 1 editing mode"));
	modeMenu->Append(MenuitemLayer2, _("Layer &2\tF6"), _("Switche to layer 2 editing mode"));
	modeMenu->Append(MenuitemLayer3, _("Layer &3\tF7"), _("Switche to layer 3 editing mode"));
	modeMenu->Append(MenuitemEvents, _("&Events\tF8"), _("Switche to event editing mode"));
	wxMenu *drawMenu = new wxMenu;
	drawMenu->Append(MenuitemPencil, _("&Pencil"), _("Draw tiles freehand"));
	drawMenu->Append(MenuitemRectangle, _("&Rectangle"), _("Draw a rectangle"));
	drawMenu->Append(MenuitemEllipse, _("&Ellipse"), _("Draw an ellipse"));
	drawMenu->Append(MenuitemFloodFill, _("&Flood Fill"), _("Fill the region with the current tile"));
	drawMenu->Append(MenuitemSelect, _("&Select"), _("Select a square portion of the map"));
	wxMenu *scaleMenu = new wxMenu;
	scaleMenu->Append(Menuitem11, _("1:&1"), _("Display the map in 1:1 scale"));
	scaleMenu->Append(Menuitem12, _("1:&2"), _("Display the map in 1:2 scale"));
	scaleMenu->Append(Menuitem14, _("1:&4"), _("Display the map in 1:4 scale"));
	wxMenu *toolsMenu = new wxMenu;
	toolsMenu->Append(MenuitemDatabase, _("&Database...\tF9"), _("Open the database"));
	toolsMenu->Append(MenuitemMaterialbase, _("&Materialbase...\tF10"), _("Open the materialbase"));
	toolsMenu->Append(MenuitemScriptEditor, _("&Script Editor...\tF11"), _("Open the script editor"));
	toolsMenu->Append(MenuitemSoundTest, _("Sound &Test..."), _("Open the sound test window"));
	toolsMenu->AppendSeparator();
	toolsMenu->Append(MenuitemOptions, _("&Options..."), _("Change editor settings"));
	wxMenu *gameMenu = new wxMenu;
	gameMenu->Append(MenuitemPlaytest, _("Play&test\tF12"), _("Start a playtest of this game"));
	gameMenu->AppendSeparator();
	gameMenu->Append(MenuitemChangeTitle, _("&Change Title..."), _("Change this game's title"));
	gameMenu->Append(MenuitemSelectRTP, _("&Select RTP..."), _("Select an RTP to use in this game"));
	gameMenu->AppendSeparator();
	gameMenu->Append(MenuitemOpenGameFolder, _("&Open Game Folder"), _("Open folder for game currently being edited"));
	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(MenuitemContents, _("&Contents\tF1"), _("Open the help"));
	helpMenu->AppendSeparator();
	helpMenu->Append(MenuitemAbout, _("&About..."), _("Display program information, version number and copyright"));
	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, _("&File"));
	menuBar->Append(editMenu, _("&Edit"));
	menuBar->Append(viewMenu, _("&View"));
	menuBar->Append(modeMenu, _("&Mode"));
	menuBar->Append(drawMenu, _("&Draw"));
	menuBar->Append(scaleMenu, _("&Scale"));
	menuBar->Append(toolsMenu, _("&Tools"));
	menuBar->Append(gameMenu, _("&Game"));
	menuBar->Append(helpMenu, _("&Help"));
	SetMenuBar(menuBar);

	//Tool bar
	wxToolBar* toolBar = CreateToolBar();
	toolBar->AddTool(wxID_NEW, wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_TOOLBAR), _("New"), _("Create a new project"));
	toolBar->AddTool(wxID_OPEN, wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR), _("Open"), _("Open an existing project"));
	toolBar->AddTool(wxID_SAVE, wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR), _("Save"), _("Save the current project"));
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_CUT, wxArtProvider::GetBitmap(wxART_CUT, wxART_TOOLBAR), _("Cut"), _("Cut the selection and put it on the Clipboard"));
	toolBar->AddTool(wxID_COPY, wxArtProvider::GetBitmap(wxART_COPY, wxART_TOOLBAR), _("Copy"), _("Copy the selection and put it on the Clipboard"));
	toolBar->AddTool(wxID_PASTE, wxArtProvider::GetBitmap(wxART_PASTE, wxART_TOOLBAR), _("Paste"), _("Insert Clipboard contents"));
	toolBar->AddTool(wxID_DELETE, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Delete"), _("Erase the selection"));
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_UNDO, wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR), _("Undo"), _("Undo the last action"));
	toolBar->AddSeparator();
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Layer 1"), _("Switche to layer 1 editing mode"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Layer 2"), _("Switche to layer 2 editing mode"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Layer 3"), _("Switche to layer 3 editing mode"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Events"), _("Switche to event editing mode"));
	toolBar->AddSeparator();
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Pencil"), _("Draw tiles freehand"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Rectangle"), _("Draw a rectangle"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Ellipse"), _("Draw an ellipse"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Flood Fill"), _("Fill the region with the current tile"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Select"), _("Select a square portion of the map"));
	toolBar->AddSeparator();
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("1:1"), _("Display the map in 1:1 scale"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("1:2"), _("Display the map in 1:2 scale"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("1:4"), _("Display the map in 1:4 scale"));
	toolBar->AddSeparator();
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Database"), _("Open the database"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Materialbase"), _("Open the materialbase"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Script Editor"), _("Open the script editor"));
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Sound Test"), _("Open the sound test window"));
	toolBar->AddSeparator();
	toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _("Playtest"), _("Start a playtest of this game"));
	toolBar->Realize();

	//Status bar
	CreateStatusBar();
}

//Events
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxString msg;
	msg.Printf(
		_(
			"EasyRPG\n"
			"version 0.0.0\n"
			"Copyright (C) 2006 EasyRPG Project\n"
			"\n"
			"EasyRPG is a computer role-playing games creation tool\n"
			"\n"
			"EasyRPG comes with ABSOLUTELY NO WARRANTY.\n"
			"This is free software, and you are welcome\n"
			"to redistribute it under certain conditions.\n"
			"See the GNU General Public license for details.\n"
			"\n"
			"Homepage:\n"
			"http://easyrpg.sourceforge.net/"
		)
	);
	wxMessageBox(msg, _("About EasyRPG"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close();
}
