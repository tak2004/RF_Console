#include  <stdio.h>
#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/Security.hpp"

void Write_Unix(const RF_Type::String& Value)
{
  fwrite(Value.c_str(),sizeof(RF_Type::UInt8), Value.Length(), stdout);
}

void HideCursor_Unix()
{
  system("tput civis");
}

void ShowCursor_Unix()
{
  system("tput cnorm");
}

namespace RadonFramework::System::IO::Console
{

void Dispatch_UNIX()
{
  Write = ::Write_Unix;
  HideCursor = ::HideCursor_Unix;
  ShowCursor = ::ShowCursor_Unix;
}

}  // namespace RadonFramework::System::IO::Console