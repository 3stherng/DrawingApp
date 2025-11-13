#pragma once

#include "CDialogBoxPropertiesGeneric.h"

class GUIObjectSelection
{
public:
  std::unique_ptr<CDialogBoxPropertiesGeneric> OnLButtonUp(UINT nFlags, CPoint i_cursor_point_scs);
  void OnMouseMove(UINT nFlags, CPoint i_cursor_point_scs);
};