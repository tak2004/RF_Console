#pragma once

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Drawing/Color/Spaces.hpp>
#include <RadonFramework/Drawing/Color/Gradient.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework::Core::Types
{
class String;
}

namespace RadonFramework::IO
{
class StringStyle
{
public:
  StringStyle();
  StringStyle(StringStyle&& Move);
  ~StringStyle();

  StringStyle& RGB(RF_Color::RGB Color, RF_Type::Bool Forground = true);
  StringStyle& Hex(RF_Type::UInt32 RGB, RF_Type::Bool Forground = true);
  StringStyle& HSL(RF_Color::HSL Color, RF_Type::Bool Forground = true);
  StringStyle& HSV(RF_Color::HSV Color, RF_Type::Bool Forground = true);
  StringStyle& HWB(RF_Color::HWB Color, RF_Type::Bool Forground = true);

  StringStyle& Bold();
  StringStyle& Bold(const RF_Type::String& Text);
  StringStyle& Italic();
  StringStyle& Italic(const RF_Type::String& Text);
  StringStyle& Underline();
  StringStyle& Underline(const RF_Type::String& Text);
  StringStyle& Strikethrough();
  StringStyle& Strikethrough(const RF_Type::String& Text);
  StringStyle& Reset();
  StringStyle& Dim();
  StringStyle& Dim(const RF_Type::String& Text);
  StringStyle& Hidden();
  StringStyle& Visible();
  StringStyle& Inverse();
  StringStyle& Inverse(const RF_Type::String& Text);

  StringStyle& Black(RF_Type::Bool Forground = true);
  StringStyle&
  Black(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Red(RF_Type::Bool Forground = true);
  StringStyle& Red(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Green(RF_Type::Bool Forground = true);
  StringStyle&
  Green(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Yellow(RF_Type::Bool Forground = true);
  StringStyle&
  Yellow(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Blue(RF_Type::Bool Forground = true);
  StringStyle&
  Blue(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Magenta(RF_Type::Bool Forground = true);
  StringStyle&
  Magenta(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Cyan(RF_Type::Bool Forground = true);
  StringStyle&
  Cyan(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& White(RF_Type::Bool Forground = true);
  StringStyle&
  White(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Gray(RF_Type::Bool Forground = true);
  StringStyle&
  Gray(const RF_Type::String& Text, RF_Type::Bool Forground = true);
  StringStyle& Text(const RF_Type::String& Text);

  StringStyle&
  Gradient(const RF_Color::Gradient& Gradient, RF_Type::Bool Forground = true);
  StringStyle& Gradient(const RF_Color::Gradient& Gradient,
                        const RF_Type::String& Text,
                        RF_Type::Bool Forground = true);

  void ToString() const;

  StringStyle& SaveCursorPosition();
  StringStyle& RestoreCursorPosition();
  StringStyle& MoveCursorUp(RF_Type::UInt16 ByValue);
  StringStyle& MoveCursorDown(RF_Type::UInt16 ByValue);
  StringStyle& MoveCursorRight(RF_Type::UInt16 ByValue);
  StringStyle& LineBreak(RF_Type::UInt16 LineWidth);

protected:
  class StyleCommand;
  StyleCommand* m_Commands;
};

}  // namespace RadonFramework::IO