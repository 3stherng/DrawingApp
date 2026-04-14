#include "pch.h"
#include "GUIDrawCircle.h"

#include "MFCUtilities.h"

#include <ProjectBase/UIOperationCreateCircle.h>

void GUIDrawCircle::_UpdateCircleParameters()
{
  auto point_from = m_draw_shape_helper.ConvertSCStoOCS(m_point_from);
  auto point_to = m_draw_shape_helper.ConvertSCStoOCS(m_point_to);

  m_diameter = std::abs(point_from[0] - point_to[0]);
  m_center_point[0] = (point_to[0] + point_from[0]) / 2;
  m_center_point[1] = (point_to[1] + point_from[1]) / 2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawCircle::OnLButtonDown(UINT nFlags, CPoint i_cursor_point)
{
  m_point_from = i_cursor_point;
  m_point_to = i_cursor_point;
  m_is_drawing = true;

  _UpdateCircleParameters();

  m_temp_circle = Object::CCircle(m_center_point, m_diameter);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawCircle::OnMouseMove(UINT nFlags, CPoint i_cursor_point)
{
  if (m_is_drawing)
  {
    m_point_to = i_cursor_point;

    _UpdateCircleParameters();

    m_temp_circle = Object::CCircle(m_center_point, m_diameter);

    AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawCircle::OnLButtonUp(UINT nFlags, CPoint i_cursor_point)
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

    _UpdateCircleParameters();

    m_temp_circle = Object::CCircle(m_center_point, m_diameter);

    const auto p_operation = std::make_shared<UIOperationCreateCircle>();
    p_operation->SetParameters(m_center_point, m_diameter);
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

void GUIDrawCircle::GeneratePreviewObject()
{
  m_temp_circle.SetColor(MFCUtilities::ConvertRGBToVectorColor(RGB(211, 211, 211)));
  m_draw_shape_helper.Draw(m_temp_circle);
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}