#include "RadonFramework/IO/Console.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/IO/StringStyle.hpp"

namespace RadonFramework::IO
{
void Console::Clear()
{
  RF_SysConsole::Clear();
}

void Console::Group(const StringStyle& Label) {}

void Console::GroupCollapsed() {}

void Console::EndGroup(const StringStyle& Label) {}

void Console::Log(const RF_Type::String& Text)
{
  RF_SysConsole::Write(Text);
}

void Console::Log(const StringStyle& Text)
{
  Text.ToString();
}

void Console::Table() {}

RF_Type::String Console::Question(const StringStyle& Text)
{
  Log(Text);
  return RF_SysConsole::ReadLine();
}

RF_Type::String
Console::SecretQuestion(const StringStyle& Text,
                        RF_Type::String (*Callback)(const RF_Type::String&))
{
  Log(Text);
  return RF_SysConsole::ReadSecretLine(Callback);
}

RF_Type::String Console::Prompt()
{
  return RF_SysConsole::ReadLine();
}

RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16>
Console::GetScreenSize() const
{
  return RF_SysConsole::GetScreenSize();
}

}  // namespace RadonFramework::IO