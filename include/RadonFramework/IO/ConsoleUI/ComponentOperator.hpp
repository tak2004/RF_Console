#pragma once

#include <RadonFramework/Core/Types/Utils/StringOperators.hpp>
#include <RadonFramework/IO/ConsoleUI/Component.hpp>

namespace RadonFramework::IO::ConsoleUI
{

struct ComponentOperator
{
  virtual void operator()(Component& Receiver) = 0;
};

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
      (*reinterpret_cast<RF_CUI::State<T>*>(result)) = m_Temporary;
    }
  }
  const T m_Temporary;
  const RF_Type::UInt64 m_State;
};

}

namespace RF_CUI = RadonFramework::IO::ConsoleUI;