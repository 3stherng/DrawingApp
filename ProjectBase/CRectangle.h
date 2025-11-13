#pragma once

#include <ProjectFramework/IObject.h>

namespace Object
{
  class CRectangle final : public I2DObject
  {
  private:
    static size_t               m_global_id;    // global id based on number of rectangle created
    size_t                      m_id;           // id of the object
    mutable std::vector<size_t> m_border_color;
    std::vector<size_t>         m_color;
    _Vector::double2            m_center_point;
    double                      m_dimension_x;
    double                      m_dimension_y;
    double                      m_surface_area;
    double                      m_perimeter;
    bool m_is_selected;

    void _CalculateSurfaceArea() override { m_surface_area = m_dimension_x * m_dimension_y; }
    void _CalculatePerimeter() override { m_perimeter = 2 * m_dimension_x + 2 * m_dimension_y; }

  public:
    CRectangle()
      : m_center_point({0., 0.})
      , m_dimension_x(0.)
      , m_dimension_y(0.)
      , m_color({ 0, 255, 0 })
      , m_border_color({ 0, 0, 0 })
      , m_is_selected(false)
      , m_id(0)
    {
      _CalculateSurfaceArea();
      _CalculatePerimeter();
    }

    CRectangle(_Vector::double2 i_center_point, double i_dimension_x, double i_dimension_y)
      : m_center_point(i_center_point)
      , m_dimension_x(i_dimension_x)
      , m_dimension_y(i_dimension_y)
      , m_color({ 53, 94, 59 })
      , m_border_color({ 0, 0, 0 })
      , m_is_selected(false)
      , m_id(m_global_id)
    {
      _CalculateSurfaceArea();
      _CalculatePerimeter();
    }

    std::wstring GetName() const override { return L"Rectangle"; }
    std::wstring GetObjectID() const override { return std::to_wstring(m_id); }
    std::vector<size_t>  GetBorderColor() const override { return m_border_color; }
    std::vector<size_t>  GetColor() const override { return m_color; }
    _Vector::double2 GetCenterPoint() const override { return m_center_point; }
    double GetDimensionX() const { return m_dimension_x; }
    double GetDimensionY() const { return m_dimension_y; }
    double GetSurfaceArea() const override { return m_surface_area; }
    double GetPerimeter() const override { return m_perimeter; }

    void IncrementGlobalID() override { ++m_global_id; }
    void ResetGlobalID() override { m_global_id = 1; }
    void SetBorderColor(const std::vector<size_t>& i_border_color) override { m_border_color = i_border_color; }
    void SetColor(const std::vector<size_t>& i_color) override { m_color = i_color; }
    void SetCenterPoint(const _Vector::double2& i_center_point) override;
    void SetDimensionX(const double& i_dimension_x);
    void SetDimensionY(const double& i_dimension_y);

    void Load(IXMLDOMNode* pNode) override;
    void Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot) override;

    bool IsCursorWithinObject(const _Vector::double2& i_point) const override;
    bool IsObjectSelected() const override { return m_is_selected; };
    void SetObjectSelectionTrue() override { m_is_selected = true; }
    void SetObjectSelectionFalse() override { m_is_selected = false; }
  };
}
