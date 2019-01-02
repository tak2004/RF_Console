#include "RadonFramework/IO/Parameter.hpp"
#include "RadonFramework/IO/Log.hpp"

namespace RadonFramework::IO
{
Bool Parameter::SafeParsingWithErrorOutput(
    const RF_Mem::AutoPointerArray<RF_Type::String>& Parameters,
    const RF_Mem::AutoPointerArray<OptionRule>& Rules,
    RF_Type::String& ErrorMessage)
{
  // reserve memory for values
  RF_Mem::AutoPointerArray<OptionValue> results(Rules.Count());

  RF_Type::Bool matchingValue, matchingParameter;
  RF_Type::UInt32 parameterIndex = 0, parameterOffset = 0;
  RF_Type::String para;
  RF_Type::String value;
  // process all rules
  for(RF_Type::UInt32 i = 0; i < Rules.Count(); ++i)
  {
    // if long and short name are null then only the value check is necessary
    matchingValue = true;

    // if there is only a value then the offset is 0 else 1
    if((Rules[i].LongName != 0 || Rules[i].ShortName != 0) &&
       Rules[i].ValueCheck != 0)
    {
      parameterOffset = 1;
    }
    else
    {
      parameterOffset = 0;
    }

    if(Parameters.Count() > parameterIndex + parameterOffset)
    {
      // If both parameter are null or one of them is unequal null and match the
      // specified name then matchingParameter is true else false.
      if(Rules[i].LongName != 0)
      {
        matchingParameter =
            Parameters[parameterIndex] ==
            RF_Type::String::UnsafeStringCreation(Rules[i].LongName);
        if(Rules[i].ShortName != 0)
          matchingParameter |=
              Parameters[parameterIndex] ==
              RF_Type::String::UnsafeStringCreation(Rules[i].ShortName);
      }
      else
      {
        if(Rules[i].ShortName != 0)
          matchingParameter =
              Parameters[parameterIndex] ==
              RF_Type::String::UnsafeStringCreation(Rules[i].ShortName);
        else
          matchingParameter = true;
      }

      // validate value if possible
      if(Rules[i].ValueCheck != 0)
        matchingValue =
            Rules[i].ValueCheck(Parameters[parameterIndex + parameterOffset]);
    }
    else
    {
      matchingParameter = false;
      matchingValue = false;
    }

    // something was going wrong
    if(!(matchingParameter && matchingValue))
    {
      switch(Rules[i].Availability)
      {
        case OptionRule::Required:  // going crazy
        {
          if(matchingParameter)
          {
            ErrorMessage = RF_Type::String::Format(
                RF_Type::String("Can't parse '%s', expected '%s' or '%s'."),
                Parameters[parameterIndex].c_str(), Rules[i].LongName,
                Rules[i].ShortName);
          }
          else
          {
            ErrorMessage = RF_Type::String("Not enough parameters!");
          }
          return false;
        }
        case OptionRule::Optional:  // don't care check the next one
          continue;
      }
    }

    if(Rules[i].ValueCheck != 0)
      results[i] =
          Parameters[parameterIndex + parameterOffset];  // parameter with value
    else
      results[i].Set();  // flag

    parameterIndex += (1 + parameterOffset);
  }

  if(parameterIndex != Parameters.Count())
  {
    ErrorMessage = "Unexpected parameter count.";
    return false;
  }

  m_Values.Swap(results);
  return true;
}

Bool Parameter::SafeParsingWithLogging(
    const RF_Mem::AutoPointerArray<RF_Type::String>& Parameters,
    const RF_Mem::AutoPointerArray<OptionRule>& Rules)
{
  RF_Type::String errMsg;
  if(!SafeParsingWithErrorOutput(Parameters, Rules, errMsg))
  {
    LogFatalError("%s", errMsg.c_str());
    return false;
  }
  return true;
}

const RF_Mem::AutoPointerArray<OptionValue>& Parameter::Values()
{
  return m_Values;
}

RF_Type::Bool
Parameter::ParsingWithLogging(const char* argv[],
                              int argc,
                              const RF_Mem::AutoPointerArray<OptionRule>& Rules)
{
  RF_Mem::AutoPointerArray<RF_Type::String> param(argc);
  for(UInt32 i = 0; i < argc; ++i)
  {
    param[i] = RF_Type::String::UnsafeStringCreation(
        argv[i], RF_Core::DataManagment::UnmanagedInstance);
  }

  return SafeParsingWithLogging(param, Rules);
}

RF_Type::Bool Parameter::ParsingWithErrorOutput(
    const char* argv[],
    int argc,
    const RF_Mem::AutoPointerArray<OptionRule>& Rules,
    RF_Type::String& ErrorMessage)
{
  RF_Mem::AutoPointerArray<RF_Type::String> param(argc);
  for(UInt32 i = 0; i < argc; ++i)
  {
    param[i] = RF_Type::String::UnsafeStringCreation(
        argv[i], RF_Core::DataManagment::UnmanagedInstance);
  }

  return SafeParsingWithErrorOutput(param, Rules, ErrorMessage);
}

}  // namespace RadonFramework::IO