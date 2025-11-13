#pragma once
#include "GUIDrawObjects.h"

#include "DrawShapesHelper.h"

class GUIDrawRectangle : public GUIDrawObjects
{
private:
  bool m_is_drawing;
  
  CPoint m_point_from;
  CPoint m_point_to;
  
  double m_dimension_x;
  double m_dimension_y;
  _Vector::double2 m_center_point;
  
  Object::CRectangle m_temp_rect;
  DrawShapesHelper m_draw_shape_helper;

  void _UpdateParameters();

public:
  GUIDrawRectangle() 
    : m_is_drawing(false)
  {
  }

  virtual bool IsDrawing() override { return m_is_drawing; };
  virtual void OnLButtonDown(UINT nFlags, CPoint i_cursor_point) override;
  virtual void OnLButtonUp(UINT nFlags, CPoint i_cursor_point) override;
  virtual void OnMouseMove(UINT nFlags, CPoint i_cursor_point) override;

  virtual void GeneratePreviewObject() override;
};
