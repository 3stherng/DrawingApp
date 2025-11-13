// todo: Use smart pointers and remove goto
#include "pch.h"
#include "LoadDom.h"

#include "Database.h"

#include <ProjectBase/CCircle.h>
#include <ProjectBase/CLine.h>
#include <ProjectBase/CRectangle.h>

#include <ProjectFramework/Database.h>
#include <ProjectFramework/UndoRedoStacks.h>

namespace LoadXMLDocumentHandler
{
  HRESULT VariantFromString(PCWSTR wszValue, VARIANT& Variant)
  {
    HRESULT hr = S_OK;
    BSTR bstr = SysAllocString(wszValue);
    CHK_ALLOC(bstr);

    V_VT(&Variant) = VT_BSTR;
    V_BSTR(&Variant) = bstr;

  CleanUp:
    return hr;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  HRESULT CreateAndInitDOM(IXMLDOMDocument** ppDoc)
  {
    HRESULT hr = CoCreateInstance(__uuidof(DOMDocument60), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc));
    if (SUCCEEDED(hr))
    {
      // these methods should not fail so don't inspect result
      (*ppDoc)->put_async(VARIANT_FALSE);
      (*ppDoc)->put_validateOnParse(VARIANT_FALSE);
      (*ppDoc)->put_resolveExternals(VARIANT_FALSE);
      (*ppDoc)->put_preserveWhiteSpace(VARIANT_TRUE);
    }
    return hr;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  HRESULT ReportParseError(IXMLDOMDocument* pDoc, char* szDesc)
  {
    HRESULT hr = S_OK;
    HRESULT hrRet = E_FAIL; // Default error code if failed to get from parse error.
    IXMLDOMParseError* pXMLErr = nullptr;
    BSTR bstrReason = nullptr;

    CHK_HR(pDoc->get_parseError(&pXMLErr));
    CHK_HR(pXMLErr->get_errorCode(&hrRet));
    CHK_HR(pXMLErr->get_reason(&bstrReason));
    printf("%s\n%S\n", szDesc, bstrReason);

  CleanUp:
    SAFE_RELEASE(pXMLErr);
    SysFreeString(bstrReason);
    return hrRet;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::string ConvertWCSToMBS(const wchar_t* i_wide_cstring, long i_wide_string_len)
  {
    int len = ::WideCharToMultiByte(CP_ACP, 0, i_wide_cstring, i_wide_string_len, nullptr, 0, nullptr, nullptr);

    std::string o_string(len, '\0');
    len = ::WideCharToMultiByte(CP_ACP, 0 /* no flags */,
      i_wide_cstring, i_wide_string_len /* not necessary NULL-terminated */,
      &o_string[0], len, nullptr, nullptr /* no default char */);

    return o_string;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::string ConvertBSTRToString(BSTR i_binary_string)
  {
    int string_len = ::SysStringLen(i_binary_string);
    return ConvertWCSToMBS(static_cast<wchar_t*>(i_binary_string), string_len);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  BSTR ConvertStringToBSTR(const std::string& i_string)
  {
    int string_len = ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
      i_string.data(), static_cast<int>(i_string.length()), nullptr, 0);

    BSTR o_binary_string = ::SysAllocStringLen(nullptr, string_len);
    ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
      i_string.data(), static_cast<int>(i_string.length()), o_binary_string, string_len);
    return o_binary_string;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::vector<double> ConvertStringToVector(const std::string& i_string)
  {
    std::stringstream ss(i_string);

    std::string token;
    std::vector<double> o_vector = {};
    while (std::getline(ss, token, ','))
    {
      if (ss.peek() == ' ')
        ss.ignore();

      o_vector.push_back(std::stod(token));
    }
    return o_vector;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void LoadXML(std::wstring i_file_path)
  {
    HRESULT hr = S_OK;
    IXMLDOMDocument* pXMLDom = nullptr;
    IXMLDOMNodeList* pNodes = nullptr;
    IXMLDOMNode* pNode = nullptr;

    BSTR bstrQuery_root = nullptr;
    BSTR bstrNodeName = nullptr;
    VARIANT_BOOL varStatus;
    VARIANT varFileName;
    VariantInit(&varFileName);

    Database& database = Database::GetInstance();

    CHK_HR(CreateAndInitDOM(&pXMLDom));

    CHK_HR(VariantFromString(i_file_path.c_str(), varFileName));
    CHK_HR(pXMLDom->load(varFileName, &varStatus));

    bstrQuery_root = SysAllocString(L"//root/*");
    CHK_ALLOC(bstrQuery_root);
    CHK_HR(pXMLDom->selectNodes(bstrQuery_root, &pNodes));
    if (pNodes)
    {
      long length;
      CHK_HR(pNodes->get_length(&length));

      for (long i = 0; i < length; i++)
      {
        CHK_HR(pNodes->get_item(i, &pNode));

        // Determine the object type based on the node name
        CHK_HR(pNode->get_nodeName(&bstrNodeName));
        std::string nodeType = ConvertBSTRToString(bstrNodeName);

        if (nodeType == "Rectangle")
        {
          auto rect = std::make_shared<Object::CRectangle>();
          rect->Load(pNode);
          database.AppendToObjectVector(rect);
        }
        else if (nodeType == "Circle")
        {
          auto circle = std::make_shared<Object::CCircle>();
          circle->Load(pNode);
          database.AppendToObjectVector(circle);

        }
        else if (nodeType == "Line")
        {
          auto line = std::make_shared<Object::CLine>();
          line->Load(pNode);
          database.AppendToObjectVector(line);
        }

        SAFE_RELEASE(pNode);
        SysFreeString(bstrNodeName);
      }
    }

  CleanUp:
    SAFE_RELEASE(pXMLDom);
    SAFE_RELEASE(pNodes);
    SAFE_RELEASE(pNode);
    SysFreeString(bstrQuery_root);
    SysFreeString(bstrNodeName);
    VariantClear(&varFileName);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void LoadXMLFromFile(std::wstring i_file_path)
  {
    HRESULT hr = CoInitialize(nullptr);
    if (SUCCEEDED(hr))
    {
      Database& database = Database::GetInstance();
      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
      database.CleanUp();
      undo_redo_stacks.CleanUp();

      LoadXML(i_file_path);
      CoUninitialize();
    }
  }
}
