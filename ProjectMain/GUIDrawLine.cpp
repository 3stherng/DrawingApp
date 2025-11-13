#include "pch.h"
#include "GUIDrawLine.h"

#include "MFCUtilities.h"

#include <ProjectBase/UIOperationCreateLine.h>

void GUIDrawLine::_UpdateLineParameters()
{
  m_point_from_vector = m_draw_shape_helper.ConvertSCStoOCS(m_point_from);
  m_point_to_vector = m_draw_shape_helper.ConvertSCStoOCS(m_point_to);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawLine::OnLButtonDown(UINT nFlags, CPoint i_cursor_point)
{
  m_point_from = i_cursor_point;
  m_point_to = i_cursor_point;
  m_is_drawing = true;

  _UpdateLineParameters();

  m_temp_line = Object::CLine(m_point_from_vector, m_point_to_vector);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawLine::OnMouseMove(UINT nFlags, CPoint i_cursor_point)
{
  if (m_is_drawing)
  {
    m_point_to = i_cursor_point;

    _UpdateLineParameters();

    m_temp_line = Object::CLine(m_point_from_vector, m_point_to_vector);
    AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GUIDrawLine::OnLButtonUp(UINT nFlags, CPoint i_cursor_point)
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

    _UpdateLineParameters();

    const auto p_operation = std::make_shared<UIOperationCreateLine>();
    p_operation->SetParameters(m_point_from_vector, m_point_to_vector);
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

void GUIDrawLine::GeneratePreviewObject()
{
  m_temp_line.SetColor(MFCUtilities::ConvertRGBToVectorColor(RGB(211, 211, 211)));
  m_draw_shape_helper.Draw(m_temp_line);
  AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
}
