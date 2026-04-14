#include "pch.h"
#include "UIOperationCreateCircle.h"

#include <ProjectFramework/UndoRedoStacks.h>

bool _IsDiameterValid(const double& i_diameter)
{
  return i_diameter > 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateCircle::SetParameters(_Vector::double2& i_center_point, double& i_diameter)
{
  m_input_parameters.m_center_point = std::make_unique<_Vector::double2>(i_center_point);
  m_input_parameters.m_diameter = std::make_unique<double>(i_diameter);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UIOperationCreateCircle::DoOperation()
{
  // Question: is this redundent, since this should not happen, "app state" will have default parameters
  if (!m_input_parameters.m_center_point || !m_input_parameters.m_diameter)
    throw (std::invalid_argument("Missing parameter"));

  if (!_IsDiameterValid(*m_input_parameters.m_diameter))
    throw (std::invalid_argument("Diameter must be larger than zero"));

  const auto p_created_circle = std::make_shared<Object::CCircle>(*(m_input_parameters.m_center_point),
                                                                  *(m_input_parameters.m_diameter));

  try
  {
    if (!p_created_circle)
      throw (std::invalid_argument("Circle cannot be created"));

    Database& database = Database::GetInstance();
    UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

    database.AppendToObjectVector(p_created_circle);
    undo_redo_stacks.AddNewlyCreatedOperationToStack(shared_from_this(), p_created_circle);
    p_created_circle->IncrementGlobalID();
  }
  // Question: does it make sense to handle any situation that went wrong?
  catch (...)
  {
    throw (std::invalid_argument("Circle cannot be created"));
    return false;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateCircle::UndoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  database.RemoveObjectFromObjectVector(ip_object);
  undo_redo_stacks.Undo();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UIOperationCreateCircle::RedoOperation(std::shared_ptr<IObject> ip_object)
{
  Database& database = Database::GetInstance();
  UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();

  database.AppendToObjectVector(ip_object);
  undo_redo_stacks.Redo();
}
