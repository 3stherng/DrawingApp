#pragma once

#include "IObject.h"

class IUIOperation
{
public:
  virtual ~IUIOperation() = default;

  virtual bool DoOperation() = 0;
  virtual void UndoOperation(std::shared_ptr<IObject> ip_object) = 0;
  virtual void RedoOperation(std::shared_ptr<IObject> ip_object) = 0;
};
 