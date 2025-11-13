#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "../ProjectBase/UIOperationChangeColor.h"
//#include "../ProjectBase/UIOperationCreateCircle.h"
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
//  TEST_CLASS(TestUIOperationChangeColor)
//  {
//  private:
//    void _CreateObject()
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
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(1));
//    }
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    UIOperationChangeColor* _ChangeColor()
//    {
//      std::vector<size_t> changed_color = { 0, 0, 0 };
//
//      Database& database = Database::GetInstance();
//
//      _CreateObject();
//
//      auto object = database.GetObjectVector()[0];
//
//      auto p_operation_change_color = std::make_shared<UIOperationChangeColor>();
//      p_operation_change_color->SetParameters(object, changed_color);
//      auto is_operation_suceeded = p_operation_change_color->DoOperation();
//
//      Assert::IsTrue(is_operation_suceeded);
//
//      return p_operation_change_color.get();
//    }
//
//    void _CompareColors(const std::vector<size_t>& i_color_1, const std::vector<size_t>& i_color_2)
//    {
//      for (auto idx = 0; idx < i_color_1.size(); ++idx)
//        Assert::AreEqual(i_color_1[idx], i_color_2[idx]);
//    }
//
//  public:
//    TEST_METHOD(TestChangeColor)
//    {
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      _ChangeColor();
//
//      std::vector<size_t> changed_color = { 0, 0, 0 };
//      _CompareColors(database.GetObjectVector()[0]->GetColor(), changed_color);
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//
//    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    TEST_METHOD(TestUndoRedoChangeColor)
//    {
//      Database& database = Database::GetInstance();
//      UndoRedoStacks& undo_redo_stacks = UndoRedoStacks::GetInstance();
//
//      std::vector<size_t> changed_color = { 0, 0, 0 };
//      std::vector<size_t> original_color = {0, 0, 255};
//
//      auto p_operation_change_color = _ChangeColor();
//      Assert::IsFalse(undo_redo_stacks.IsRedoable());
//
//      auto p_object = undo_redo_stacks.GetTopUIObjectInUndoStack();
//      _CompareColors(p_object->GetColor(), changed_color);
//
//      p_operation_change_color->UndoOperation(p_object);
//      _CompareColors(database.GetObjectVector()[0]->GetColor(), original_color);
//     
//      p_operation_change_color->RedoOperation(p_object);
//      _CompareColors(database.GetObjectVector()[0]->GetColor(), changed_color);
//
//      database.CleanUp();
//      undo_redo_stacks.CleanUp();
//    }
//  };
//}
