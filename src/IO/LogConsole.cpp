#include "RadonFramework/IO/LogConsole.hpp"
#include "RadonFramework/IO/Console.hpp"
#include "RadonFramework/IO/StringStyle.hpp"

namespace RadonFramework::IO
{
void LogConsole::WriteInfo(const RF_Type::String& Text)
{
  Console().Log(StringStyle().Gray(Text + "\n"_rfs));
}

void LogConsole::WriteError(const RF_Type::String& Text)
{
  Console().Log(StringStyle().RGB({127, 0, 0}).Text(Text + "\n"_rfs));
}

void LogConsole::WriteFatalError(const RF_Type::String& Text)
{
  Console().Log(StringStyle().Red(Text + "\n"_rfs));
}

void LogConsole::WriteDebug(const RF_Type::String& Text)
{
  Console().Log(StringStyle().RGB({127, 127, 0}).Text(Text+"\n"_rfs));
}

}  // namespace RadonFramework::IO