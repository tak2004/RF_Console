#pragma once

#include <RadonFramework/IO/Appender.hpp>

namespace RadonFramework::IO
{
/** @brief This class relay the log messages to the command line.
 *
 * Usage:
 * RF_Mem::AutoPointer<RF_Diag::Appender> console(new RF_IO::LogConsole);
 * RF_IO::Log::AddAppender(console);
 * RF_IO::LogInfo("Hello world!");
 **/
class LogConsole : public Appender
{
public:
  void WriteInfo(const RF_Type::String& Text) override;
  void WriteError(const RF_Type::String& Text) override;
  void WriteFatalError(const RF_Type::String& Text) override;
  void WriteDebug(const RF_Type::String& Text) override;
};

}  // namespace RadonFramework::IO