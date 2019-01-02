#include <stdlib.h>
#include <Windows.h>
#include <wincon.h>
#include <varargs.h>
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/System/Environment.hpp"

void Clear_Windows()
{
  system("cls");
}

RF_Type::String ReadLine_Windows()
{
  RF_Type::String result;
  char c[1024];
  DWORD mode, count;
  HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
  GetConsoleMode(ih, &mode);
  SetConsoleMode(ih, mode | ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT |
                             ENABLE_ECHO_INPUT);
  while(ReadConsoleA(ih, c, 1024, &count, NULL) && count == 1024)
  {
    result += RF_Type::String(c, count);
  }
  // remove \r\n
  result.SubString(0, result.Size() - 2);
  SetConsoleMode(ih, mode);
  return RF_Type::String();
}

RF_Type::String
    ReadSecretLine_Windows(RF_Type::String (*Callback)(const RF_Type::String&))
{
  DWORD mode, count;
  HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
  RF_Type::String result;
  if(GetConsoleMode(ih, &mode))
  {
    RF_Type::String secret;
    char c[1024];
    SetConsoleMode(ih, (mode | ENABLE_LINE_INPUT) & ~ENABLE_ECHO_INPUT );
    while(ReadConsoleA(ih, c, 1024, &count, NULL))
    {
      if (count != 1024)
      {// remove \r\n
        count -= 2;
      }
      auto newPart = RF_Type::String(c, count);
      secret += newPart;
      // clear console buffer
      RF_SysMem::Set(c, 0, 1024);
      // overwrite buffer with 0 before memory release
      RF_SysMem::Set(const_cast<void*>(reinterpret_cast<const void*>(newPart.ByteData())), 0, newPart.Size());
      newPart.Clear();
      if (count < 1024)
      {
        count = 0;
        break;
      }
    }
    SetConsoleMode(ih, mode);
    result = Callback(secret);
    // overwrite buffer with 0 before memory release
    RF_SysMem::Set(const_cast<void*>(reinterpret_cast<const void*>(secret.ByteData())), 0, secret.Size());
    secret.Clear();
  }
  return result;
}

void Write_Windows(const RF_Type::String& Value)
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  WriteConsoleA(oh, Value.c_str(), Value.Length(), &written, nullptr);
}

void WriteLine_Windows(const RF_Type::String& Value)
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  WriteConsoleA(oh, (Value + "\n").c_str(), Value.Length(), &written, nullptr);
}

void SetForgroundColor_Windows(RF_Type::UInt8 R,
                               RF_Type::UInt8 G,
                               RF_Type::UInt8 B)
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  auto escape = RF_Type::String::Format("\x1b[38;2;%u;%u;%um"_rfs, R, G, B);
  WriteConsoleA(oh, escape.c_str(), escape.Length(), &written, nullptr);
}

void SetBackgroundColor_Windows(RF_Type::UInt8 R,
                                RF_Type::UInt8 G,
                                RF_Type::UInt8 B)
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  auto escape = RF_Type::String::Format("\x1b[48;2;%u;%u;%um"_rfs, R, G, B);
  WriteConsoleA(oh, escape.c_str(), escape.Length(), &written, nullptr);
}

void SetModifier_Windows(RF_SysConsole::Modifiers Modifiers)
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
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
  WriteConsoleA(oh, escape.c_str(), escape.Length(), &written, nullptr);
}

void ResetForgroundColor_Windows()
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  RF_Type::String escape;
  escape = RF_Type::String::Format("\x1b[39m"_rfs);
  WriteConsoleA(oh, escape.c_str(), escape.Length(), &written, nullptr);
}

void ResetBackgroundColor_Windows()
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  RF_Type::String escape;
  escape = RF_Type::String::Format("\x1b[49m"_rfs);
  WriteConsoleA(oh, escape.c_str(), escape.Length(), &written, nullptr);
}

void ResetModifier_Windows(RF_SysConsole::Modifiers Modifiers)
{
  DWORD written;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
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
  WriteConsoleA(oh, escape.c_str(), escape.Length(), &written, nullptr);
}

RF_SysConsole::ColorLevel GetColorLevelSupport_Windows()
{
  auto result = RF_SysConsole::ColorLevel::HasBasic;
  auto& version = RF_SysEnv::OSVersion();
  // Windows 10 build 10586 is the first Windows release that supports 256
  // colors. Windows 10 build 14931 is the first release that supports
  // 16m/TrueColor.
  if(version.VersionNumber().Major() >= 10 &&
     version.VersionNumber().Build() >= 10586)
  {
    result = version.VersionNumber().Build() >= 14931
                 ? RF_SysConsole::ColorLevel::Has16m
                 : RF_SysConsole::ColorLevel::Has256;
  }
  return result;
}

namespace RadonFramework::System::IO::Console
{
void Init()
{
  if(GetColorLevelSupport_Windows() == RF_SysConsole::ColorLevel::Has16m)
  {
    // Enable escape sequence processing for true color support and table
    // printing support.
    HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(oh, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(oh, dwMode);
    SetConsoleOutputCP(CP_UTF8);
  }
}

void Dispatch()
{
  Init();
  Clear = ::Clear_Windows;
  ReadLine = ::ReadLine_Windows;
  ReadSecretLine = ::ReadSecretLine_Windows;
  WriteLine = ::WriteLine_Windows;
  Write = ::Write_Windows;
  SetForgroundColor = ::SetForgroundColor_Windows;
  SetBackgroundColor = ::SetBackgroundColor_Windows;
  SetModifier = ::SetModifier_Windows;
  ResetForgroundColor = ::ResetForgroundColor_Windows;
  ResetBackgroundColor = ::ResetBackgroundColor_Windows;
  ResetModifier = ::ResetModifier_Windows;
  GetColorLevelSupport = ::GetColorLevelSupport_Windows;
}

}  // namespace RadonFramework::System::IO::Console