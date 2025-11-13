#include "pch.h"
#include "ProjectChildView.h"

#include "GUIObjectSelection.h"
#include "ProjectMainFrm.h"

#include <ProjectBase/CCircle.h> 
#include <ProjectBase/CLine.h>
#include <ProjectBase/CRectangle.h>

#include <ProjectFramework/Database.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CChildView, CWnd)
  ON_WM_PAINT()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_MESSAGE(WM_PROPERTIES_DIALOG_DESTROYED, OnCommandPropertiesDialogDestroyed)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CChildView::_CreateDialog(std::unique_ptr<CDialogBoxPropertiesGeneric> ip_dialog_box)
{
  if (mp_properties_dialog_box)
    mp_properties_dialog_box->SetFocus();
  else
  {
    mp_properties_dialog_box = std::move(ip_dialog_box);
    mp_properties_dialog_box->Create(IDD_DIALOG_GENERIC, this);
    mp_properties_dialog_box->ShowWindow(SW_SHOW);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CChildView message handlers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
  if (!CWnd::PreCreateWindow(cs))
    return FALSE;

  cs.dwExStyle |= WS_EX_CLIENTEDGE;
  cs.style &= ~WS_BORDER;

  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CChildView::OnPaint()
{
  CRect canvas;
  GetClientRect(&canvas);

  auto offset_x = static_cast<double>(canvas.Width() / 2);
  auto offset_y = static_cast<double>(canvas.Height() / 2);
  m_draw_shape_helper.SetWcsOffset(offset_x, offset_y);

  CDC memory_device_context, * p_device_context;
  CBitmap memory_bitmap;

  p_device_context = this->GetDC();
  memory_device_context.CreateCompatibleDC(p_device_context);
  memory_bitmap.CreateCompatibleBitmap(p_device_context, canvas.right, canvas.bottom);

  // TODO: Use smart pointer
  CBitmap* p_old_bitmap = (CBitmap*)memory_device_context.SelectObject(&memory_bitmap);

  memory_device_context.FillSolidRect(0, 0, canvas.right, canvas.bottom, RGB(255, 255, 255));

  _DrawObjects(memory_device_context);

  p_device_context->BitBlt(0, 0, canvas.right, canvas.bottom, &memory_device_context, 0, 0, SRCCOPY);
  memory_device_context.SelectObject(p_old_bitmap);

  ReleaseDC(p_device_context);
  ReleaseDC(&memory_device_context);

  CWnd::OnPaint(); // Somehow this fixed DoModal() infinite loop
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CChildView::_DrawObjects(CDC& i_device_context)
{
  m_draw_shape_helper.SetDeviceContext(i_device_context);

  Database& database = Database::GetInstance();
  for (auto& p_object : database.GetObjectVector())
  {
    if (auto circle = dynamic_cast<Object::CCircle*>(p_object.get()))
      m_draw_shape_helper.Draw(*circle);

    else if (auto rectangle = dynamic_cast<Object::CRectangle*>(p_object.get()))
      m_draw_shape_helper.Draw(*rectangle);

    else if (auto line = dynamic_cast<Object::CLine*>(p_object.get()))
      m_draw_shape_helper.Draw(*line);
  }

  auto p_main_frame = dynamic_cast<CMainFrame*>(GetParentFrame());
  if (auto active_dialog = dynamic_cast<CDialogBoxGeneric*>(p_main_frame->GetActiveDialog().get()))
    active_dialog->GeneratePreviewObject();

  if (auto active_feature = p_main_frame->GetActiveGuiDrawFeature().get();
    active_feature && active_feature->IsDrawing())
    active_feature->GeneratePreviewObject();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
  auto p_main_frame = dynamic_cast<CMainFrame*>(GetParentFrame());
  if (auto active_feature = p_main_frame->GetActiveGuiDrawFeature().get(); active_feature)
    active_feature->OnLButtonDown(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CChildView::OnMouseMove(UINT nFlags, CPoint i_cursor_point_scs)
{
  auto p_main_frame = dynamic_cast<CMainFrame*>(GetParentFrame());
  if (auto active_feature = p_main_frame->GetActiveGuiDrawFeature().get(); active_feature)
    active_feature->OnMouseMove(nFlags, i_cursor_point_scs);
  else
  {
    // Deactivate mouse move checking if objects are selected
    if (mp_properties_dialog_box)
      return;

    GUIObjectSelection gui_object_selection;
    gui_object_selection.OnMouseMove(nFlags, i_cursor_point_scs);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CChildView::OnLButtonUp(UINT nFlags, CPoint i_cursor_point_scs)
{
  auto p_main_frame = dynamic_cast<CMainFrame*>(GetParentFrame());
  if (auto active_feature = p_main_frame->GetActiveGuiDrawFeature().get(); active_feature)
    active_feature->OnLButtonUp(nFlags, i_cursor_point_scs);
  else
  {
    GUIObjectSelection gui_object_selection;
    if (auto dialog = gui_object_selection.OnLButtonUp(nFlags, i_cursor_point_scs); dialog)
      _CreateDialog(std::move(dialog));
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CChildView::OnCommandPropertiesDialogDestroyed(WPARAM wParam, LPARAM IParam)
{
  if (mp_properties_dialog_box)
    mp_properties_dialog_box.reset();
  return 0;
}
