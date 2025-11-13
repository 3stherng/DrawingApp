#include "pch.h"
#include "ProjectMain.h"

#include "CAboutBox.h"
#include "ProjectMainFrm.h"

#include <ProjectFramework/Database.h>
#include <ProjectFramework/SaveDom.h>
#include <ProjectFramework/UndoRedoStacks.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
  const constexpr wchar_t* FILE_EXTENSION = L"blah";
  const constexpr wchar_t* FILE_NAME_FORMAT = L"*.blah";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CApp, CWinApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
  ON_COMMAND(ID_FILE_SAVE, OnFileSave)
  ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
  ON_COMMAND(ID_FILE_NEW, OnFileNew)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CApp::CApp() noexcept
{
  // Replace application ID string below with unique ID string; recommended
  // format for string is CompanyName.ProductName.SubProduct.VersionInformation
  SetAppID(L"That DrawingApp 2.0.0");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CApp drawing_app;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CApp::InitInstance()
{
  CWinApp::InitInstance();

  EnableTaskbarInteraction(FALSE);


  // AfxInitRichEdit2() is required to use RichEdit control
  // AfxInitRichEdit2();

  // Standard initialization
  // If you are not using these features and wish to reduce the size
  // of your final executable, you should remove from the following
  // the specific initialization routines you do not need
  // Change the registry key under which our settings are stored
  // TODO: You should modify this string to be something appropriate
  // such as the name of your company or organization
  SetRegistryKey(L"Local AppWizard-Generated Applications");

  // To create the main window, this code creates a new frame window
  // object and then sets it as the application's main window object
  CFrameWnd* pFrame = new CMainFrame();
  if (!pFrame)
    return FALSE;
  m_pMainWnd = pFrame;
  // create and load the frame with its resources
  pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr, nullptr);

  // The one and only window has been initialized, so show and update it
  pFrame->ShowWindow(SW_SHOW);
  pFrame->UpdateWindow();

  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CApp::ExitInstance()
{
  //TODO: handle additional resources you may have added
  return CWinApp::ExitInstance();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CApp message handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CApp::OnFileSave()
{
  CFileDialog file_dialog(FALSE,
                          FILE_EXTENSION,
                          FILE_NAME_FORMAT,
                          OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
                          L"Blah Files (*.blah)|*.blah|All Files (*.*)|*.*||");

  if (file_dialog.DoModal() == IDOK)
  {
    CString file_path = file_dialog.GetPathName();
    SaveXMLDocumentHandler::SaveXMLToFile(file_path.GetString());
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CApp::OnFileOpen()
{
  CFileDialog file_dialog(true);
  if (file_dialog.DoModal() == IDOK)
  {
    CString file_path = file_dialog.GetPathName();
    LoadXMLDocumentHandler::LoadXMLFromFile(file_path.GetString());
  }
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CApp::OnFileNew()
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
  database.CleanUp();
  undo_redo_stacks.CleanUp();

  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}
