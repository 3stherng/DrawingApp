#pragma once
#include "GUIDrawObjects.h"

#include "DrawShapesHelper.h"

class GUIDrawLine : public GUIDrawObjects
{
private:
  bool m_is_drawing;
  CPoint m_point_from;
  CPoint m_point_to;

  Object::CLine m_temp_line;
  DrawShapesHelper m_draw_shape_helper;

  _Vector::double2 m_point_from_vector;
  _Vector::double2 m_point_to_vector;

  void _UpdateLineParameters();

public:
  GUIDrawLine()
    : m_is_drawing(false)
  {
  }

  virtual bool IsDrawing() override { return m_is_drawing; };
  virtual void OnLButtonDown(UINT nFlags, CPoint i_cursor_point) override;
  virtual void OnLButtonUp(UINT nFlags, CPoint i_cursor_point) override;
  virtual void OnMouseMove(UINT nFlags, CPoint i_cursor_point) override;

  virtual void GeneratePreviewObject() override;
};
