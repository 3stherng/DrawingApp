#pragma once

#include "IObject.h"
#include "IUIOperation.h"

#include <utility>

class UndoRedoStacks
{
private:
  std::vector<std::pair<std::shared_ptr<IUIOperation>, std::shared_ptr<IObject>>> m_operation_stack;
  int m_current_operation_idx;

  UndoRedoStacks() : m_operation_stack(), m_current_operation_idx(-1) {};
  ~UndoRedoStacks() = default;

public:
  static UndoRedoStacks& GetInstance()
  {
    static UndoRedoStacks instance;
    return instance;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool IsUndoable() const
  {
    return !m_operation_stack.empty() &&
      m_current_operation_idx >= 0 &&
      m_current_operation_idx <= static_cast<int>(m_operation_stack.size());
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool IsRedoable() const
  {
    return !m_operation_stack.empty() &&
      m_current_operation_idx >= -1 &&
      m_current_operation_idx < static_cast<int>(m_operation_stack.size() - 1);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void AddNewlyCreatedOperationToStack(std::shared_ptr<IUIOperation> ip_operation, std::shared_ptr<IObject> ip_object)
  {
    if (m_operation_stack.size() > 0 && m_current_operation_idx < static_cast<int>(m_operation_stack.size()) - 1)
    {
      if (m_operation_stack.size() == 1)
        m_operation_stack.clear();
      else
        m_operation_stack.erase(m_operation_stack.begin() + (m_current_operation_idx + 1), m_operation_stack.end());
    }
    m_operation_stack.push_back(std::make_pair(ip_operation, ip_object));
    ++m_current_operation_idx;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool Undo()
  {
    // Question: does it make sense that no exception handling is needed as we never get message from "over-undo"
    if (!IsUndoable())
      return false;

    --m_current_operation_idx;
    return true;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool Redo()
  {
    if (!IsRedoable())
      return false;

    ++m_current_operation_idx;
    return true;
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::pair<std::shared_ptr<IUIOperation>, std::shared_ptr<IObject>> GetCurrentOperation() const
  {
    return !m_operation_stack.empty() ? m_operation_stack[m_current_operation_idx] : std::make_pair(nullptr, nullptr);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::pair<std::shared_ptr<IUIOperation>, std::shared_ptr<IObject>> GetNextOperation() const
  {
    return !m_operation_stack.empty() ? m_operation_stack[m_current_operation_idx + 1] : std::make_pair(nullptr, nullptr);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CleanUp()
  {
    m_operation_stack.clear();
    m_current_operation_idx = -1;
  }
};
