#pragma once

#include <ProjectFramework/IObject.h>

namespace
{
  const constexpr double M_PI = 3.14159265358979323846;
}

namespace Object
{
  class CCircle final : public I2DObject
  {
  private:
    static size_t               m_global_id;  // global id based on number of rectangle created
    size_t                      m_id;         // id of the object
    mutable std::vector<size_t> m_border_color;
    std::vector<size_t>         m_color;
    _Vector::double2            m_center_point;
    double                      m_diameter;
    double                      m_surface_area;
    double                      m_perimeter;
    bool                        m_is_selected;

    void _CalculateSurfaceArea() override { m_surface_area = M_PI * std::pow(m_diameter / 2, 2); };
    void _CalculatePerimeter() override { m_perimeter = M_PI * m_diameter; };

  public:
    CCircle()
      : m_center_point({0., 0.})
      , m_diameter(0.)
      , m_border_color({ 0, 0, 0 })
      , m_color({ 0, 0, 255 })
      , m_is_selected(false)
      , m_id(0)
    {
      _CalculateSurfaceArea();
      _CalculatePerimeter();
    }

    CCircle(_Vector::double2 i_center_point, double i_diameter)
      : m_center_point(i_center_point)
      , m_diameter(i_diameter)
      , m_color({ 115, 147, 179 })
      , m_border_color({ 0, 0, 0 })
      , m_is_selected(false)
      , m_id(m_global_id)
    {
      _CalculateSurfaceArea();
      _CalculatePerimeter();
    }

    ~CCircle() = default;

    std::wstring GetName() const override { return L"Circle"; }
    std::wstring GetObjectID() const override { return std::to_wstring(m_id); }
    _Vector::double2 GetCenterPoint() const override { return m_center_point; }
    double GetDiameter() const { return m_diameter; }
    double GetSurfaceArea() const override { return m_surface_area; }
    double GetPerimeter() const override { return m_perimeter; }
    std::vector<size_t> GetBorderColor() const override { return m_border_color; }
    std::vector<size_t> GetColor() const override { return m_color; }

    void IncrementGlobalID() override { ++m_global_id; }
    void ResetGlobalID() override { m_global_id = 1; }
    void SetCenterPoint(const _Vector::double2& i_center_point) override;
    void SetDiameter(const double& i_diameter);
    void SetBorderColor(const std::vector<size_t>& i_border_color) override { m_border_color = i_border_color; }
    void SetColor(const std::vector<size_t>& i_color) override { m_color = i_color; }

    void Load(IXMLDOMNode* pNode) override;
    void Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot) override;

    bool IsCursorWithinObject(const _Vector::double2& i_point) const override;
    bool IsObjectSelected() const override { return m_is_selected; }
    void SetObjectSelectionTrue() override { m_is_selected = true; }
    void SetObjectSelectionFalse() override { m_is_selected = false; }
  };
}
