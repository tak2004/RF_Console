#pragma once

#include <RadonFramework/IO/ConsoleUI/Component.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO::ConsoleUI
{

struct Progress : public Component
{
public:
  Progress() : Max(100)
  {
    Current = 50;
    RegisterState("current", Current);
  }
  template <typename... ARGS>
  Progress(ARGS&&... Args) : Max(100)
  {
    RegisterState("current", Current);
    Add(Args...);
  }

  RF_Type::Size
  Render(StringStyle& Style, const RF_Type::Size Width) override
  {
    Current.Updated();

    RF_Type::Size characters = (Current * Width) / Max;
    if(characters > 0 && characters < Width)
    {
      auto forground = RF_Type::String::Format("%-*s"_rfs, characters, " "_rfs);
      auto progressBackground =
          RF_Type::String::Format("%-*s"_rfs, Width - characters, " "_rfs);
      Style.RGB(RF_Color::RGB{0, 132, 193}, false)
          .Text(forground)
          .Gray(progressBackground, false)
          .Reset();
    }
    else
    {
      auto bar = RF_Type::String::Format("%-*s"_rfs, Width, " "_rfs);
      if(characters == 0)
      {
        Style.Gray(bar, false).Reset();
      }
      else
      {
        Style.RGB(RF_Color::RGB{0, 132, 193}, false).Text(bar).Reset();
      }
    }
    return 1;
  }

  RF_Type::Bool ShouldComponentUpdate() const override
  {
    return Current.WasChanged();
  }

  State<RF_Type::UInt8> Current;
  Property<RF_Type::UInt8> Max;
};

}  // namespace RadonFramework::IO::ConsoleUI

namespace RF_CUI = RadonFramework::IO::ConsoleUI;