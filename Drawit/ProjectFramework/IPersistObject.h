#pragma once

#include "SaveDom.h"
#include "LoadDom.h"

class IPersistObject
{
public:
  ~IPersistObject() = default;

  virtual void Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot) = 0;
  virtual void Load(IXMLDOMNode* pNode) = 0;
};
