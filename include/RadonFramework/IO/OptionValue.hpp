#pragma once

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::IO
{
class OptionValue
{
public:
  OptionValue();
  OptionValue(const OptionValue& Copy);
  OptionValue(const RF_Type::String& Value);

  OptionValue& operator=(const OptionValue& Other);
  OptionValue& operator=(const RF_Type::String& Value);

  void Set();
  RF_Type::Bool IsSet() const;
  const RF_Type::String& Value() const;

protected:
  RF_Type::String m_Value;
  RF_Type::Bool m_ValueSet;

private:
  RF_Type::UInt8 Padding[31];
};

}  // namespace RadonFramework::IO