#pragma once

#include <RadonFramework/IO/ConsoleUI/Component.hpp>

namespace RadonFramework::IO::ConsoleUI
{

struct Div : public Component
{
  template <typename... ARGS>
  Div(ARGS&&... Args) : Component(Args...)
  {
  }

  RF_Type::Size
  Render(StringStyle& Style, const RF_Type::Size Width) override
  {
    auto result = Component::Render(Style, Width / GetChildCount());
    Style.LineBreak(Width);
    return 1;
  }
};

}

namespace RF_CUI = RadonFramework::IO::ConsoleUI;