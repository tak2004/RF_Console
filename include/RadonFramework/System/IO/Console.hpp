#pragma once

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework::System::IO::Console
{
void Dispatch();
RF_Type::Bool IsSuccessfullyDispatched();
void GetNotDispatchedFunctions(RF_Collect::List<RF_Type::String>& Result);

using ClearCallback = void (*)();
extern ClearCallback Clear;

using ReadLineCallback = RF_Type::String (*)();
extern ReadLineCallback ReadLine;

using ReadSecretLineCallback =
    RF_Type::String (*)(RF_Type::String (*)(const RF_Type::String&));
extern ReadSecretLineCallback ReadSecretLine;

using WriteLineCallback = void (*)(const RF_Type::String&);
extern WriteLineCallback WriteLine;

using WriteCallback = void (*)(const RF_Type::String&);
extern WriteCallback Write;

using SetForgroundColorCallback = void (*)(RF_Type::UInt8,
                                           RF_Type::UInt8,
                                           RF_Type::UInt8);
extern SetForgroundColorCallback SetForgroundColor;

using SetBackgroundColorCallback = void (*)(RF_Type::UInt8,
                                            RF_Type::UInt8,
                                            RF_Type::UInt8);
extern SetBackgroundColorCallback SetBackgroundColor;

using ResetForgroundColorCallback = void (*)();
extern ResetForgroundColorCallback ResetForgroundColor;

using ResetBackgroundColorCallback = void (*)();
extern ResetBackgroundColorCallback ResetBackgroundColor;

using GetScreenSizeCallback =
    RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16> (*)();
extern GetScreenSizeCallback GetScreenSize;

using GetCursorPositionCallback =
    RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16> (*)();
extern GetCursorPositionCallback GetCursorPosition;

using SaveCursorPositionCallback = void (*)();
extern SaveCursorPositionCallback SaveCursorPosition;

using RestoreCursorPositionCallback = void (*)();
extern RestoreCursorPositionCallback RestoreCursorPosition;

using ClearScreenCallback = void (*)();
extern ClearScreenCallback ClearScreen;

using MoveCursorToCallback = void (*)(RF_Type::UInt16, RF_Type::UInt16);
extern MoveCursorToCallback MoveCursorTo;

using MoveCursorUpCallback = void(*)(RF_Type::UInt16);
extern MoveCursorUpCallback MoveCursorUp;

using MoveCursorDownCallback = void (*)(RF_Type::UInt16);
extern MoveCursorDownCallback MoveCursorDown;

using MoveCursorLeftCallback = void (*)(RF_Type::UInt16);
extern MoveCursorLeftCallback MoveCursorLeft;

using MoveCursorRightCallback = void (*)(RF_Type::UInt16);
extern MoveCursorRightCallback MoveCursorRight;

using HideCursorCallback = void (*)();
extern HideCursorCallback HideCursor;

using ShowCursorCallback = void (*)();
extern ShowCursorCallback ShowCursor;

enum class Modifiers
{
  Reset,
  Bold,
  Dim,
  Italic,
  Underline,
  Inverse,
  Hidden,
  Strikethrough,
  Visible
};

using SetModifierCallback = void (*)(Modifiers);
extern SetModifierCallback SetModifier;

using ResetModifierCallback = void (*)(Modifiers);
extern ResetModifierCallback ResetModifier;

enum class ColorLevel
{
  NoColorSupport,
  HasBasic,
  Has256,
  Has16m
};

using GetColorLevelSupportCallback = ColorLevel (*)();
extern GetColorLevelSupportCallback GetColorLevelSupport;

}  // namespace RadonFramework::System::IO::Console

#ifndef RF_SHORTHAND_NAMESPACE_SYSCONSOLE
#define RF_SHORTHAND_NAMESPACE_SYSCONSOLE
namespace RF_SysConsole = RadonFramework::System::IO::Console;
#endif