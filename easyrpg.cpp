#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/artprov.h"
#include "wx/sysopt.h"

#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "easyrpg.xpm"
#endif

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
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
    //Frame title
    MyFrame *frame = new MyFrame(_T("EasyRPG"));
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
    fileMenu->Append(MenuitemNewProject, _T("&New Project...\tCtrl-N"), _T("Create a new project"));
    fileMenu->Append(MenuitemOpenProject, _T("&Open Project\tCtrl-O"), _T("Open an existing project"));
    fileMenu->Append(MenuitemCloseProject, _T("&Close Project"), _T("Close the current project"));
    fileMenu->Append(MenuitemSaveProject, _T("&Save Project\tCtrl-S"), _T("Save the current project"));
    fileMenu->AppendSeparator();
    fileMenu->Append(MenuitemCompressGameData, _T("Co&mpress Game Data..."), _T("Compress game data and create a distributable file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(MenuitemQuit, _T("E&xit EasyRPG"), _T("Exit EasyRPG"));
    wxMenu *editMenu = new wxMenu;
    editMenu->Append(MenuitemUndo, _T("&Undo\tCtrl-Z"), _T("Undo the last action"));
    editMenu->AppendSeparator();
    editMenu->Append(MenuitemCut, _T("Cu&t\tCtrl-X"), _T("Cut the selection and put it on the Clipboard"));
    editMenu->Append(MenuitemCopy, _T("&Copy\tCtrl-C"), _T("Copy the selection and put it on the Clipboard"));
    editMenu->Append(MenuitemPaste, _T("&Paste\tCtrl-V"), _T("Insert Clipboard contents"));
    editMenu->Append(MenuitemDelete, _T("&Delete\tDel"), _T("Erase the selection"));
    wxMenu *viewMenu = new wxMenu;
    viewMenu->Append(MenuitemCurrentLayerAndBelow, _T("&Current Layer and Below\tF2"), _T("Display layer currently being edited and the layer below"));
    viewMenu->Append(MenuitemAllLayers, _T("&All Layers\tF3"), _T("Show all layers"));
    viewMenu->AppendSeparator();
    viewMenu->Append(MenuitemDimOtherLayers, _T("&Dim Other Layers\tF4"), _T("Dim all but the layer currently being edited"));
    wxMenu *modeMenu = new wxMenu;
    modeMenu->Append(MenuitemLayer1, _T("Layer &1\tF5"), _T("Switche to layer 1 editing mode"));
    modeMenu->Append(MenuitemLayer2, _T("Layer &2\tF6"), _T("Switche to layer 2 editing mode"));
    modeMenu->Append(MenuitemLayer3, _T("Layer &3\tF7"), _T("Switche to layer 3 editing mode"));
    modeMenu->Append(MenuitemEvents, _T("&Events\tF8"), _T("Switche to event editing mode"));
    wxMenu *drawMenu = new wxMenu;
    drawMenu->Append(MenuitemPencil, _T("&Pencil"), _T("Draw tiles freehand"));
    drawMenu->Append(MenuitemRectangle, _T("&Rectangle"), _T("Draw a rectangle"));
    drawMenu->Append(MenuitemEllipse, _T("&Ellipse"), _T("Draw an ellipse"));
    drawMenu->Append(MenuitemFloodFill, _T("&Flood Fill"), _T("Fill the region with the current tile"));
    drawMenu->Append(MenuitemSelect, _T("&Select"), _T("Select a square portion of the map"));
    wxMenu *scaleMenu = new wxMenu;
    scaleMenu->Append(Menuitem11, _T("1:&1"), _T("Display the map in 1:1 scale"));
    scaleMenu->Append(Menuitem12, _T("1:&2"), _T("Display the map in 1:2 scale"));
    scaleMenu->Append(Menuitem14, _T("1:&4"), _T("Display the map in 1:4 scale"));
    wxMenu *toolsMenu = new wxMenu;
    toolsMenu->Append(MenuitemDatabase, _T("&Database...\tF9"), _T("Open the database"));
    toolsMenu->Append(MenuitemMaterialbase, _T("&Materialbase...\tF10"), _T("Open the materialbase"));
    toolsMenu->Append(MenuitemScriptEditor, _T("&Script Editor...\tF11"), _T("Open the script editor"));
    toolsMenu->Append(MenuitemSoundTest, _T("Sound &Test..."), _T("Open the sound test window"));
    toolsMenu->AppendSeparator();
    toolsMenu->Append(MenuitemOptions, _T("&Options..."), _T("Change editor settings"));
    wxMenu *gameMenu = new wxMenu;
    gameMenu->Append(MenuitemPlaytest, _T("Play&test\tF12"), _T("Start a playtest of this game"));
    gameMenu->AppendSeparator();
    gameMenu->Append(MenuitemChangeTitle, _T("&Change Title..."), _T("Change this game's title"));
    gameMenu->Append(MenuitemSelectRTP, _T("&Select RTP..."), _T("Select an RTP to use in this game"));
    gameMenu->AppendSeparator();
    gameMenu->Append(MenuitemOpenGameFolder, _T("&Open Game Folder"), _T("Open folder for game currently being edited"));
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(MenuitemContents, _T("&Contents\tF1"), _T("Open the help"));
    helpMenu->AppendSeparator();
    helpMenu->Append(MenuitemAbout, _T("&About..."), _T("Display program information, version number and copyright"));
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(editMenu, _T("&Edit"));
    menuBar->Append(viewMenu, _T("&View"));
    menuBar->Append(modeMenu, _T("&Mode"));
    menuBar->Append(drawMenu, _T("&Draw"));
    menuBar->Append(scaleMenu, _T("&Scale"));
    menuBar->Append(toolsMenu, _T("&Tools"));
    menuBar->Append(gameMenu, _T("&Game"));
    menuBar->Append(helpMenu, _T("&Help"));
    SetMenuBar(menuBar);

    //Tool bar
    wxToolBar* toolBar = CreateToolBar();
    toolBar->AddTool(wxID_NEW, wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_TOOLBAR), _T("New"), _T("Create a new project"));
    toolBar->AddTool(wxID_OPEN, wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR), _T("Open"), _T("Open an existing project"));
    toolBar->AddTool(wxID_SAVE, wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR), _T("Save"), _T("Save the current project"));
    toolBar->AddSeparator();
    toolBar->AddTool(wxID_CUT, wxArtProvider::GetBitmap(wxART_CUT, wxART_TOOLBAR), _T("Cut"), _T("Cut the selection and put it on the Clipboard"));
    toolBar->AddTool(wxID_COPY, wxArtProvider::GetBitmap(wxART_COPY, wxART_TOOLBAR), _T("Copy"), _T("Copy the selection and put it on the Clipboard"));
    toolBar->AddTool(wxID_PASTE, wxArtProvider::GetBitmap(wxART_PASTE, wxART_TOOLBAR), _T("Paste"), _T("Insert Clipboard contents"));
    toolBar->AddTool(wxID_DELETE, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Delete"), _T("Erase the selection"));
    toolBar->AddSeparator();
    toolBar->AddTool(wxID_UNDO, wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR), _T("Undo"), _T("Undo the last action"));
    toolBar->AddSeparator();
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Layer 1"), _T("Switche to layer 1 editing mode"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Layer 2"), _T("Switche to layer 2 editing mode"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Layer 3"), _T("Switche to layer 3 editing mode"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Events"), _T("Switche to event editing mode"));
    toolBar->AddSeparator();
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Pencil"), _T("Draw tiles freehand"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Rectangle"), _T("Draw a rectangle"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Ellipse"), _T("Draw an ellipse"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Flood Fill"), _T("Fill the region with the current tile"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Select"), _T("Select a square portion of the map"));
    toolBar->AddSeparator();
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("1:1"), _T("Display the map in 1:1 scale"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("1:2"), _T("Display the map in 1:2 scale"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("1:4"), _T("Display the map in 1:4 scale"));
    toolBar->AddSeparator();
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Database"), _T("Open the database"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Materialbase"), _T("Open the materialbase"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Script Editor"), _T("Open the script editor"));
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Sound Test"), _T("Open the sound test window"));
    toolBar->AddSeparator();
    toolBar->AddTool(-1, wxArtProvider::GetBitmap(wxART_CROSS_MARK, wxART_TOOLBAR), _T("Playtest"), _T("Start a playtest of this game"));
    toolBar->Realize();

    //Status bar
    CreateStatusBar();
}

//Events
void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("EasyRPG\n")
                _T("version 0.0.0\n")
                _T("Copyright (C) 2006 EasyRPG Project\n\n")
                _T("EasyRPG is a computer role-playing games creation tool\n\n")
                _T("EasyRPG comes with ABSOLUTELY NO WARRANTY.\n")
                _T("This is free software, and you are welcome\n")
                _T("to redistribute it under certain conditions.\n")
                _T("See the GNU General Public license for details.\n\n")
                _T("Homepage:\n")
                _T("http://easyrpg.sourceforge.net/"));
    wxMessageBox(msg, _T("About EasyRPG"), wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
