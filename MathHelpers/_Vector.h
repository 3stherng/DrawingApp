#pragma once

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept> 
#include <vector>

namespace
{
  template <typename TType>
  const constexpr void SetPrecision(const TType& i_value)
  {
    if (std::is_floating_point<TType>::value)
      std::cout << std::setprecision(1) << std::fixed;
  }
}

namespace _Vector
{
  template <typename TType>
  const auto constexpr epsilon = std::numeric_limits<TType>::epsilon();

  template <typename TType, std::size_t Dimension> class Vector;
  template <typename TType, std::size_t Dimension>
  std::ostream& operator<<(std::ostream&, const Vector<TType, Dimension>&);


  template <typename TType, std::size_t Dimension>
  class Vector
  {
  private:
    std::vector<TType> m_vector;

  public:
    Vector() : m_vector(Dimension, TType())
    {
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector(std::initializer_list<TType> i_vector)
    {
      if (i_vector.size() != Dimension)
        throw std::invalid_argument("Dimension is invalid");
      m_vector = i_vector;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    friend std::ostream& operator<< <TType, Dimension>(std::ostream& os, const Vector& i_vector);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::vector<TType>& GetVector() const
    {
      return m_vector;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t GetDimension() const
    {
      return Dimension;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const TType& operator[](std::size_t i_idx) const
    {
      return m_vector[i_idx];
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TType& operator[](std::size_t i_idx)
    {
      return m_vector[i_idx];
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Vector<TType, Dimension>& operator +=(const Vector<TType, Dimension>& i_vector)
    {
      for (size_t i = 0; i < Dimension; ++i)
      {
        m_vector[i] += i_vector[i];
      }
      return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const Vector<TType, Dimension>& operator -=(const Vector<TType, Dimension>& i_vector)
    {
      for (size_t i = 0; i < Dimension; ++i)
      {
        m_vector[i] -= i_vector[i];
      }
      return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename TType2>
    const Vector<TType, Dimension>& operator *=(const TType2& i_factor)
    {
      for (size_t i = 0; i < Dimension; ++i)
      {
        m_vector[i] *= i_factor;
      }
      return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    double GetMagnitude() const
    {
      double total_magnitude = 0;

      for (size_t i = 0; i < Dimension; ++i)
      {
        total_magnitude += std::pow(m_vector[i], 2);
      }
      return std::sqrt(total_magnitude);
    }
  };

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Free Functions
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType, std::size_t Dimension>
  std::ostream& operator<<(std::ostream& os, const Vector<TType, Dimension>& i_vector)
  {
    os << "(";
    for (const auto& coordinate : i_vector.GetVector())
    {
      SetPrecision(coordinate);
      os << coordinate;
      if (&coordinate != &i_vector.GetVector().back())
        os << ", ";
    }
    os << ")";
    return os;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType, std::size_t Dimension>
  TType FindDotProduct(const Vector<TType, Dimension>& i_vector1,
    const Vector<TType, Dimension>& i_vector2)
  {
    TType dot_product = 0;

    for (size_t i = 0; i < Dimension; ++i)
    {
      dot_product += i_vector1[i] * i_vector2[i];
    }
    return dot_product;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType>
  double FindCrossProduct(const Vector<TType, 2>& i_vector1,
    const Vector<TType, 2>& i_vector2)
  {
    return i_vector1[0] * i_vector2[1] - i_vector1[1] * i_vector2[0];
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType>
  Vector<TType, 3> FindCrossProduct(const Vector<TType, 3>& i_vector1,
    const Vector<TType, 3>& i_vector2)
  {
    auto copy = i_vector1;

    copy[0] = i_vector1[1] * i_vector2[2] - i_vector1[2] * i_vector2[1];
    copy[1] = i_vector1[2] * i_vector2[0] - i_vector1[0] * i_vector2[2];
    copy[2] = i_vector1[0] * i_vector2[1] - i_vector1[1] * i_vector2[0];

    return copy;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Not applicable for complex number
  template <typename TType, std::size_t Dimension>
  double FindAngleBetweenVector(const Vector<TType, Dimension>& i_vector1,
    const Vector<TType, Dimension>& i_vector2)
  {
    auto x = i_vector1.GetMagnitude() * i_vector2.GetMagnitude();
    
    if (x == 0)  
      throw std::invalid_argument("Magnitude of at least one vector is zero");
    
    return std::acos(FindDotProduct(i_vector1, i_vector2) / x);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*
  Binary arithmetic operators section in
  stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading
  */

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType, std::size_t Dimension>
  inline Vector<TType, Dimension> operator+(Vector<TType, Dimension> i_vector1,
    const Vector<TType, Dimension>& i_vector2)
  {
    i_vector1 += i_vector2;
    return i_vector1;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType, std::size_t Dimension>
  inline Vector<TType, Dimension> operator-(Vector<TType, Dimension> i_vector1,
    const Vector<TType, Dimension>& i_vector2)
  {
    i_vector1 -= i_vector2;
    return i_vector1;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType, typename TType2, std::size_t Dimension>
  inline Vector<TType, Dimension> operator*(Vector<TType, Dimension> i_vector,
    const TType2& i_factor)
  {
    i_vector *= i_factor;
    return i_vector;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType, std::size_t Dimension>
  inline bool operator ==(const Vector<TType, Dimension> i_vector1,
    const Vector<TType, Dimension>& i_vector2)
  {
    auto is_equal = true;

    for (size_t i = 0; i < Dimension; ++i)
    {
      if (std::abs(i_vector1[i] - i_vector2[i]) >= epsilon<TType>)
        is_equal = false;
    }
    return is_equal;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType, std::size_t Dimension>
  inline bool operator!=(const Vector<TType, Dimension> i_vector1,
    const Vector<TType, Dimension>& i_vector2)
  {
    return !(i_vector1 == i_vector2);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template <typename TType>
  using point2 = Vector<TType, 2>;

  template <typename TType>
  using point3 = Vector<TType, 3>;

  using int2 = point2<int>;
  using double2 = point2<double>;

  using int3 = point3<int>;
  using double3 = point3<double>;
  using double2 = point2<double>;
}
