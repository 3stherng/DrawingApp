#include "pch.h"
#include "GUIObjectSelection.h"

#include "CDialogBoxPropertiesCircle.h"
#include "CDialogBoxPropertiesLine.h"
#include "CDialogBoxPropertiesRectangle.h"
#include "DrawShapesHelper.h"
#include "MFCUtilities.h"

#include <ProjectBase/CCircle.h>
#include <ProjectBase/CLine.h>
#include <ProjectBase/CRectangle.h>

#include <ProjectFramework/Database.h>

// Question: Not sure what is the best way to do this?
std::unique_ptr<CDialogBoxPropertiesGeneric> GUIObjectSelection::OnLButtonUp(UINT nFlags, CPoint i_cursor_point_scs)
{
  DrawShapesHelper draw_shape_helper;
  auto& cursor_point_ocs = draw_shape_helper.ConvertSCStoOCS(i_cursor_point_scs);
  auto selected_border_color = MFCUtilities::ConvertRGBToVectorColor(RGB(0, 0, 255));

  Database& database = Database::GetInstance();
  auto object_vector_copy = database.GetObjectVector();

  for (auto it_object = object_vector_copy.rbegin(); it_object != object_vector_copy.rend(); ++it_object)
  {
    if ((*it_object)->IsCursorWithinObject(cursor_point_ocs))
    {
      (*it_object)->SetObjectSelectionTrue();

      if (auto two_d_objects = dynamic_cast<I2DObject*>((*it_object).get()))
      {
        two_d_objects->SetBorderColor(selected_border_color);
        AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
      }

      if (auto rect = dynamic_cast<Object::CRectangle*>((*it_object).get());
        rect && rect->IsObjectSelected())
        return std::make_unique<CDialogBoxPropertiesRectangle>(*it_object);

      else if (auto line = dynamic_cast<Object::CLine*>((*it_object).get());
        line && line->IsObjectSelected())
        return std::make_unique<CDialogBoxPropertiesLine>(*it_object);

      else if (auto circle = dynamic_cast<Object::CCircle*>((*it_object).get());
        circle && circle->IsObjectSelected())
        return std::make_unique<CDialogBoxPropertiesCircle>(*it_object);
    }
  }
  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Question: Not sure what is the best way to do this?
void GUIObjectSelection::OnMouseMove(UINT nFlags, CPoint i_cursor_point_scs)
{
  DrawShapesHelper draw_shape_helper;
  auto cursor_point_ocs = draw_shape_helper.ConvertSCStoOCS(i_cursor_point_scs);

  Database& database = Database::GetInstance();
  auto copy = database.GetObjectVector();

  auto blue_color_vector = MFCUtilities::ConvertRGBToVectorColor(RGB(0, 0, 255));
  auto black_color_vector = MFCUtilities::ConvertRGBToVectorColor(RGB(0, 0, 0));
  auto is_object_picked = false;

  for (auto it_object = copy.rbegin(); it_object != copy.rend(); ++it_object)
  {
    auto object = dynamic_cast<I2DObject*>((*it_object).get());

    if (auto two_d_object = dynamic_cast<I2DObject*>((*it_object).get()))
    {
      if (!is_object_picked && two_d_object->IsCursorWithinObject(cursor_point_ocs))
      {
        is_object_picked = true;
        if (object->GetBorderColor() != blue_color_vector)
          object->SetBorderColor(blue_color_vector);
      }
      else if (object->GetBorderColor() != black_color_vector)
        object->SetBorderColor(black_color_vector);

    }
    AfxGetMainWnd()->SendMessage(WM_REDRAW_EVERYTHING, 0);
  }
}
