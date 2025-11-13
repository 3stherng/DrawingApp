#pragma once

#include <ProjectFramework/IObject.h>

namespace
{
  const constexpr double BUFFER = 5.;
}

namespace Object
{
  class CLine final : public I1DObject
  {
  private:
    static size_t               m_global_id;  // global id based on number of rectangle created
    size_t                      m_id;         // id of the object
    mutable std::vector<size_t> m_color;
    _Vector::double2            m_point_from;
    _Vector::double2            m_point_to;
    double                      m_length;
    bool                        m_is_selected;

    virtual void _CalculateLength() override { m_length = (m_point_from - m_point_to).GetMagnitude(); }

  public:
    CLine() 
      : m_point_from({0., 0.})
      , m_point_to({0., 0.})
      , m_color({ 0, 0, 0 })
      , m_id(0)
    {
      _CalculateLength();
    }

    CLine(_Vector::double2 i_point_from, _Vector::double2 i_point_to)
      : m_point_from(i_point_from)
      , m_point_to(i_point_to)
      , m_color({ 0, 0, 0 })
      , m_id(m_global_id)
    {
      _CalculateLength();
    }

    std::wstring GetName() const override { return L"Line"; }
    std::wstring GetObjectID() const override { return std::to_wstring(m_id); }
    std::vector<size_t> GetColor() const override { return m_color; }
    _Vector::double2 GetPointFrom() const { return m_point_from; }
    _Vector::double2 GetPointTo() const { return m_point_to; }
    double GetLength() const override { return m_length; }

    void IncrementGlobalID() override { ++m_global_id; }
    void ResetGlobalID() override { m_global_id = 1; }
    void SetColor(const std::vector<size_t>& i_color) override { m_color = i_color; }
    void SetPointFrom(const _Vector::double2& i_point_from);
    void SetPointTo(const _Vector::double2& i_point_to);

    void Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot) override;
    void Load(IXMLDOMNode* pNode) override;

    bool IsCursorWithinObject(const _Vector::double2& i_point) const override;
    bool IsObjectSelected() const override { return m_is_selected; }
    void SetObjectSelectionTrue() override { m_is_selected = true; }
    void SetObjectSelectionFalse() override { m_is_selected = false; }
  };
}
