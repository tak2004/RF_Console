#include "RadonFramework/IO/Console.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/IO/StringStyle.hpp"

namespace RadonFramework::IO
{
void Console::Clear()
{
  RadonFramework::System::IO::Console::Clear();
}

void Console::Group(const StringStyle& Label) {}

void Console::GroupCollapsed() {}

void Console::EndGroup(const StringStyle& Label) {}

void Console::Log(char* Text, ...) {}

void Console::Log(const StringStyle& Text, ...) {
  Text.ToString();
}

void Console::Table() {}

RF_Type::String Console::Question(const StringStyle& Text)
{
  Log(Text);
  return RadonFramework::System::IO::Console::ReadLine();
}

RF_Type::String Console::SecretQuestion(const StringStyle& Text, 
  RF_Type::String (*Callback)(const RF_Type::String&))
{
  Log(Text);
  return RadonFramework::System::IO::Console::ReadSecretLine(Callback);
}

RF_Type::String Console::Prompt()
{
  return RadonFramework::System::IO::Console::ReadLine();
}

}  // namespace RadonFramework::IO