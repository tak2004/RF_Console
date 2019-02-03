#pragma once

#include <RadonFramework/Core/Types/Bool.hpp>

namespace RadonFramework::IO::ConsoleUI
{

template <class T>
struct State
{
  void operator=(T Value)
  {
    m_Changed = m_Value != Value;
    if(m_Changed)
    {
      m_Value = Value;
    }
  }
  operator T() { return m_Value; }
  RF_Type::Bool WasChanged() const { return m_Changed; }
  const T& operator()() { return m_Value; }
  T* operator->()
  {
    m_Changed = true;
    return &m_Value;
  }
  void Updated() { m_Changed = false; }

private:
  T m_Value;
  RF_Type::Bool m_Changed;
};

}

namespace RF_CUI = RadonFramework::IO::ConsoleUI;