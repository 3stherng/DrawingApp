#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "../ProjectBase/UIOperationCreateRectangle.h"
//#include "../ProjectFramework/Database.h"
//#include "../ProjectFramework/UndoRedoStacks.h"
//#include "../MathHelpers/_Vector.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//
//namespace TestProjectBase
//{
//  TEST_CLASS(TestUIOperationCreateRectangle)
//  {
//  private:
//    UIOperationCreateRectangle* _CreateRectangle()
//    {
//      Database& database = Database::GetInstance();
//
//      _Vector::double2 center_point = { 0., 0. };
//      double dimension_x = 10.;
//      double dimension_y = 20.;
//      auto p_operation_create_reactangle = std::make_shared<UIOperationCreateRectangle>();
//      p_operation_create_reactangle->SetParameters(center_point, dimension_x, dimension_y);
//      auto is_operation_suceeded = p_operation_create_reactangle->DoOperation();
//
//      Assert::IsTrue(is_operation_suceeded);
//
//      return p_operation_create_reactangle.get();
//    }
//
//  public:
//    TEST_METHOD(TestCreateRectangle)
//    {
//      _CreateRectangle();
//
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      auto object = database.GetObjectVector()[0];
//      auto created_rectangle = dynamic_cast<Object::CRectangle*>(object.get());
//      Assert::IsTrue(created_rectangle);
//
//      if (created_rectangle)
//      {
//        Assert::AreEqual(created_rectangle->GetObjectID(), std::to_wstring(1));
//        Assert::AreEqual(created_rectangle->GetCenterPoint()[0], 0.0);
//        Assert::AreEqual(created_rectangle->GetCenterPoint()[1], 0.0);
//        Assert::AreEqual(created_rectangle->GetDimensionX(), 10.0);
//        Assert::AreEqual(created_rectangle->GetDimensionY(), 20.0);
//
//        double tolerance = 1e-6;
//        double expected_surface_area = 200.000000;
//        double expected_perimeter = 60.000000;
//
//        Assert::IsTrue(std::abs(created_rectangle->GetSurfaceArea() - expected_surface_area) < tolerance);
//        Assert::IsTrue(std::abs(created_rectangle->GetPerimeter() - expected_perimeter) < tolerance);
//      }
//
//      _CreateRectangle();
//      auto object_2 = database.GetObjectVector()[1];
//      auto created_rectangle_2 = dynamic_cast<Object::CRectangle*>(object_2.get());
//      if (created_rectangle_2)
//        Assert::AreEqual(created_rectangle_2->GetObjectID(), std::to_wstring(2));
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    TEST_METHOD(TestUndoRedoCreateRectangle)
//    {
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      auto p_operation_create_rectangle = _CreateRectangle();
//      Assert::IsFalse(undo_redo_stacks.IsRedoable());
//
//       Created rectangle is added to undo stack
//      auto p_object = undo_redo_stacks.GetCurrentOperation();
//      auto p_rectangle = dynamic_cast<Object::CRectangle*>(p_object.second.get());
//      Assert::IsTrue(p_rectangle);
//
//      p_operation_create_rectangle->UndoOperation(p_object.second);
//
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(0));
//      p_object = undo_redo_stacks.GetCurrentOperation();
//      p_rectangle = dynamic_cast<Object::CRectangle*>(p_object.second.get());
//      Assert::IsTrue(p_rectangle);
//
//       Created rectangle is added back to undo stack
//      p_operation_create_rectangle->RedoOperation(p_object);
//      p_object = undo_redo_stacks.GetTopUIObjectInUndoStack();
//      p_rectangle = dynamic_cast<Object::CRectangle*>(p_object.get());
//      Assert::IsTrue(p_rectangle);
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//
//    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    TEST_METHOD(TestBothInvalidDimension)
//    {
//      auto center_point = _Vector::double2({ 0., 0. });
//      auto dimension_x = 0.;
//      auto dimension_y = -10.;
//      auto p_operation_create_reactangle = std::unique_ptr<UIOperationCreateRectangle>();
//
//      Assert::ExpectException<std::invalid_argument>(
//        [&p_operation_create_reactangle, &center_point, &dimension_x, &dimension_y]
//        {
//          p_operation_create_reactangle->SetParameters(center_point, dimension_x, dimension_y);
//        });
//    }
//
//    TEST_METHOD(TestInvalidDimensionX)
//    {
//      auto center_point = _Vector::double2({ 0., 0. });
//      auto dimension_x = -5.;
//      auto dimension_y = 2.;
//      auto p_operation_create_reactangle = std::unique_ptr<UIOperationCreateRectangle>();
//
//      Assert::ExpectException<std::invalid_argument>(
//        [&p_operation_create_reactangle, &center_point, &dimension_x, &dimension_y]
//        {
//          p_operation_create_reactangle->SetParameters(center_point, dimension_x, dimension_y);
//        });
//    }
//
//    TEST_METHOD(TestInvalidDimensionY)
//    {
//      auto center_point = _Vector::double2({ 0., 0. });
//      auto dimension_x = 5.;
//      auto dimension_y = 0.;
//      auto p_operation_create_reactangle = std::unique_ptr<UIOperationCreateRectangle>();
//
//      Assert::ExpectException<std::invalid_argument>(
//        [&p_operation_create_reactangle, &center_point, &dimension_x, &dimension_y]
//        {
//          p_operation_create_reactangle->SetParameters(center_point, dimension_x, dimension_y);
//        });
//    }
//  };
//}
