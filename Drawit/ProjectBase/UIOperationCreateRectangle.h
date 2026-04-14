#pragma once
#include "CRectangle.h"

#include <ProjectFramework/Database.h>
#include <ProjectFramework/IUIOperation.h>

class UIOperationCreateRectangle : public IUIOperation, public std::enable_shared_from_this<UIOperationCreateRectangle>
{
private:
  struct InputParameters
  {
    std::unique_ptr<_Vector::double2> m_center_point = nullptr;
    std::unique_ptr<double> m_dimension_x = nullptr;
    std::unique_ptr<double> m_dimension_y = nullptr;
  };

  InputParameters m_input_parameters;

public:
  virtual bool DoOperation() override;
  virtual void UndoOperation(std::shared_ptr<IObject> ip_object) override;
  virtual void RedoOperation(std::shared_ptr<IObject> ip_object) override;
  void SetParameters(_Vector::double2& i_center_point, double& i_dimension_x, double& i_dimension_y);
};
