#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "../ProjectBase/UIOperationCreateCircle.h"
//#include "../ProjectFramework/Database.h"
//#include "../ProjectFramework/UndoRedoStacks.h"
//#include "../MathHelpers/_Vector.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//
//namespace TestProjectBase
//{
//  TEST_CLASS(TestUIOperationCreateCircle)
//  {
//  private:
//    UIOperationCreateCircle* _CreateCircle()
//    {
//      Database& database = Database::GetInstance();
//
//      _Vector::double2 center_point = { 0., 0. };
//      double diameter = 10.;
//
//      auto p_operation_create_circle = std::make_shared<UIOperationCreateCircle>();
//      p_operation_create_circle->SetParameters(center_point, diameter);
//      auto is_operation_suceeded = p_operation_create_circle->DoOperation();
//
//      Assert::IsTrue(is_operation_suceeded);
//
//      return p_operation_create_circle.get();
//    }
//
//  public:
//    TEST_METHOD(TestCreateCircle)
//    {
//      _CreateCircle();
//
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      auto object = database.GetObjectVector()[0];
//      auto created_circle = dynamic_cast<Object::CCircle*>(object.get());
//      Assert::IsTrue(created_circle);
//      if (created_circle)
//      {
//        Assert::AreEqual(created_circle->GetObjectID(), std::to_wstring(1));
//        Assert::AreEqual(created_circle->GetCenterPoint()[0], 0.0);
//        Assert::AreEqual(created_circle->GetCenterPoint()[1], 0.0);
//        Assert::AreEqual(created_circle->GetDiameter(), 10.0);
//
//        double tolerance = 1e-6;
//        double expected_surface_area = 78.539816;
//        double expected_perimeter = 31.415927;
//
//        Assert::IsTrue(std::abs(created_circle->GetSurfaceArea() - expected_surface_area) < tolerance);
//        Assert::IsTrue(std::abs(created_circle->GetPerimeter() - expected_perimeter) < tolerance);
//      }
//
//      _CreateCircle();
//      auto object_2 = database.GetObjectVector()[1];
//      auto created_circle_2 = dynamic_cast<Object::CCircle*>(object_2.get());
//      if (created_circle_2)
//        Assert::AreEqual(created_circle_2->GetObjectID(), std::to_wstring(2));
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    TEST_METHOD(TestUndoRedoCreateCircle)
//    {
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      auto p_operation_create_circle = _CreateCircle();
//      Assert::IsFalse(undo_redo_stacks.IsRedoable());
//
//      // Created circle is added to undo stack
//      auto p_object = undo_redo_stacks.GetTopUIObjectInUndoStack();
//      auto p_circle = dynamic_cast<Object::CCircle*>(p_object.get());
//      Assert::IsTrue(p_circle);
//
//      p_operation_create_circle->UndoOperation(p_object);
//
//      // Created circle is deleted and added to redo stack
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(0));
//      p_object = undo_redo_stacks.GetTopUIObjectInRedoStack();
//      p_circle = dynamic_cast<Object::CCircle*>(p_object.get());
//      Assert::IsTrue(p_circle);
//
//      // Created circle is added back to undo stack
//      p_operation_create_circle->RedoOperation(p_object);
//      p_object = undo_redo_stacks.GetTopUIObjectInUndoStack();
//      p_circle = dynamic_cast<Object::CCircle*>(p_object.get());
//      Assert::IsTrue(p_circle);
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    TEST_METHOD(TestInvalidDiameter)
//    {
//      auto center_point = _Vector::double2({ 0., 0. });
//      auto diameter = 0.;
//      auto p_operation_create_circle = std::unique_ptr<UIOperationCreateCircle>();
//
//      Assert::ExpectException<std::invalid_argument>(
//        [&p_operation_create_circle, &center_point, &diameter]
//        {
//          p_operation_create_circle->SetParameters(center_point, diameter);
//        });
//    }
//  };
//}