#pragma once
#include "pch.h"

class GUIDrawObjects
{
public:
  ~GUIDrawObjects() = default;

  virtual bool IsDrawing() = 0;
  
  virtual void OnLButtonDown(UINT nFlags, CPoint i_cursor_point) = 0;
  virtual void OnLButtonUp(UINT nFlags, CPoint i_cursor_point) = 0;
  virtual void OnMouseMove(UINT nFlags, CPoint i_cursor_point) = 0;
  virtual void GeneratePreviewObject() = 0;
};
