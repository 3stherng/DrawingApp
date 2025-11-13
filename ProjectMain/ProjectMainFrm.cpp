#include "pch.h"
#include "ProjectMainFrm.h"

#include "CDialogBoxCreateCircle.h"
#include "CDialogBoxCreateLine.h"
#include "CDialogBoxCreateRectangle.h"
#include "GUIDrawCircle.h"
#include "GUIDrawLine.h"
#include "GUIDrawRectangle.h"
#include "resource.h"

#include <ProjectFramework/UndoRedoStacks.h>

#include <winuser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
  ON_COMMAND(ID_CREATE_RECTANGLE, OnCreateRectangleMenuClicked)
  ON_COMMAND(ID_CREATE_CIRCLE, OnCreateCircleMenuClicked)
  ON_COMMAND(ID_CREATE_LINE, OnCreateLineMenuClicked)
  ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircleToggled)
  ON_COMMAND(ID_DRAW_LINE, OnDrawLineToggled)
  ON_COMMAND(ID_DRAW_RECTANGLE, OnDrawRectangleToggled)
  ON_COMMAND(ID_EDIT_UNDO, OnUndoMenuClicked)
  ON_COMMAND(ID_EDIT_REDO, OnRedoMenuClicked)

  ON_MESSAGE(WM_OPERATION_DIALOG_DESTROYED, OnCommandOperationDialogDestroyed)
  ON_MESSAGE(WM_PROPERTIES_DIALOG_DESTROYED, OnCommandPropertiesDialogDestroyed)
  ON_MESSAGE(WM_REDRAW_EVERYTHING, OnCommandRedrawEverything)
  
  ON_WM_CREATE()
  ON_WM_SETFOCUS()
  ON_WM_KEYDOWN()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::_CreateMenu()
{
  CMenu main_menu;
  main_menu.CreateMenu();

  CMenu menu_file;
  menu_file.CreatePopupMenu();
  menu_file.AppendMenu(MF_STRING, ID_FILE_NEW, L"&New");
  menu_file.AppendMenu(MF_STRING, ID_FILE_OPEN, L"&Open");
  menu_file.AppendMenu(MF_STRING, ID_FILE_SAVE, L"&Save");
  menu_file.AppendMenu(MF_STRING, ID_APP_EXIT, L"E&xit");

  // TODO:
  //MENUITEM "Cu&t\tCtrl+X", ID_EDIT_CUT
  //MENUITEM "&Copy\tCtrl+C", ID_EDIT_COPY
  //MENUITEM "&Paste\tCtrl+V", ID_EDIT_PASTE

  CMenu menu_edit;
  menu_edit.CreatePopupMenu();
  menu_edit.AppendMenu(MF_STRING, ID_EDIT_UNDO, L"&Undo\tCtrl+Z");
  menu_edit.AppendMenu(MF_STRING, ID_EDIT_REDO, L"&Redo\tCtrl+Y");

  CMenu menu_design;
  menu_design.CreatePopupMenu();

  CMenu menu_design_create;
  menu_design_create.CreatePopupMenu();
  menu_design_create.AppendMenu(MF_STRING, ID_CREATE_LINE, L"&Line");
  menu_design_create.AppendMenu(MF_STRING, ID_CREATE_CIRCLE, L"&Circle");
  menu_design_create.AppendMenu(MF_STRING, ID_CREATE_RECTANGLE, L"&Rectangle");

  CMenu menu_design_draw;
  menu_design_draw.CreatePopupMenu();
  menu_design_draw.AppendMenu(MF_STRING | MF_UNCHECKED, ID_DRAW_LINE, L"&Line");
  menu_design_draw.AppendMenu(MF_STRING | MF_UNCHECKED, ID_DRAW_CIRCLE, L"&Circle");
  menu_design_draw.AppendMenu(MF_STRING | MF_UNCHECKED, ID_DRAW_RECTANGLE, L"&Rectangle");

  menu_design.AppendMenu(MF_POPUP, (UINT)menu_design_create.Detach(), L"&Create");
  menu_design.AppendMenu(MF_POPUP, (UINT)menu_design_draw.Detach(), L"&Draw");

  CMenu menu_help;
  menu_help.CreatePopupMenu();
  menu_help.AppendMenu(MF_STRING, ID_APP_ABOUT, L"&About");

  // Append menus to main menu
  // TODO: Fix warning
  main_menu.AppendMenu(MF_POPUP, (UINT)menu_file.Detach(), L"&File");
  main_menu.AppendMenu(MF_POPUP, (UINT)menu_edit.Detach(), L"&Edit");
  main_menu.AppendMenu(MF_POPUP, (UINT)menu_design.Detach(), L"&Design");
  main_menu.AppendMenu(MF_POPUP, (UINT)menu_help.Detach(), L"&Help");

  SetMenu(&main_menu);
  main_menu.Detach();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  _CreateMenu();
  HINSTANCE hInstance = GetModuleHandle(NULL);
  HICON hIcon = LoadIconW(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
  SetIcon(hIcon, FALSE);

  // create a view to occupy the client area of the frame
  if (!m_child_view.Create(nullptr,
                           nullptr,
                           AFX_WS_DEFAULT_VIEW,
                           CRect(0, 0, 0, 0),
                           this,
                           AFX_IDW_PANE_FIRST,
                           nullptr))
  {
    TRACE0("Failed to create view window\n");
    return -1;
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
  if (!CFrameWnd::PreCreateWindow(cs))
    return FALSE;
  // TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs

  cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
  cs.lpszClass = AfxRegisterWndClass(0);
  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
  CFrameWnd::AssertValid();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::Dump(CDumpContext& dc) const
{
  CFrameWnd::Dump(dc);
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
  // forward focus to the view window
  m_child_view.SetFocus();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
  // let the view have first crack at the command
  if (m_child_view.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;

  // otherwise, do default handling
  return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TODO: Create app state handle to handle enter pause and exit state
void CMainFrame::_CreateDialog(std::unique_ptr<CDialogBoxGeneric> ip_dialog_box)
{
  if (mp_dialog)
    mp_dialog->SetFocus();
  else
  {
    mp_dialog = std::move(ip_dialog_box);
    mp_dialog->Create(IDD_DIALOG_GENERIC, this);
    mp_dialog->ShowWindow(SW_SHOW);
    m_child_view.Invalidate();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::_DeactivateDrawingFeature()
{
  if (is_drawing_feature_active)
  {
    mp_active_gui_draw_feature.reset();
    is_drawing_feature_active = false;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnCreateLineMenuClicked()
{
  _DeactivateDrawingFeature();
  auto p_dialog = std::make_unique<CDialogBoxCreateLine>();
  _CreateDialog(std::move(p_dialog));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnCreateRectangleMenuClicked()
{
  _DeactivateDrawingFeature();
  auto p_dialog = std::make_unique<CDialogBoxCreateRectangle>();
  _CreateDialog(std::move(p_dialog));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnCreateCircleMenuClicked()
{
  _DeactivateDrawingFeature();
  auto p_dialog = std::make_unique<CDialogBoxCreateCircle>();
  _CreateDialog(std::move(p_dialog));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnUndoMenuClicked()
{
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  if (!undo_redo_stacks.IsUndoable())
    return;

  auto operation = undo_redo_stacks.GetCurrentOperation().first;
  auto object = undo_redo_stacks.GetCurrentOperation().second;
  operation->UndoOperation(object);
  m_child_view.Invalidate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnRedoMenuClicked()
{
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  if (!undo_redo_stacks.IsRedoable())
    return;

  auto operation = undo_redo_stacks.GetNextOperation().first;
  auto object = undo_redo_stacks.GetNextOperation().second;
  operation->RedoOperation(object);
  m_child_view.Invalidate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnDrawRectangleToggled()
{
  // Do nothing if draw_line is already avtivated
  if (auto p_draw_rect = dynamic_cast<GUIDrawRectangle*>(mp_active_gui_draw_feature.get()); p_draw_rect)
    return;

  is_drawing_feature_active = true;
  mp_active_gui_draw_feature = std::make_shared<GUIDrawRectangle>();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnDrawCircleToggled()
{
  // Do nothing if draw_line is already avtivated
  if (auto p_draw_circle = dynamic_cast<GUIDrawCircle*>(mp_active_gui_draw_feature.get()); p_draw_circle)
    return;

  is_drawing_feature_active = true;
  mp_active_gui_draw_feature = std::make_shared<GUIDrawCircle>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnDrawLineToggled()
{
  // Do nothing if draw_line is already avtivated
  if (auto p_draw_line = dynamic_cast<GUIDrawLine*>(mp_active_gui_draw_feature.get()); p_draw_line)
    return;

  is_drawing_feature_active = true;
  mp_active_gui_draw_feature = std::make_shared<GUIDrawLine>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CMainFrame::OnCommandRedrawEverything(WPARAM wParam, LPARAM IParam)
{
  m_child_view.Invalidate();
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CMainFrame::OnCommandOperationDialogDestroyed(WPARAM wParam, LPARAM IParam)
{
  if (mp_dialog)
    mp_dialog.reset();
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This is handled in ChildView as properties box are created from there
LRESULT CMainFrame::OnCommandPropertiesDialogDestroyed(WPARAM wParam, LPARAM IParam)
{
  m_child_view.SendMessage(WM_PROPERTIES_DIALOG_DESTROYED, wParam, IParam);
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN)
  {
    // Handle the key event here or call your existing OnKeyDown method
    OnKeyDown(pMsg->wParam, LOWORD(pMsg->lParam), HIWORD(pMsg->lParam));
    return TRUE;  // Mark the message as handled
  }

  return CFrameWnd::PreTranslateMessage(pMsg);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
 if (nChar == VK_ESCAPE && is_drawing_feature_active)
   _DeactivateDrawingFeature();
}
