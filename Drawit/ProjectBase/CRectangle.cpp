#include "pch.h"
#include "CRectangle.h"

#include <ProjectFramework/Database.h>

namespace Object
{
  size_t CRectangle::m_global_id = 1;

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CRectangle::SetCenterPoint(const _Vector::double2& i_center_point)
  {
    m_center_point = i_center_point;
    _CalculateSurfaceArea();
    _CalculatePerimeter();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CRectangle::SetDimensionX(const double& i_dimension_x)
  {
    m_dimension_x = i_dimension_x;
    _CalculateSurfaceArea();
    _CalculatePerimeter();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CRectangle::SetDimensionY(const double& i_dimension_y)
  {
    m_dimension_y = i_dimension_y;
    _CalculateSurfaceArea();
    _CalculatePerimeter();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CRectangle::IsCursorWithinObject(const _Vector::double2& i_point) const
  {
    return (
      (i_point[0] >= (m_center_point[0] - m_dimension_x / 2)) &&
      (i_point[0] <= (m_center_point[0] + m_dimension_x / 2)) &&
      (i_point[1] >= (m_center_point[1] - m_dimension_y / 2)) &&
      (i_point[1] <= (m_center_point[1] + m_dimension_y / 2)));
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // todo: Change to smart pointer and remove CleanUp
  void CRectangle::Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot)
  {
    using namespace SaveXMLDocumentHandler;

    HRESULT hr = S_OK;
    IXMLDOMElement* p_node_name = nullptr;
    IXMLDOMElement* p_sub_node_id = nullptr;
    IXMLDOMElement* p_sub_node_center_point = nullptr;
    IXMLDOMElement* p_sub_node_dimension_x = nullptr;
    IXMLDOMElement* p_sub_node_dimension_y = nullptr;
    IXMLDOMElement* p_sub_node_color = nullptr;

    std::wstring center_point = std::to_wstring(m_center_point[0]) + L", " + std::to_wstring(m_center_point[1]);
    std::wstring color = std::to_wstring(m_color[0]) + L", " + std::to_wstring(m_color[1]) + L", " + std::to_wstring(m_color[2]);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"Rectangle", L"\n\t", pRoot, &p_node_name));

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"id", L"\n\t\t", p_node_name, &p_sub_node_id));
    CHK_HR(CreateAndAddTextNode(pXMLDom, GetObjectID().c_str(), p_sub_node_id));
    SAFE_RELEASE(p_sub_node_id);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"center_point", L"\n\t\t", p_node_name, &p_sub_node_center_point));
    CHK_HR(CreateAndAddTextNode(pXMLDom, center_point.c_str(), p_sub_node_center_point));
    SAFE_RELEASE(p_sub_node_center_point);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"dimension_x", L"\n\t\t", p_node_name, &p_sub_node_dimension_x));
    CHK_HR(CreateAndAddTextNode(pXMLDom, std::to_wstring(m_dimension_x).c_str(), p_sub_node_dimension_x));
    SAFE_RELEASE(p_sub_node_dimension_x);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"dimension_y", L"\n\t\t", p_node_name, &p_sub_node_dimension_y));
    CHK_HR(CreateAndAddTextNode(pXMLDom, std::to_wstring(m_dimension_y).c_str(), p_sub_node_dimension_y));
    SAFE_RELEASE(p_sub_node_dimension_y);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"color", L"\n\t\t", p_node_name, &p_sub_node_color));
    CHK_HR(CreateAndAddTextNode(pXMLDom, color.c_str(), p_sub_node_color));
    SAFE_RELEASE(p_sub_node_color);

    CHK_HR(CreateAndAddTextNode(pXMLDom, L"\n\t", p_node_name));
    SAFE_RELEASE(p_node_name);

  CleanUp:
    SAFE_RELEASE(p_node_name);
    SAFE_RELEASE(p_sub_node_center_point);
    SAFE_RELEASE(p_sub_node_dimension_x);
    SAFE_RELEASE(p_sub_node_dimension_y);
    SAFE_RELEASE(p_sub_node_color);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // todo: Change to smart pointer and remove CleanUp
  void CRectangle::Load(IXMLDOMNode* pNode)
  {
    using namespace LoadXMLDocumentHandler;

    HRESULT hr = S_OK;

    IXMLDOMNode* p_node_id = nullptr;
    IXMLDOMNode* p_center_point_node = nullptr;
    IXMLDOMNode* p_node_dimension_x = nullptr;
    IXMLDOMNode* p_node_dimension_y = nullptr;
    IXMLDOMNode* p_node_color = nullptr;
    Database& database = Database::GetInstance();

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
      auto vector_center_point = ConvertStringToVector(ConvertBSTRToString(bstr_center_point));
      SetCenterPoint({ vector_center_point[0], vector_center_point[1] });
      SysFreeString(bstr_center_point);
      SAFE_RELEASE(p_center_point_node);
    }

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("dimension_x"), &p_node_dimension_x));
    if (p_node_dimension_x)
    {
      BSTR bstr_dimension_x;
      CHK_HR(p_node_dimension_x->get_text(&bstr_dimension_x));
      SetDimensionX(stod(ConvertBSTRToString(bstr_dimension_x)));
      SysFreeString(bstr_dimension_x);
      SAFE_RELEASE(p_node_dimension_x);
    }

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("dimension_y"), &p_node_dimension_y));
    if (p_node_dimension_y)
    {
      BSTR bstr_dimension_y;
      CHK_HR(p_node_dimension_y->get_text(&bstr_dimension_y));
      SetDimensionY(stod(ConvertBSTRToString(bstr_dimension_y)));
      SysFreeString(bstr_dimension_y);
      SAFE_RELEASE(p_node_dimension_y);
    }

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("color"), &p_node_color));
    if (p_node_color)
    {
      BSTR bstr_color;
      CHK_HR(p_node_color->get_text(&bstr_color));
      auto v = ConvertStringToVector(ConvertBSTRToString(bstr_color));
      SetColor({ static_cast<size_t>(v[0]), static_cast<size_t>(v[1]), static_cast<size_t>(v[2]) });
      SysFreeString(bstr_color);
      SAFE_RELEASE(p_node_color);
    }

  CleanUp:
    SAFE_RELEASE(p_center_point_node);
    SAFE_RELEASE(p_node_dimension_x);
    SAFE_RELEASE(p_node_dimension_y);
  }
}
