#pragma once

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Collections/Pair.hpp>

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
  void Log(const RF_Type::String& Text);
  void Log(const StringStyle& Text);
  void Table();
  RF_Type::String Question(const StringStyle& Text);
  RF_Type::String SecretQuestion(const StringStyle& Text,
                                 RF_Type::String (*)(const RF_Type::String&));
  RF_Type::String Prompt();
  RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16> GetScreenSize() const;
  void SetCursorVisible(RF_Type::Bool Visible= false);
};

}  // namespace RadonFramework::IO