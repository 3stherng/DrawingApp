#include "pch.h"
#include "CCircle.h"

namespace Object
{
  size_t CCircle::m_global_id = 1;

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CCircle::SetCenterPoint(const _Vector::double2& i_center_point)
  {
    m_center_point = i_center_point;
    _CalculateSurfaceArea();
    _CalculatePerimeter();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CCircle::SetDiameter(const double& i_diameter)
  {
    m_diameter = i_diameter;
    _CalculateSurfaceArea();
    _CalculatePerimeter();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CCircle::IsCursorWithinObject(const _Vector::double2& i_point) const
  {
    const auto dx = i_point[0] - m_center_point[0];
    const auto dy = i_point[1] - m_center_point[1];
    
    return dx * dx + dy * dy <= m_diameter * m_diameter / 4;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // todo: Change to smart pointer and remove CleanUp
  void CCircle::Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot)
  {
    using namespace SaveXMLDocumentHandler;

    HRESULT hr = S_OK;
    IXMLDOMElement* p_node_name = nullptr;
    IXMLDOMElement* p_sub_node_id = nullptr;
    IXMLDOMElement* p_sub_node_center_point = nullptr;
    IXMLDOMElement* p_sub_node_diameter = nullptr;
    IXMLDOMElement* p_sub_node_dimension_y = nullptr;
    IXMLDOMElement* p_sub_node_color = nullptr;

    std::wstring center_point = std::to_wstring(m_center_point[0]) + L", " + std::to_wstring(m_center_point[1]);
    std::wstring color = std::to_wstring(
      m_color[0]) + L", " + std::to_wstring(m_color[1]) + L", " + std::to_wstring(m_color[2]);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"Circle", L"\n\t", pRoot, &p_node_name));

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"id", L"\n\t\t", p_node_name, &p_sub_node_id));
    CHK_HR(CreateAndAddTextNode(pXMLDom, GetObjectID().c_str(), p_sub_node_id));
    SAFE_RELEASE(p_sub_node_id);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"center_point", L"\n\t\t", p_node_name, &p_sub_node_center_point));
    CHK_HR(CreateAndAddTextNode(pXMLDom, center_point.c_str(), p_sub_node_center_point));
    SAFE_RELEASE(p_sub_node_center_point);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"diameter", L"\n\t\t", p_node_name, &p_sub_node_diameter));
    CHK_HR(CreateAndAddTextNode(pXMLDom, std::to_wstring(m_diameter).c_str(), p_sub_node_diameter));
    SAFE_RELEASE(p_sub_node_diameter);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"color", L"\n\t\t", p_node_name, &p_sub_node_color));
    CHK_HR(CreateAndAddTextNode(pXMLDom, color.c_str(), p_sub_node_color));
    SAFE_RELEASE(p_sub_node_color);

    CHK_HR(CreateAndAddTextNode(pXMLDom, L"\n\t", p_node_name));
    SAFE_RELEASE(p_node_name);

  CleanUp:
    SAFE_RELEASE(p_node_name);
    SAFE_RELEASE(p_sub_node_center_point);
    SAFE_RELEASE(p_sub_node_diameter);
    SAFE_RELEASE(p_sub_node_color);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // todo: Change to smart pointer and remove CleanUp
  void CCircle::Load(IXMLDOMNode* pNode)
  {
    using namespace LoadXMLDocumentHandler;

    HRESULT hr = S_OK;

    IXMLDOMNode* p_node_id = nullptr;
    IXMLDOMNode* p_center_point_node = nullptr;
    IXMLDOMNode* p_node_diameter = nullptr;
    IXMLDOMNode* p_node_color = nullptr;

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("id"), &p_node_id));
    if (p_node_id)
    {
      BSTR bstr_id;
      CHK_HR(p_node_id->get_text(&bstr_id));
      auto id = stoi(ConvertBSTRToString(bstr_id));
      m_id = static_cast<size_t>(id);
      SysFreeString(bstr_id);
      SAFE_RELEASE(p_node_id);
    }

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("center_point"), &p_center_point_node));
    if (p_center_point_node)
    {
      BSTR bstr_center_point;
      CHK_HR(p_center_point_node->get_text(&bstr_center_point));
      auto center_point = ConvertStringToVector(ConvertBSTRToString(bstr_center_point));
      SetCenterPoint({ center_point[0], center_point[1] });
      SysFreeString(bstr_center_point);
      SAFE_RELEASE(p_center_point_node);
    }

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("diameter"), &p_node_diameter));
    if (p_node_diameter)
    {
      BSTR bstr_point_to;
      CHK_HR(p_node_diameter->get_text(&bstr_point_to));
      SetDiameter(stod(ConvertBSTRToString(bstr_point_to)));
      SysFreeString(bstr_point_to);
      SAFE_RELEASE(p_node_diameter);
    }

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("color"), &p_node_color));
    if (p_node_color)
    {
      BSTR bstr_color;
      CHK_HR(p_node_color->get_text(&bstr_color));
      auto color = ConvertStringToVector(ConvertBSTRToString(bstr_color));
      SetColor({ static_cast<size_t>(color[0]), static_cast<size_t>(color[1]), static_cast<size_t>(color[2]) });
      SysFreeString(bstr_color);
      SAFE_RELEASE(p_node_color);
    }

  CleanUp:
    SAFE_RELEASE(p_center_point_node);
    SAFE_RELEASE(p_node_diameter);
  }
}
