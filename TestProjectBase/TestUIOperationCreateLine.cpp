#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "../ProjectBase/UIOperationCreateLine.h"
//#include "../ProjectFramework/Database.h"
//#include "../ProjectFramework/UndoRedoStacks.h"
//#include "../MathHelpers/_Vector.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//
//namespace TestProjectBase
//{
//  TEST_CLASS(TestUIOperationCreateLine)
//  {
//  private:
//    UIOperationCreateLine* _CreateLine()
//    {
//      Database& database = Database::GetInstance();
//
//      _Vector::double2 point1 = { 0., -1.1111 };
//      _Vector::double2 point2 = { 10., 0. };
//      double diameter = 10.;
//      auto p_operation_create_line = std::make_shared<UIOperationCreateLine>();
//      p_operation_create_line->SetParameters(point1, point2);
//      auto is_operation_suceeded = p_operation_create_line->DoOperation();
//
//      Assert::IsTrue(is_operation_suceeded);
//
//      return p_operation_create_line.get();
//    }
//
//  public:
//    TEST_METHOD(TestCreateLine)
//    {
//      _CreateLine();
//
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      auto object = database.GetObjectVector()[0];
//      auto created_line = dynamic_cast<Object::CLine*>(object.get());
//      Assert::IsTrue(created_line);
//
//      if (created_line)
//      {
//        Assert::AreEqual(created_line->GetObjectID(), std::to_wstring(1));
//        Assert::AreEqual(created_line->GetPointFrom()[0], 0.0);
//        Assert::AreEqual(created_line->GetPointFrom()[1], -1.1111);
//        Assert::AreEqual(created_line->GetPointTo()[0], 10.0);
//        Assert::AreEqual(created_line->GetPointTo()[1], 0.0);
//
//        double tolerance = 1e-6;
//        double expected_length = 10.061538;
//
//        Assert::IsTrue(std::abs(created_line->GetLength() - expected_length) < tolerance);
//      }
//
//      _CreateLine();
//      auto object_2 = database.GetObjectVector()[1];
//      auto created_line_2 = dynamic_cast<Object::CLine*>(object_2.get());
//      if (created_line_2)
//        Assert::AreEqual(created_line_2->GetObjectID(), std::to_wstring(2));
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    TEST_METHOD(TestUndoRedoCreateLine)
//    {
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      auto p_operation_create_line = _CreateLine();
//      Assert::IsFalse(undo_redo_stacks.IsRedoable());
//
//      // Created line is added to undo stack
//      auto p_object = undo_redo_stacks.GetTopUIObjectInUndoStack();
//      auto p_line = dynamic_cast<Object::CLine*>(p_object.get());
//      Assert::IsTrue(p_line);
//
//      p_operation_create_line->UndoOperation(p_object);
//
//      // Created line is deleted and added to redo stack
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(0));
//      p_object = undo_redo_stacks.GetTopUIObjectInRedoStack();
//      p_line = dynamic_cast<Object::CLine*>(p_object.get());
//      Assert::IsTrue(p_line);
//
//      // Created line is added back to undo stack
//      p_operation_create_line->RedoOperation(p_object);
//      p_object = undo_redo_stacks.GetTopUIObjectInUndoStack();
//      p_line = dynamic_cast<Object::CLine*>(p_object.get());
//      Assert::IsTrue(p_line);
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//  };
//}
