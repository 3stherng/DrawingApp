#include "pch.h"
#include "UIOperationCreateLine.h"

#include <ProjectFramework/UndoRedoStacks.h>

void UIOperationCreateLine::SetParameters(_Vector::double2& i_point_from, _Vector::double2& i_point_to)
{
  m_input_parameters.m_point_from = std::make_unique<_Vector::double2>(i_point_from);
  m_input_parameters.m_point_to = std::make_unique<_Vector::double2>(i_point_to);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UIOperationCreateLine::DoOperation()
{
  // Question: should i handle exception like UIOperationCreateCircle?
  const auto p_created_line = std::make_shared<Object::CLine>(*(m_input_parameters.m_point_from),
                                                              *(m_input_parameters.m_point_to));

  if (p_created_line)
  {
    Database& database = Database::GetInstance();
    UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

    database.AppendToObjectVector(p_created_line);
    undo_redo_stacks.AddNewlyCreatedOperationToStack(shared_from_this(), p_created_line);
    p_created_line->IncrementGlobalID();

    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateLine::UndoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  database.RemoveObjectFromObjectVector(ip_object);
  undo_redo_stacks.Undo();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateLine::RedoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  database.AppendToObjectVector(ip_object);
  undo_redo_stacks.Redo();
}
