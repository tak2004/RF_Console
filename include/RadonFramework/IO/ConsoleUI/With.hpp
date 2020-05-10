#pragma once

#include <RadonFramework/IO/ConsoleUI/Component.hpp>
#include <RadonFramework/IO/ConsoleUI/ComponentOperator.hpp>
#include <RadonFramework/IO/ConsoleUI/State.hpp>

namespace RadonFramework::IO::ConsoleUI
{

template <class T>
struct With : public ComponentOperator
{
  template <int N>
  With(char const (&CString)[N], T&& Value)
  : m_Temporary(Value), m_State(RF_HASH(CString))
  {
  }

  void operator()(Component& Receiver) override
  {
    void* result;
    if(Receiver.States().Get(m_State, result))
    {
      (*reinterpret_cast<State<T>*>(result)) = m_Temporary;
    }
  }
  const T m_Temporary;
  const RF_Type::UInt64 m_State;
};

}

namespace RF_CUI = RadonFramework::IO::ConsoleUI;