#include "pch.h"
#include "DrawShapesHelper.h"

#include "MFCUtilities.h"


double DrawShapesHelper::m_offset_x = 0.;

double DrawShapesHelper::m_offset_y = 0.;

CDC* DrawShapesHelper::mp_device_context = nullptr;

void DrawShapesHelper::Draw(const Object::CLine& i_line)
{
  const auto color_rgb = MFCUtilities::ConvertVectorColorToRGB(i_line.GetColor());
  CPen pen(PS_ALL, 5, color_rgb);

  const auto point_from_scs = ConvertOCStoSCS(i_line.GetPointFrom());
  const auto point_to_scs = ConvertOCStoSCS(i_line.GetPointTo());

  mp_device_context->SelectObject(&pen);
  mp_device_context->MoveTo(point_from_scs.x, point_from_scs.y);
  mp_device_context->LineTo(point_to_scs.x, point_to_scs.y);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawShapesHelper::Draw(const Object::CRectangle& i_rectangle)
{
  const auto color_rgb = MFCUtilities::ConvertVectorColorToRGB(i_rectangle.GetColor());
  const auto border_color_rgb = MFCUtilities::ConvertVectorColorToRGB(i_rectangle.GetBorderColor());

  CBrush brush(color_rgb);
  CPen border_pen(PS_ALL, 5, border_color_rgb);

  mp_device_context->SelectObject(&border_pen);
  mp_device_context->SelectObject(&brush);

  const auto center_point_scs = ConvertOCStoSCS(i_rectangle.GetCenterPoint());

  mp_device_context->Rectangle(
    center_point_scs.x - static_cast<int>(i_rectangle.GetDimensionX() / 2),
    center_point_scs.y - static_cast<int>(i_rectangle.GetDimensionY() / 2),
    center_point_scs.x + static_cast<int>(i_rectangle.GetDimensionX() / 2),
    center_point_scs.y + static_cast<int>(i_rectangle.GetDimensionY() / 2));

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawShapesHelper::Draw(const Object::CCircle& i_circle)
{
  const auto color_rgb = MFCUtilities::ConvertVectorColorToRGB(i_circle.GetColor());
  const auto border_color_rgb = MFCUtilities::ConvertVectorColorToRGB(i_circle.GetBorderColor());

  CBrush brush(color_rgb);
  CPen border_pen(PS_ALL, 3, border_color_rgb);
  mp_device_context->SelectObject(&border_pen);
  mp_device_context->SelectObject(&brush);

  const auto center_point_scs = ConvertOCStoSCS(i_circle.GetCenterPoint());

  mp_device_context->Ellipse(
    center_point_scs.x - static_cast<int>(i_circle.GetDiameter() / 2),
    center_point_scs.y - static_cast<int>(i_circle.GetDiameter() / 2),
    center_point_scs.x + static_cast<int>(i_circle.GetDiameter() / 2),
    center_point_scs.y + static_cast<int>(i_circle.GetDiameter() / 2));
}
