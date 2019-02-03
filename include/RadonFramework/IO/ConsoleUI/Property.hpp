#pragma once

namespace RadonFramework::IO::ConsoleUI
{

  template <class T>
struct Property
{
  Property(const T& Literal) : m_Value(Literal) {}
  operator T() { return m_Value; }

private:
  T m_Value;
};

}

namespace RF_CUI = RadonFramework::IO::ConsoleUI;