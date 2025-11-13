#pragma once

#include "IPersistObject.h"

#include <MathHelpers/_Vector.h>

class IObject :public IPersistObject
{
public:
  virtual ~IObject() = default;

  virtual std::vector<size_t> GetColor() const = 0;
  virtual std::wstring GetName() const = 0;
  virtual std::wstring GetObjectID() const = 0;

  virtual void IncrementGlobalID() = 0;
  virtual void ResetGlobalID() = 0;
  virtual void SetColor(const std::vector<size_t>& i_color) = 0;

  virtual bool IsCursorWithinObject(const _Vector::double2& i_point) const = 0 ;
  virtual bool IsObjectSelected() const = 0;
  virtual void SetObjectSelectionTrue() = 0;
  virtual void SetObjectSelectionFalse() = 0;

  virtual void Load(IXMLDOMNode* pNode) override = 0;
  virtual void Save(IXMLDOMDocument* pXMLDom, IXMLDOMElement* pRoot) override = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class I1DObject : public IObject
{
protected:
  virtual void _CalculateLength() = 0;

public:
  virtual ~I1DObject() = default;

  virtual double GetLength() const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class I2DObject : public IObject
{
protected:
  virtual void _CalculateSurfaceArea() = 0;
  virtual void _CalculatePerimeter() = 0;

public:
  virtual ~I2DObject() = default;

  virtual _Vector::double2 GetCenterPoint() const = 0;
  virtual double GetSurfaceArea() const = 0;
  virtual double GetPerimeter() const = 0;
  virtual std::vector<size_t> GetBorderColor() const = 0;

  virtual void SetCenterPoint(const _Vector::double2& i_center_point) = 0;
  virtual void SetBorderColor(const std::vector<size_t>& i_color) = 0;
};
