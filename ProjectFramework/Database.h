#pragma once

#include "IObject.h"

#include <algorithm>

namespace Object
{
  class CCircle;
  class CLine;
  class CRectangle;
}

class Database
{
private:
  std::vector<std::shared_ptr<IObject>> m_object_vector{};

  Database() = default;
  ~Database() = default;

public:
  static Database& GetInstance()
  {
    static Database instance;
    return instance;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  std::vector<std::shared_ptr<IObject>> GetObjectVector()
  {
    return m_object_vector;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void AppendToObjectVector(std::shared_ptr<IObject> ip_object)
  {
    m_object_vector.push_back(ip_object);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void RemoveObjectFromObjectVector(std::shared_ptr<IObject> ip_object)
  {
    // Question: Would it reduce time complexity?
    if (ip_object == m_object_vector.back())
    {
      m_object_vector.pop_back();
      return;
    }

    m_object_vector.erase(std::remove(m_object_vector.begin(), m_object_vector.end(), ip_object), 
                          m_object_vector.end());
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  void CleanUp()
  {
    std::for_each(m_object_vector.begin(), m_object_vector.end(),
                  [](std::shared_ptr<IObject>& ip_object) 
                  { 
                    ip_object->ResetGlobalID();
                    ip_object.reset(); 
                  });

    m_object_vector.clear();
  }
};
