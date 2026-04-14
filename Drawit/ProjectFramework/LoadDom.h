// todo: Use smart pointers and remove goto

/*  
  References:
    - https://learn.microsoft.com/en-us/previous-versions/windows/desktop/ms767609(v=vs.85)
    - https://stackoverflow.com/questions/6284524/bstr-to-stdstring-stdwstring-and-vice-versa
*/

// Questions: any suggestion how can i handle this, changing to smart pointers give error at the moment

// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)

// Macro to verify memory allcation.
#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0)

// Macro that releases a COM object if not NULL.
#define SAFE_RELEASE(p)     do { if ((p)) { (p)->Release(); (p) = nullptr; } } while(0)

namespace LoadXMLDocumentHandler
{
  // Helper function to create a VT_BSTR variant from a null terminated string. 
  HRESULT VariantFromString(PCWSTR wszValue, VARIANT& Variant);

  HRESULT CreateAndInitDOM(IXMLDOMDocument** ppDoc);
  HRESULT ReportParseError(IXMLDOMDocument* pDoc, char* szDesc);

  std::string ConvertWCSToMBS(const wchar_t* pstr, long wslen);
  std::string ConvertBSTRToString(BSTR bstr);
  BSTR ConvertStringToBSTR(const std::string& str);

  std::vector<double> ConvertStringToVector(const std::string& i_string);

  void LoadXML(std::wstring i_file_path);
  void LoadXMLFromFile(std::wstring i_file_path);
}
