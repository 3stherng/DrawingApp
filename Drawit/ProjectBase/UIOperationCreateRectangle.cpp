#include "pch.h"
#include "UIOperationCreateRectangle.h"

#include <ProjectFramework/UndoRedoStacks.h>

bool _IsDimensionValid(const double& i_dimension)
{
  return i_dimension > 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateRectangle::SetParameters(_Vector::double2& i_center_point,
                                               double& i_dimension_x,
                                               double& i_dimension_y)
{
  if (!_IsDimensionValid(i_dimension_x) || !_IsDimensionValid(i_dimension_y))
    throw std::invalid_argument("Dimension must be positive number");

  m_input_parameters.m_center_point = std::make_unique<_Vector::double2>(i_center_point);
  m_input_parameters.m_dimension_x = std::make_unique<double>(i_dimension_x);
  m_input_parameters.m_dimension_y = std::make_unique<double>(i_dimension_y);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UIOperationCreateRectangle::DoOperation()
{
  // Question: should i handle exception like UIOperationCreateCircle?
  if (!_IsDimensionValid(*m_input_parameters.m_dimension_x) || !_IsDimensionValid(*m_input_parameters.m_dimension_y))
    throw (std::invalid_argument("Dimension must be larger than zero"));

  const auto p_created_rectangle = std::make_shared<Object::CRectangle>(*(m_input_parameters.m_center_point),
                                                                        *(m_input_parameters.m_dimension_x),
                                                                        *(m_input_parameters.m_dimension_y));

  if (p_created_rectangle)
  {
    Database& database = Database::GetInstance();
    UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

    database.AppendToObjectVector(p_created_rectangle);
    undo_redo_stacks.AddNewlyCreatedOperationToStack(shared_from_this(), p_created_rectangle);
    p_created_rectangle->IncrementGlobalID();

    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateRectangle::UndoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  database.RemoveObjectFromObjectVector(ip_object);
  undo_redo_stacks.Undo();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateRectangle::RedoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  database.AppendToObjectVector(ip_object);
  undo_redo_stacks.Redo();
}
