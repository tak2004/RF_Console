#pragma once

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO
{
struct StandardRuleChecker
{
  static RF_Type::Bool Text(const RF_Type::String& Value)
  {
    return Value != "";
  }

  static RF_Type::Bool Numeric(const RF_Type::String& Value)
  {
    return Value.IsNumber();
  }

  static RF_Type::Bool Boolean(const RF_Type::String& Value)
  {
    return Value.IsBoolean();
  }
};

}  // namespace RadonFramework::IO