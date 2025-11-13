#include "pch.h"
#include "CLine.h"

#include <ProjectFramework/Database.h>


namespace Object
{
  size_t CLine::m_global_id = 1;

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CLine::SetPointFrom(const _Vector::double2& i_point_from)
  {
    m_point_from = i_point_from;
    _CalculateLength();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CLine::SetPointTo(const _Vector::double2& i_point_to)
  {
    m_point_to = i_point_to;
    _CalculateLength();
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CLine::IsCursorWithinObject(const _Vector::double2& i_point) const
  {
    /* m = (y2 - y1) / (x2 - x1)
       c = y1 - X1(m)
       perpendicular distance = mx + c - y
       sqrt(m^2 + 1) is for normalization   */
    auto m = (m_point_to[1] - m_point_from[1]) / (m_point_to[0] - m_point_from[0]);
    auto c = m_point_from[1] - m * m_point_from[0];
    auto distance = abs(m * i_point[0] - i_point[1] + c) / sqrt(m * m + 1);

    return distance <= BUFFER;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // TODO: Change to smart pointer and remove CleanUp
  void CLine::Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot)
  {
    using namespace SaveXMLDocumentHandler;

    HRESULT hr = S_OK;
    IXMLDOMElement* p_node_name = nullptr;
    IXMLDOMElement* p_sub_node_id = nullptr;
    IXMLDOMElement* p_sub_node_point_from = nullptr;
    IXMLDOMElement* p_sub_node_point_to = nullptr;
    IXMLDOMElement* p_sub_node_color = nullptr;

    std::wstring point_from = std::to_wstring(m_point_from[0]) + L", " + std::to_wstring(m_point_from[1]);
    std::wstring point_to = std::to_wstring(m_point_to[0]) + L", " + std::to_wstring(m_point_to[1]);
    std::wstring color = std::to_wstring(
      m_color[0]) + L", " + std::to_wstring(m_color[1]) + L", " + std::to_wstring(m_color[2]);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"Line", L"\n\t", pRoot, &p_node_name));

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"id", L"\n\t\t", p_node_name, &p_sub_node_id));
    CHK_HR(CreateAndAddTextNode(pXMLDom, GetObjectID().c_str(), p_sub_node_id));
    SAFE_RELEASE(p_sub_node_id);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"point_from", L"\n\t\t", p_node_name, &p_sub_node_point_from));
    CHK_HR(CreateAndAddTextNode(pXMLDom, point_from.c_str(), p_sub_node_point_from));
    SAFE_RELEASE(p_sub_node_point_from);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"point_to", L"\n\t\t", p_node_name, &p_sub_node_point_to));
    CHK_HR(CreateAndAddTextNode(pXMLDom, point_to.c_str(), p_sub_node_point_to));
    SAFE_RELEASE(p_sub_node_point_to);

    CHK_HR(CreateAndAddElementNode(pXMLDom, L"color", L"\n\t\t", p_node_name, &p_sub_node_color));
    CHK_HR(CreateAndAddTextNode(pXMLDom, color.c_str(), p_sub_node_color));
    SAFE_RELEASE(p_sub_node_color);

    CHK_HR(CreateAndAddTextNode(pXMLDom, L"\n\t", p_node_name));
    SAFE_RELEASE(p_node_name);

  CleanUp:
    SAFE_RELEASE(p_node_name);
    SAFE_RELEASE(p_sub_node_point_from);
    SAFE_RELEASE(p_sub_node_point_to);
    SAFE_RELEASE(p_sub_node_color);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // TODO: Change to smart pointer and remove CleanUp
  void CLine::Load(IXMLDOMNode* pNode)
  {
    using namespace LoadXMLDocumentHandler;

    HRESULT hr = S_OK;
    IXMLDOMNode* p_node_id = nullptr;
    IXMLDOMNode* p_node_point_from = nullptr;
    IXMLDOMNode* p_node_point_to = nullptr;
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

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("point_from"), &p_node_point_from));
    if (p_node_point_from)
    {
      BSTR bstr_point_from;
      CHK_HR(p_node_point_from->get_text(&bstr_point_from));
      auto point_from = ConvertStringToVector(ConvertBSTRToString(bstr_point_from));
      SetPointFrom({ point_from[0], point_from[1] });
      SysFreeString(bstr_point_from);
      SAFE_RELEASE(p_node_point_from);
    }

    CHK_HR(pNode->selectSingleNode(ConvertStringToBSTR("point_to"), &p_node_point_to));
    if (p_node_point_to)
    {
      BSTR bstr_point_to;
      CHK_HR(p_node_point_to->get_text(&bstr_point_to));
      auto point_to = ConvertStringToVector(ConvertBSTRToString(bstr_point_to));
      SetPointTo({ point_to[0], point_to[1] });
      SysFreeString(bstr_point_to);
      SAFE_RELEASE(p_node_point_to);
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
    SAFE_RELEASE(p_node_point_from);
    SAFE_RELEASE(p_node_point_to);
  }
}