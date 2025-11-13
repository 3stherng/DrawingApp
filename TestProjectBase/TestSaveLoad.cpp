#include "pch.h"
//#include "CppUnitTest.h"
//
//#include "../ProjectBase/UIOperationCreateCircle.h"
//#include "../ProjectBase/UIOperationCreateLine.h"
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
//  TEST_CLASS(TestSaveLoad)
//  {
//  private:
//    void _CreateLineCircleRectangle()
//    {
//      _Vector::double2 point1 = { 0., 0. };
//      _Vector::double2 point2 = { 10., 10. };
//      auto parameter = 5.;
//
//      auto p_operation_circle = std::make_shared<UIOperationCreateCircle>();
//      p_operation_circle->SetParameters(point1, parameter);
//      p_operation_circle->DoOperation();
//
//      auto p_operation_line = std::make_shared<UIOperationCreateLine>();
//      p_operation_line->SetParameters(point1, point2);
//      p_operation_line->DoOperation();
//
//      auto p_operation_rectangle = std::make_shared<UIOperationCreateRectangle>();
//      p_operation_rectangle->SetParameters(point1, parameter, parameter);
//      p_operation_rectangle->DoOperation();
//    }
//
//    void _CompareColors(const std::vector<size_t>& i_color_1, const std::vector<size_t>& i_color_2)
//    {
//      for (auto idx = 0; idx < i_color_1.size(); ++idx)
//        Assert::AreEqual(i_color_1[idx], i_color_2[idx]);
//    }
//
//    void _ComparePoints(const _Vector::double2& i_point_1, const _Vector::double2& i_point_2)
//    {
//      for (auto idx = 0; idx < 2; ++idx)
//        Assert::AreEqual(i_point_1[idx], i_point_2[idx]);
//    }
//
//  public:
//    TEST_METHOD(SaveAndLoad)
//    {
//      UndoRedoStacks& stacks = UndoRedoStacks::GetInstance();
//      Database& database = Database::GetInstance();
//
//      // FILE* temp_dir = tmpfile();
//      // 
//      // if (!temp_dir)
//      // {
//      //   perror("Error creating temporary file");
//      //   exit(true);
//      // }
//      //fclose(fp);
//
//      _CreateLineCircleRectangle();
//
//      std::wstring hard_coded_file_path = L"C:\\Users\\yng\\OneDrive - Materialise NV\\Desktop\\test.blah";
//      SaveXMLDocumentHandler::SaveXMLToFile(hard_coded_file_path);
//      LoadXMLDocumentHandler::LoadXMLFromFile(hard_coded_file_path);
//
//      Assert::AreEqual(database.GetObjectVector().size(), static_cast<size_t>(3));
//      Assert::IsFalse(stacks.IsUndoable());
//      Assert::IsFalse(stacks.IsRedoable());
//
//      auto vector = database.GetObjectVector();
//
//      auto circle = dynamic_cast<Object::CCircle*>(vector[0].get());
//      Assert::IsTrue(circle);
//      if (circle)
//      {
//        _CompareColors(circle->GetColor(), { 0, 0, 255 });
//        _ComparePoints(circle->GetCenterPoint(), { 0.000000, 0.000000 });
//        Assert::AreEqual(circle->GetDiameter(), 5.000000);
//      }
//
//      auto line = dynamic_cast<Object::CLine*>(vector[1].get());
//      Assert::IsTrue(line);
//      if (line)
//      {
//        _CompareColors(line->GetColor(), { 0, 0, 0 });
//        _ComparePoints(line->GetPointFrom(), { 0.000000, 0.000000 });
//        _ComparePoints(line->GetPointTo(), { 10.000000, 10.000000 });
//      }
//      auto rectangle = dynamic_cast<Object::CRectangle*>(vector[2].get());
//      Assert::IsTrue(rectangle);
//      if (rectangle)
//      {
//        _CompareColors(rectangle->GetColor(), { 0, 255, 0 });
//        _ComparePoints(rectangle->GetCenterPoint(), { 0.000000, 0.000000 });
//        Assert::AreEqual(rectangle->GetDimensionX(), 5.000000);
//        Assert::AreEqual(rectangle->GetDimensionY(), 5.000000);
//      }
//
//      database.CleanUp();
//      stacks.CleanUp();
//    }
//  };
//}
