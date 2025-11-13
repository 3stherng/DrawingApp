#pragma once

#include <ProjectBase/CCircle.h>
#include <ProjectBase/CLine.h>
#include <ProjectBase/CRectangle.h>

class DrawShapesHelper
{
private:
  static double m_offset_x;
  static double m_offset_y;
  static CDC* mp_device_context;

public:
  void SetDeviceContext(CDC& i_dc) { mp_device_context = &i_dc; }

  CDC* GetDeviceContext() { return mp_device_context; }

  void SetWcsOffset(const double& i_offset_x, const double& i_offset_y)
  {
    m_offset_x = i_offset_x;
    m_offset_y = i_offset_y;
  }

  CPoint ConvertOCStoSCS(const _Vector::double2& i_object_coordinate_system) const
  {
    return CPoint(static_cast<int>(m_offset_x + i_object_coordinate_system[0]),
                  static_cast<int>(m_offset_y - i_object_coordinate_system[1]));
  }

  _Vector::double2 ConvertSCStoOCS(const CPoint& i_screen_coordinate_system) const
  {
    return { static_cast<double>(i_screen_coordinate_system.x) - m_offset_x,
             m_offset_y - static_cast<double>(i_screen_coordinate_system.y) };
  }

  void Draw(const Object::CCircle& circle);
  void Draw(const Object::CLine& line);
  void Draw(const Object::CRectangle& rectangle);
};
