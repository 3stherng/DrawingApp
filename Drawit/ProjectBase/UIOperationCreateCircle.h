#pragma once
#include "CCircle.h"

#include <ProjectFramework/Database.h>
#include <ProjectFramework/IUIOperation.h>

class UIOperationCreateCircle : public IUIOperation, public std::enable_shared_from_this<UIOperationCreateCircle>
{
private:
  struct InputParameters
  {
    std::unique_ptr<_Vector::double2> m_center_point = nullptr;
    std::unique_ptr<double> m_diameter = nullptr;
  };

  InputParameters m_input_parameters;

public:
  void SetParameters(_Vector::double2& i_center_point, double& i_diameter);
  virtual bool DoOperation() override;
  virtual void UndoOperation(std::shared_ptr<IObject> ip_object) override;
  virtual void RedoOperation(std::shared_ptr<IObject> ip_object) override;
};
