#pragma once

#include <RadonFramework/IO/ConsoleUI/Component.hpp>

namespace RadonFramework::IO::ConsoleUI
{

class VirtualConsole
{
public:
  VirtualConsole(RF_Type::Size DesignWidth = 80) : m_DesignWidth(DesignWidth)
  {
    RF_IO::Console console;
    auto size = console.GetScreenSize();
    m_Width = size.First;
    m_Height = size.Second;
  }

  RF_IO::StringStyle ToStyle()
  {
    RF_IO::StringStyle result;
    m_Childs->Render(result, m_Width);
    return result;
  }

  template <typename... ARGS>
  void SetTree(ARGS&&... Args)
  {
    m_Childs.Reset(new RF_CUI::Component(Args...));
    m_Childs->Startup();
  }

  RF_Type::Bool ShouldUpdate() const
  {
    return m_Childs ? m_Childs->ShouldComponentUpdate() : false;
  }

private:
  RF_Type::Size m_Width;
  RF_Type::Size m_Height;
  RF_Type::Size m_DesignWidth;
  RF_Mem::AutoPointer<Component> m_Childs;
};

}  // namespace RadonFramework::IO::ConsoleUI

namespace RF_CUI = RadonFramework::IO::ConsoleUI;