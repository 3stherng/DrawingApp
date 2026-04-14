#include "pch.h"
#include "UIOperationChangeColor.h"

#include <ProjectFramework/Database.h>
#include <ProjectFramework/UndoRedoStacks.h>

void UIOperationChangeColor::SetParameters(std::shared_ptr<IObject> ip_object, std::vector<size_t>& i_new_color)
{
  mp_object = ip_object;
  m_old_color = std::make_unique<std::vector<size_t>>(mp_object->GetColor());
  m_new_color = std::make_unique<std::vector<size_t>>(i_new_color);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UIOperationChangeColor::DoOperation()
{
  // Question: should i handle exception like UIOperationCreateCircle?
  if (!mp_object)
    throw (std::invalid_argument("object is not provided"));

  mp_object->SetColor(*m_new_color);

  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  undo_redo_stacks.AddNewlyCreatedOperationToStack(shared_from_this(), mp_object);

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationChangeColor::UndoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  mp_object->SetColor(*m_old_color);
  undo_redo_stacks.Undo();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationChangeColor::RedoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  mp_object->SetColor(*m_new_color);
  undo_redo_stacks.Redo();
}
