#include <RadonFramework/Core/Common/Assert.hpp>
#include "RadonFramework/System/IO/Console.hpp"

namespace RadonFramework::System::IO::Console
{
void Clear_SystemAPIDispatcher()
{
  Clear = nullptr;
  Dispatch();
  RF_ASSERT(Clear != Clear_SystemAPIDispatcher && Clear != nullptr,
            "Funtion was called and couldn't be dispatched");
  Clear();
}

RF_Type::String ReadLine_SystemAPIDispatcher()
{
  ReadLine = nullptr;
  Dispatch();
  RF_ASSERT(ReadLine != ReadLine_SystemAPIDispatcher && ReadLine != nullptr,
            "Funtion was called and couldn't be dispatched");
  return ReadLine();
}

RF_Type::String ReadSecretLine_SystemAPIDispatcher(
    RF_Type::String (*Callback)(const RF_Type::String&))
{
  ReadSecretLine = nullptr;
  Dispatch();
  RF_ASSERT(ReadSecretLine != ReadSecretLine_SystemAPIDispatcher &&
                ReadSecretLine != nullptr,
            "Funtion was called and couldn't be dispatched");
  return ReadSecretLine(Callback);
}

void WriteLine_SystemAPIDispatcher(const RF_Type::String& Value)
{
  WriteLine = nullptr;
  Dispatch();
  RF_ASSERT(WriteLine != WriteLine_SystemAPIDispatcher && WriteLine != nullptr,
            "Funtion was called and couldn't be dispatched");
  WriteLine(Value);
}

void Write_SystemAPIDispatcher(const RF_Type::String& Value)
{
  Write = nullptr;
  Dispatch();
  RF_ASSERT(Write != Write_SystemAPIDispatcher && Write != nullptr,
            "Funtion was called and couldn't be dispatched");
  Write(Value);
}

void SetForgroundColor_SystemAPIDispatcher(RF_Type::UInt8 R,
                                           RF_Type::UInt8 G,
                                           RF_Type::UInt8 B)
{
  SetForgroundColor = nullptr;
  Dispatch();
  RF_ASSERT(SetForgroundColor != SetForgroundColor_SystemAPIDispatcher &&
                SetForgroundColor != nullptr,
            "Funtion was called and couldn't be dispatched");
  SetForgroundColor(R, G, B);
}

void SetBackgroundColor_SystemAPIDispatcher(RF_Type::UInt8 R,
                                            RF_Type::UInt8 G,
                                            RF_Type::UInt8 B)
{
  SetBackgroundColor = nullptr;
  Dispatch();
  RF_ASSERT(SetBackgroundColor != SetBackgroundColor_SystemAPIDispatcher &&
                SetBackgroundColor != nullptr,
            "Funtion was called and couldn't be dispatched");
  SetBackgroundColor(R, G, B);
}

void SetModifier_SystemAPIDispatcher(RF_SysConsole::Modifiers Modifier)
{
  SetModifier = nullptr;
  Dispatch();
  RF_ASSERT(
      SetModifier != SetModifier_SystemAPIDispatcher && SetModifier != nullptr,
      "Funtion was called and couldn't be dispatched");
  SetModifier(Modifier);
}

void ResetForgroundColor_SystemAPIDispatcher()
{
  ResetForgroundColor = nullptr;
  Dispatch();
  RF_ASSERT(ResetForgroundColor != ResetForgroundColor_SystemAPIDispatcher &&
                ResetForgroundColor != nullptr,
            "Funtion was called and couldn't be dispatched");
  ResetForgroundColor();
}

void ResetBackgroundColor_SystemAPIDispatcher()
{
  ResetBackgroundColor = nullptr;
  Dispatch();
  RF_ASSERT(ResetBackgroundColor != ResetBackgroundColor_SystemAPIDispatcher &&
                ResetBackgroundColor != nullptr,
            "Funtion was called and couldn't be dispatched");
  ResetBackgroundColor();
}

void ResetModifier_SystemAPIDispatcher(RF_SysConsole::Modifiers Modifier)
{
  ResetModifier = nullptr;
  Dispatch();
  RF_ASSERT(ResetModifier != ResetModifier_SystemAPIDispatcher &&
                ResetModifier != nullptr,
            "Funtion was called and couldn't be dispatched");
  ResetModifier(Modifier);
}

ColorLevel GetColorLevelSupport_SystemAPIDispatcher()
{
  GetColorLevelSupport = nullptr;
  Dispatch();
  RF_ASSERT(GetColorLevelSupport != GetColorLevelSupport_SystemAPIDispatcher &&
                GetColorLevelSupport != nullptr,
            "Funtion was called and couldn't be dispatched");
  return GetColorLevelSupport();
}

RF_Collect::Pair<RF_Type::UInt16, RF_Type::UInt16>
GetScreenSize_SystemAPIDispatcher()
{
  GetScreenSize = nullptr;
  Dispatch();
  RF_ASSERT(GetScreenSize != GetScreenSize_SystemAPIDispatcher &&
                GetScreenSize != nullptr,
            "Funtion was called and couldn't be dispatched");
  return GetScreenSize();
}

ClearCallback Clear = Clear_SystemAPIDispatcher;
ReadLineCallback ReadLine = ReadLine_SystemAPIDispatcher;
ReadSecretLineCallback ReadSecretLine = ReadSecretLine_SystemAPIDispatcher;
WriteLineCallback WriteLine = WriteLine_SystemAPIDispatcher;
WriteCallback Write = Write_SystemAPIDispatcher;
SetForgroundColorCallback SetForgroundColor =
    SetForgroundColor_SystemAPIDispatcher;
SetBackgroundColorCallback SetBackgroundColor =
    SetBackgroundColor_SystemAPIDispatcher;
SetModifierCallback SetModifier = SetModifier_SystemAPIDispatcher;
ResetForgroundColorCallback ResetForgroundColor =
    ResetForgroundColor_SystemAPIDispatcher;
ResetBackgroundColorCallback ResetBackgroundColor =
    ResetBackgroundColor_SystemAPIDispatcher;
ResetModifierCallback ResetModifier = ResetModifier_SystemAPIDispatcher;
GetColorLevelSupportCallback GetColorLevelSupport =
    GetColorLevelSupport_SystemAPIDispatcher;
GetScreenSizeCallback GetScreenSize = GetScreenSize_SystemAPIDispatcher;

RF_Type::Bool IsSuccessfullyDispatched()
{
  RF_Type::Bool result = true;
  result = result && Clear != Clear_SystemAPIDispatcher && Clear != nullptr;
  result =
      result && ReadLine != ReadLine_SystemAPIDispatcher && ReadLine != nullptr;
  result = result && ReadSecretLine != ReadSecretLine_SystemAPIDispatcher &&
           ReadSecretLine != nullptr;
  result = result && WriteLine != WriteLine_SystemAPIDispatcher &&
           WriteLine != nullptr;
  result = result && Write != Write_SystemAPIDispatcher && Write != nullptr;
  result = result &&
           SetForgroundColor != SetForgroundColor_SystemAPIDispatcher &&
           SetForgroundColor != nullptr;
  result = result &&
           SetBackgroundColor != SetBackgroundColor_SystemAPIDispatcher &&
           SetBackgroundColor != nullptr;
  result = result && SetModifier != SetModifier_SystemAPIDispatcher &&
           SetModifier != nullptr;
  result = result &&
           ResetForgroundColor != ResetForgroundColor_SystemAPIDispatcher &&
           ResetForgroundColor != nullptr;
  result = result &&
           ResetBackgroundColor != ResetBackgroundColor_SystemAPIDispatcher &&
           ResetBackgroundColor != nullptr;
  result = result && ResetModifier != ResetModifier_SystemAPIDispatcher &&
           ResetModifier != nullptr;
  result = result &&
           GetColorLevelSupport != GetColorLevelSupport_SystemAPIDispatcher &&
           GetColorLevelSupport != nullptr;
  result = result && GetScreenSize != GetScreenSize_SystemAPIDispatcher &&
           GetScreenSize != nullptr;
  return result;
}

void GetNotDispatchedFunctions(RF_Collect::List<RF_Type::String>& Result)
{
  if(Clear == Clear_SystemAPIDispatcher || Clear == nullptr)
    Result.AddLast("Clear"_rfs);
  if(ReadLine == ReadLine_SystemAPIDispatcher || ReadLine == nullptr)
    Result.AddLast("ReadLine"_rfs);
  if(ReadSecretLine == ReadSecretLine_SystemAPIDispatcher ||
     ReadSecretLine == nullptr)
    Result.AddLast("ReadSecretLine"_rfs);
  if(WriteLine == WriteLine_SystemAPIDispatcher || WriteLine == nullptr)
    Result.AddLast("WriteLine"_rfs);
  if(Write == Write_SystemAPIDispatcher || Write == nullptr)
    Result.AddLast("Write"_rfs);
  if(SetForgroundColor == SetForgroundColor_SystemAPIDispatcher ||
     SetForgroundColor == nullptr)
    Result.AddLast("SetForgroundColor"_rfs);
  if(SetBackgroundColor == SetBackgroundColor_SystemAPIDispatcher ||
     SetBackgroundColor == nullptr)
    Result.AddLast("SetBackgroundColor"_rfs);
  if(SetModifier == SetModifier_SystemAPIDispatcher || SetModifier == nullptr)
    Result.AddLast("SetModifier"_rfs);
  if(ResetForgroundColor == ResetForgroundColor_SystemAPIDispatcher ||
     ResetForgroundColor == nullptr)
    Result.AddLast("ResetForgroundColor"_rfs);
  if(ResetBackgroundColor == ResetBackgroundColor_SystemAPIDispatcher ||
     ResetBackgroundColor == nullptr)
    Result.AddLast("ResetBackgroundColor"_rfs);
  if(ResetModifier == ResetModifier_SystemAPIDispatcher ||
     ResetModifier == nullptr)
    Result.AddLast("ResetModifier"_rfs);
  if(GetColorLevelSupport == GetColorLevelSupport_SystemAPIDispatcher ||
     GetColorLevelSupport == nullptr)
    Result.AddLast("GetColorLevelSupport"_rfs);
  if(GetScreenSize == GetScreenSize_SystemAPIDispatcher ||
     GetScreenSize == nullptr)
    Result.AddLast("GetScreenSize"_rfs);
}

}  // namespace RadonFramework::System::IO::Console