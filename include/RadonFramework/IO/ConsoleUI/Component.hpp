#pragma once

#include <RadonFramework/IO/ConsoleUI/ComponentOperator.hpp>
#include <RadonFramework/IO/ConsoleUI/State.hpp>
#include <RadonFramework/IO/ConsoleUI/Property.hpp>
#include <RadonFramework/IO/StringStyle.hpp>
#include <RadonFramework/Collections/HashList.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>

namespace RadonFramework::IO::ConsoleUI
{

struct Component
{
  using IDType = RF_Collect::HashList::KeyType;
  using StateKeyType = RF_Collect::HashList::KeyType;

  Component() : m_States(1) { RegisterState("id", ID); }
  Component(Component&& Move) : m_States(1)
  {
    m_Childs.Swap(Move.m_Childs);
    RegisterState("id", ID);
    ID = Move.ID;
  }

  Component(Component& Copy) : m_States(1)
  {
    m_Childs.Swap(Copy.m_Childs);
    RegisterState("id", ID);
    ID = Copy.ID;
  }

  template <typename... ARGS>
  Component(ARGS&&... Args) : m_States(1)
  {
    RegisterState("id", ID);
    Add(Args...);
  }

  template <class T, int N>
  void RegisterState(char const (&CString)[N], State<T>& State)
  {
    m_States.Add(RF_HASH(CString), &State);
  }

  template <class T>
  void Add(T& Other)
  {
    if constexpr(std::is_base_of<Component, T>::value)
    {
      m_Childs.PushBack(RF_Mem::AutoPointer<T>(new T(Other)));

      T* last = reinterpret_cast<T*>(m_Childs[m_Childs.Count() - 1]);
      if(last->ID)
      {
        GetIDList().Add(last->ID, last);
      }
    }
    if constexpr(std::is_base_of<ComponentOperator, T>::value)
    {
      Other(*this);
    }
  }

  template <class T, typename... ARGS>
  void Add(T& First, ARGS&&... Rest)
  {
    Add(Rest...);
    Add(First);
  }

  virtual RF_Type::Bool ShouldComponentUpdate() const
  {
    RF_Type::Bool result = false;
    if(m_Childs.Count() > 0)
    {
      for(auto i = 0; i < m_Childs.Count(); ++i)
      {
        if(m_Childs[i]->ShouldComponentUpdate())
        {
          result = true;
          break;
        }
      }
    }
    return result;
  }

  virtual void Startup()
  {
    if(m_Childs.Count() > 0)
    {
      for(auto i = 0; i < m_Childs.Count(); ++i)
      {
        m_Childs[i]->Startup();
      }
    }
  }

  virtual RF_Type::Size
  Render(StringStyle& Style, const RF_Type::Size Width)
  {
    RF_Type::Size maxLines = 0;
    for(auto i = m_Childs.Count(); i > 0; --i)
    {
      auto lines = m_Childs[i - 1]->Render(Style, Width);
      if(lines > maxLines)
      {
        maxLines = lines;
      }
      Style.MoveCursorUp(lines - 1);
    }
    Style.MoveCursorDown(maxLines - 1);
    return maxLines;
  }

  RF_Type::Size GetChildCount() const { return m_Childs.Count(); }

  Component* GetElementByID(const IDType ID)
  {
    Component* result = nullptr;
    GetIDList().Get(ID, reinterpret_cast<void*&>(result));
    return result;
  }

  RF_Collect::HashList& States() { return m_States; }

  RF_CUI::State<IDType> ID;

private:
  RF_Collect::AutoVector<Component> m_Childs;
  RF_Collect::HashList m_States;

  static RF_Collect::HashList& GetIDList()
  {
    static RF_Collect::HashList globalIDList(100);
    return globalIDList;
  }
};

}

namespace RF_CUI = RadonFramework::IO::ConsoleUI;