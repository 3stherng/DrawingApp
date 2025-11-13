#include "pch.h"
#include "GUIDrawRectangle.h"

#include "DrawShapesHelper.h"
#include "MFCUtilities.h"

#include <ProjectBase/UIOperationCreateRectangle.h>

void GUIDrawRectangle::_UpdateParameters()
{
  auto point_from = m_draw_shape_helper.ConvertSCStoOCS(m_point_from);
  auto point_to = m_draw_shape_helper.ConvertSCStoOCS(m_point_to);

  m_dimension_x = std::abs(point_from[0] - point_to[0]);
  m_dimension_y = std::abs(point_from[1] - point_to[1]);
  m_center_point = { (point_to[0] + point_from[0]) / 2 , (point_to[1] + point_from[1]) / 2 };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawRectangle::OnLButtonDown(UINT nFlags, CPoint i_cursor_point)
{
  m_point_from = i_cursor_point;
  m_point_to = i_cursor_point;
  m_is_drawing = true;

  _UpdateParameters();

  m_temp_rect = Object::CRectangle(m_center_point, m_dimension_x, m_dimension_y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawRectangle::OnMouseMove(UINT nFlags, CPoint i_cursor_point)
{
  if (m_is_drawing)
  {
    m_point_to = i_cursor_point;

    _UpdateParameters();

    m_temp_rect = Object::CRectangle(m_center_point, m_dimension_x, m_dimension_y);
    AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawRectangle::OnLButtonUp(UINT nFlags, CPoint i_cursor_point)
{
  if (m_point_from == m_point_to)
  {
    m_is_drawing = false;
    return;
  }

  if (m_is_drawing)
  {
    m_is_drawing = false;
    m_point_to = i_cursor_point;
    _UpdateParameters();

    const auto p_operation = std::make_shared<UIOperationCreateRectangle>();
    p_operation->SetParameters(m_center_point, m_dimension_x, m_dimension_y);
    try
    {
      p_operation->DoOperation();
      AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
    }
    catch (std::exception& ex)
    {
      AfxMessageBox(L"Failed Create Circle");
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawRectangle::GeneratePreviewObject()
{
  m_temp_rect.SetColor(MFCUtilities::ConvertRGBToVectorColor(RGB(211, 211, 211)));
  m_draw_shape_helper.Draw(m_temp_rect);
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}
