#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "../ProjectBase/UIOperationChangeColor.h"
//#include "../ProjectBase/UIOperationCreateCircle.h"
//#include "../ProjectBase/UIOperationCreateRectangle.h"
//
//#include "../ProjectFramework/Database.h"
//#include "../ProjectFramework/UndoRedoStacks.h"
//
//#include "../MathHelpers/_Vector.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//
//namespace TestProjectBase
//{
//  TEST_MODULE_CLEANUP(ModuleCleanup)
//  {
//    UndoRedoStacks& stacks = UndoRedoStacks::GetInstance();
//    Database& database = Database::GetInstance();
//
//    database.CleanUp();
//    stacks.CleanUp();
//  }
//
//  TEST_CLASS(TestDatabase)
//  {
//  private:
//    void _CreateTestObjects()
//    {
//      _Vector::double2 center_point = { 0., 0. };
//      auto dimension = 5.;
//
//      auto p_operation_rectangle = std::make_shared<UIOperationCreateRectangle>();
//      p_operation_rectangle->SetParameters(center_point, dimension, dimension);
//      p_operation_rectangle->DoOperation();
//
//      auto p_operation_circle = std::make_shared<UIOperationCreateCircle>();
//      p_operation_circle->SetParameters(center_point, dimension);
//      p_operation_circle->DoOperation();
//    }
//
//  public:
//    TEST_METHOD(TestUndoRedo)
//    {
//      UndoRedoStacks& stacks = UndoRedoStacks::GetInstance();
//      Database& database = Database::GetInstance();
//
//      Assert::IsFalse(stacks.IsUndoable());
//      Assert::IsFalse(stacks.IsRedoable());
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(0));
//
//      _CreateTestObjects();
//
//      Assert::IsTrue(stacks.IsUndoable());
//      Assert::IsFalse(stacks.IsRedoable());
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(2));
//
//      //Undo twice
//      stacks.GetCurrentOperation().first->UndoOperation(stacks.GetCurrentOperation().second);
//      stacks.GetCurrentOperation().first->UndoOperation(stacks.GetCurrentOperation().second);
//      Assert::IsFalse(stacks.IsUndoable());
//      Assert::IsTrue(stacks.IsRedoable());
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(0));
//
//      //Redo twice
//      stacks.GetNextOperation().first->RedoOperation(stacks.GetNextOperation().second);
//      stacks.GetNextOperation().first->RedoOperation(stacks.GetNextOperation().second);
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(2));
//    }
//
//    TEST_METHOD(CleanUp)
//    {
//      UndoRedoStacks& stacks = UndoRedoStacks::GetInstance();
//      Database& database = Database::GetInstance();
//
//      _CreateTestObjects();
//
//      stacks.CleanUp();
//      database.CleanUp();
//
//      Assert::IsFalse(stacks.IsUndoable());
//      Assert::IsFalse(stacks.IsRedoable());
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(0));
//
//      // After cleanup, object ID should reset to 1
//      for (auto& object : database.GetObjectVector())
//        Assert::AreEqual(object->GetObjectID(), std::to_wstring(1));
//    }
//  };
//}
