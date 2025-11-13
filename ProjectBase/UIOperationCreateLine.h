#pragma once
#include "CLine.h"

#include <ProjectFramework/Database.h>
#include <ProjectFramework/IUIOperation.h>

class UIOperationCreateLine : public IUIOperation, public std::enable_shared_from_this<UIOperationCreateLine>
{
private:
  struct InputParameters
  {
    std::unique_ptr<_Vector::double2> m_point_from = nullptr;
    std::unique_ptr<_Vector::double2> m_point_to = nullptr;
  };

  InputParameters m_input_parameters;

public:
  virtual bool DoOperation() override;
  virtual void UndoOperation(std::shared_ptr<IObject> ip_object) override;
  virtual void RedoOperation(std::shared_ptr<IObject> ip_object) override;
  void SetParameters(_Vector::double2& i_point_from, _Vector::double2& i_point_to);
};
