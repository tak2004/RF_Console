#pragma once

#include <RadonFramework/IO/ConsoleUI/Component.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO::ConsoleUI
{

struct P : public Component
{
  template <typename... ARGS>
  P(ARGS&&... Args)
  {
    RegisterState("text", Text);
    RegisterState("color", Color);
    Add(Args...);
  }

  RF_Type::Size
  Render(StringStyle& Style, const RF_Type::Size Width) override
  {
    Text.Updated();
    Color.Updated();
    Style.RGB(Color())
        .Text(RF_Type::String::Format("%-*s"_rfs, Width, Text().c_str()))
        .Reset();
    return 1;
  }

  RF_Type::Bool ShouldComponentUpdate() const override
  {
    return Text.WasChanged() || Color.WasChanged();
  }

  State<RF_Type::String> Text;
  State<RF_Color::RGB> Color;
};

}  // namespace RadonFramework::IO::ConsoleUI

namespace RF_CUI = RadonFramework::IO::ConsoleUI;