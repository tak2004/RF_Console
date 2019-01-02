#pragma once

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO
{
class StringStyle;

class Console
{
public:
  void Clear();
  void Group(const StringStyle& Label);
  void GroupCollapsed();
  void EndGroup(const StringStyle& Label);
  void Log(char* Text, ...);
  void Log(const StringStyle& Text, ...);
  void Table();
  RF_Type::String Question(const StringStyle& Text);
  RF_Type::String SecretQuestion(const StringStyle& Text,
                                 RF_Type::String (*)(const RF_Type::String&));
  RF_Type::String Prompt();
};

}  // namespace RadonFramework::IO