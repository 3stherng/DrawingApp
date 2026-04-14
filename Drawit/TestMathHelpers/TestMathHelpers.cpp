#include "pch.h"
#include "CppUnitTest.h"

#include "../MathHelpers/_Vector.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace TestMathHelpers
{
  TEST_CLASS(TestVectors)
  {
  private:
    _Vector::double3 v1 = { 1.0, 2.0, 3.0 };
    _Vector::double3 v2 = { 4.0, 5.0, 6.0 };

  public:

    TEST_METHOD(Addition)
    {
      _Vector::double3 add_result = v1 + v2;

      Assert::AreEqual(add_result[0], 5.0);
      Assert::AreEqual(add_result[1], 7.0);
      Assert::AreEqual(add_result[2], 9.0);
    }

    TEST_METHOD(Subtraction)
    {
      _Vector::double3 minus_result = v1 - v2;

      Assert::AreEqual(minus_result[0], -3.0);
      Assert::AreEqual(minus_result[1], -3.0);
      Assert::AreEqual(minus_result[2], -3.0);
    }

    TEST_METHOD(MultiplicationByScalar)
    {
      double scalar = 2.0;

      _Vector::double3 multiply_result = v1 * scalar;

      Assert::AreEqual(multiply_result[0], 2.0);
      Assert::AreEqual(multiply_result[1], 4.0);
      Assert::AreEqual(multiply_result[2], 6.0);
    }

    TEST_METHOD(Equality)
    {
      _Vector::double3 v3 = { 1.0, 2.0, 3.0 };

      Assert::IsTrue(v1 == v3);
    }

    TEST_METHOD(Inequality)
    {
      Assert::IsTrue(v1 != v2);
    }

    TEST_METHOD(DotProduct)
    {
      double dot_result = _Vector::FindDotProduct(v1, v2);

      Assert::AreEqual(dot_result, 32.0);
    }

    TEST_METHOD(CrossProduct)
    {
      _Vector::double3 crossed_result = _Vector::FindCrossProduct(v1, v2);

      Assert::AreEqual(crossed_result[0], -3.0);
      Assert::AreEqual(crossed_result[1], 6.0);
      Assert::AreEqual(crossed_result[2], -3.0);
    }

    TEST_METHOD(Magnitude)
    {
      _Vector::double3 v4 = { 1.0, 2.0, 2.0 };

      double result = v4.GetMagnitude();

      Assert::AreEqual(result, 3.0);
    }

    TEST_METHOD(AngleBetweenVectors)
    {
      _Vector::double3 v5 = { 1.0, 0.0, 0.0 };
      _Vector::double3 v6 = { 0.0, 1.0, 0.0 };

      double result = _Vector::FindAngleBetweenVector(v5, v6);

      double tolerance = 1e-4;
      double expected_angle = 1.5708;

      Assert::IsTrue(std::abs(result - expected_angle) < tolerance);
    }

    TEST_METHOD(InvalidDimensionInitialized)
    {
      Assert::ExpectException<std::invalid_argument>([]
        {
          _Vector::double3 vector_missing_z = { 1.0, 0.0 };
        });

      Assert::ExpectException<std::invalid_argument>([]
        {
          _Vector::double3 vector_extra_value = { 1.0, 0.0, 0.0, 0.0 };
        });
    }
  };
}
