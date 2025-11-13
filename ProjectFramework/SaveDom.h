// todo: Use smart pointers and remove goto
// Questions: any suggestion how can i handle this, changing to smart pointers give error at the moment

// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)

// Macro to verify memory allcation.
#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0)

// Macro that releases a COM object if not NULL.
#define SAFE_RELEASE(p)     do { if ((p)) { (p)->Release(); (p) = nullptr; } } while(0)

namespace SaveXMLDocumentHandler
{ 
  HRESULT VariantFromString(PCWSTR wszValue, VARIANT& Variant); // Helper function to create a VT_BSTR variant from a null terminated string.
  HRESULT CreateAndInitDOM(IXMLDOMDocument** ppDoc);
  HRESULT CreateElement(IXMLDOMDocument* pXMLDom, PCWSTR wszName, IXMLDOMElement** ppElement);
  HRESULT AppendChildToParent(IXMLDOMNode* pChild, IXMLDOMNode* pParent);
  HRESULT CreateAndAddPINode(IXMLDOMDocument* pDom, PCWSTR wszTarget, PCWSTR wszData);
  HRESULT CreateAndAddCommentNode(IXMLDOMDocument* pDom, PCWSTR wszComment);
  HRESULT CreateAndAddAttributeNode(IXMLDOMDocument* pDom, PCWSTR wszName, PCWSTR wszValue, IXMLDOMElement* pParent);
  HRESULT CreateAndAddTextNode(IXMLDOMDocument* pDom, PCWSTR wszText, IXMLDOMNode* pParent);
  HRESULT CreateAndAddCDATANode(IXMLDOMDocument* pDom, PCWSTR wszCDATA, IXMLDOMNode* pParent);
  HRESULT CreateAndAddElementNode(IXMLDOMDocument* pDom, PCWSTR wszName, PCWSTR wszNewline, IXMLDOMNode* pParent, IXMLDOMElement** ppElement);

  void _WriteAndSaveXML(std::wstring i_file_path);
  void SaveXMLToFile(std::wstring i_file_path);
}
