#pragma once

#include <ProjectFramework/IUIOperation.h>

class UIOperationChangeColor final : public IUIOperation, public std::enable_shared_from_this<UIOperationChangeColor>
{
private:
  std::shared_ptr<IObject> mp_object;
  std::unique_ptr<std::vector<size_t>> m_old_color;
  std::unique_ptr<std::vector<size_t>> m_new_color;

public:
  void SetParameters(std::shared_ptr<IObject> ip_object, std::vector<size_t>& i_new_color);
  bool DoOperation() override;
  void UndoOperation(std::shared_ptr<IObject> ip_object) override;
  void RedoOperation(std::shared_ptr<IObject> ip_object) override;
};
