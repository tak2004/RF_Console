#include "RadonFramework/BuildInfo.hpp"
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/System/IO/Console.hpp"

void SetForgroundColor_Escape(RF_Type::UInt8 R,
  RF_Type::UInt8 G,
  RF_Type::UInt8 B)
{
  RF_SysConsole::Write(
      RF_Type::String::Format("\x1b[38;2;%u;%u;%um"_rfs, R, G, B));
}

void SetBackgroundColor_Escape(RF_Type::UInt8 R,
                              RF_Type::UInt8 G,
                              RF_Type::UInt8 B)
{
  RF_SysConsole::Write(
      RF_Type::String::Format("\x1b[48;2;%u;%u;%um"_rfs, R, G, B));
}

void SetModifier_Escape(RF_SysConsole::Modifiers Modifiers)
{
  RF_Type::String escape;
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Reset)
  {
    escape = RF_Type::String::Format("\x1b[0m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Bold)
  {
    escape = RF_Type::String::Format("\x1b[1m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Dim)
  {
    escape = RF_Type::String::Format("\x1b[2m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Italic)
  {
    escape = RF_Type::String::Format("\x1b[3m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Underline)
  {
    escape = RF_Type::String::Format("\x1b[4m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Inverse)
  {
    escape = RF_Type::String::Format("\x1b[7m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Hidden)
  {
    escape = RF_Type::String::Format("\x1b[8m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Strikethrough)
  {
    escape = RF_Type::String::Format("\x1b[9m"_rfs);
  }
  RF_SysConsole::Write(escape);
}

void ResetModifier_Escape(RF_SysConsole::Modifiers Modifiers)
{
  RF_Type::String escape;
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Reset)
  {
    escape = RF_Type::String::Format("\x1b[0m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Bold ||
     Modifiers == RadonFramework::System::IO::Console::Modifiers::Dim)
  {
    escape = RF_Type::String::Format("\x1b[22m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Italic)
  {
    escape = RF_Type::String::Format("\x1b[23m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Underline)
  {
    escape = RF_Type::String::Format("\x1b[24m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Inverse)
  {
    escape = RF_Type::String::Format("\x1b[27m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Hidden)
  {
    escape = RF_Type::String::Format("\x1b[28m"_rfs);
  }
  if(Modifiers == RadonFramework::System::IO::Console::Modifiers::Strikethrough)
  {
    escape = RF_Type::String::Format("\x1b[29m"_rfs);
  }
  RF_SysConsole::Write(escape);
}

void SaveCursorPosition_Escape()
{
  RF_SysConsole::Write("\033[s"_rfs);
}

void RestoreCursorPosition_Escape()
{
  RF_SysConsole::Write("\033[u"_rfs);
}

void ClearScreen_Escape()
{
  RF_SysConsole::Write("\033[2J"_rfs);
}

void ResetForgroundColor_Escape()
{
  RF_SysConsole::Write("\x1b[39m"_rfs);
}

void ResetBackgroundColor_Escape()
{
  RF_SysConsole::Write("\x1b[49m"_rfs);
}

void MoveCursorTo_Escape(RF_Type::UInt16 Line, RF_Type::UInt16 Column)
{
  RF_SysConsole::Write(RF_Type::String::Format("\033[%d;%dH"_rfs, Line, Column));
}

void MoveCursorUp_Escape(RF_Type::UInt16 ByValue)
{
  RF_SysConsole::Write(RF_Type::String::Format("\033[%dA"_rfs,ByValue));
}

void MoveCursorDown_Escape(RF_Type::UInt16 ByValue)
{
  RF_SysConsole::Write(RF_Type::String::Format("\033[%dB"_rfs, ByValue));
}

void MoveCursorLeft_Escape(RF_Type::UInt16 ByValue)
{
  RF_SysConsole::Write(RF_Type::String::Format("\033[%dD"_rfs, ByValue));
}

void MoveCursorRight_Escape(RF_Type::UInt16 ByValue)
{
  RF_SysConsole::Write(RF_Type::String::Format("\033[%dC"_rfs, ByValue));
}

namespace RadonFramework::System::IO::Console
{
void Dispatch()
{
  if constexpr(RF_BI::HostingOS == RF_BI::HostOS::UNIX ||
               RF_BI::HostingOS == RF_BI::HostOS::Linux ||
               RF_BI::HostingOS == RF_BI::HostOS::MacOS ||
               RF_BI::HostingOS == RF_BI::HostOS::Windows)
  {
    SaveCursorPosition = ::SaveCursorPosition_Escape;
    RestoreCursorPosition = ::RestoreCursorPosition_Escape;
    ClearScreen = ::ClearScreen_Escape;
    ResetForgroundColor = ::ResetForgroundColor_Escape;
    ResetBackgroundColor = ::ResetBackgroundColor_Escape;
    SetForgroundColor = ::SetForgroundColor_Escape;
    SetBackgroundColor = ::SetBackgroundColor_Escape;
    SetModifier = ::SetModifier_Escape;
    ResetForgroundColor = ::ResetForgroundColor_Escape;
    ResetBackgroundColor = ::ResetBackgroundColor_Escape;
    ResetModifier = ::ResetModifier_Escape;
    MoveCursorTo = ::MoveCursorTo_Escape;
    MoveCursorUp = ::MoveCursorUp_Escape;
    MoveCursorDown = ::MoveCursorDown_Escape;
    MoveCursorLeft = ::MoveCursorLeft_Escape;
    MoveCursorRight = ::MoveCursorRight_Escape;
  }

  if constexpr(RF_BI::HostingOS == RF_BI::HostOS::Windows)
  {
    extern void Dispatch_Windows();
    Dispatch_Windows();
  }

  if constexpr(RF_BI::HostingOS == RF_BI::HostOS::UNIX ||
               RF_BI::HostingOS == RF_BI::HostOS::Linux ||
               RF_BI::HostingOS == RF_BI::HostOS::MacOS)
  {
    extern void Dispatch_UNIX();
    Dispatch_UNIX();
  }
}

}  // namespace RadonFramework::System::IO::Console