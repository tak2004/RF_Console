#include "RadonFramework/IO/OptionValue.hpp"

namespace RadonFramework::IO
{
OptionValue::OptionValue() : m_ValueSet(false) {}

OptionValue::OptionValue(const OptionValue& Copy)
{
  *this = Copy;
}

OptionValue::OptionValue(const RF_Type::String& Value)
{
  m_ValueSet = true;
  m_Value = Value;
}

Bool OptionValue::IsSet() const
{
  return m_ValueSet;
}

OptionValue& OptionValue::operator=(const OptionValue& Other)
{
  m_ValueSet = Other.m_ValueSet;
  m_Value = Other.m_Value;
  return *this;
}

OptionValue& OptionValue::operator=(const RF_Type::String& Value)
{
  m_ValueSet = true;
  m_Value = Value;
  return *this;
}

const RF_Type::String& OptionValue::Value() const
{
  return m_Value;
}

void OptionValue::Set()
{
  m_ValueSet = true;
}
}  // namespace RadonFramework::IO
