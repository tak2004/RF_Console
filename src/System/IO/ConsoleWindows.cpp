#include <stdlib.h>
#include <Windows.h>
#include <wincon.h>
#include <varargs.h>
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Security.hpp"

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
    SetConsoleMode(ih, (mode | ENABLE_LINE_INPUT) & ~ENABLE_ECHO_INPUT);
    while(ReadConsoleA(ih, c, 1024, &count, NULL))
    {
      if(count != 1024)
      {  // remove \r\n
        count -= 2;
      }
      auto newPart = RF_Type::String(c, count);
      secret += newPart;
      RF_SysSecurity::EnsureFillZeros(reinterpret_cast<RF_Type::UInt8*>(c),
                                      1024);
      RF_SysSecurity::EnsureFillZeros(
          const_cast<RF_Type::UInt8*>(newPart.ByteData()), newPart.Size());
      newPart.Clear();
      if(count < 1024)
      {
        count = 0;
        break;
      }
    }
    SetConsoleMode(ih, mode);
    result = Callback(secret);
    RF_SysSecurity::EnsureFillZeros(
        const_cast<RF_Type::UInt8*>(secret.ByteData()), secret.Size());
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

RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16> GetScreenSize_Windows()
{
  RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16> result;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  if(GetConsoleScreenBufferInfo(oh, &csbi))
  {
    result.First = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    result.Second = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  }
  return result;
}

RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16> GetCursorPosition_Windows()
{
  RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16> result;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE oh = GetStdHandle(STD_OUTPUT_HANDLE);
  if(GetConsoleScreenBufferInfo(oh, &csbi))
  {
    result.First = csbi.dwCursorPosition.X;
    result.Second = csbi.dwCursorPosition.Y;
  }
  return result;
}

void ShowConsoleCursor(bool showFlag)
{
  HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

  CONSOLE_CURSOR_INFO cursorInfo;

  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = showFlag;  // set the cursor visibility
  SetConsoleCursorInfo(out, &cursorInfo);
}

void HideCursor_Windows() {
  ShowConsoleCursor(false);
}

void ShowCursor_Windows()
{
  ShowConsoleCursor(true);
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

void Dispatch_Windows()
{
  Init();
  Clear = ::Clear_Windows;
  ReadLine = ::ReadLine_Windows;
  ReadSecretLine = ::ReadSecretLine_Windows;
  WriteLine = ::WriteLine_Windows;
  Write = ::Write_Windows;
  GetColorLevelSupport = ::GetColorLevelSupport_Windows;
  GetScreenSize = ::GetScreenSize_Windows;
  GetCursorPosition = ::GetCursorPosition_Windows;
  HideCursor = ::HideCursor_Windows;
  ShowCursor = ::ShowCursor_Windows;
}

}  // namespace RadonFramework::System::IO::Console