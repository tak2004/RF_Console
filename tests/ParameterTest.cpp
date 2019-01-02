#include <RadonFramework/Radon.hpp>
#include <RadonFramework/IO/Parameter.hpp>
#include <RadonFramework/IO/LogConsole.hpp>
#include <RadonFramework/IO/StandardRuleChecker.hpp>

enum ApplicationOptions
{
  ApplicationDirectory,
  Destination,
  DisableColorOutput,
  MAX
};

int main(int argc, const char** argv)
{
  RadonFramework::Radon framework;
  RF_IO::Log::AddAppender(
      RF_Mem::AutoPointer<RF_Diag::Appender>(new RF_IO::LogConsole()));

  RF_Mem::AutoPointerArray<RF_IO::OptionRule> rules(
      new RF_IO::OptionRule[ApplicationOptions::MAX], ApplicationOptions::MAX);
  rules[ApplicationOptions::ApplicationDirectory].Init(
      0, 0, RF_IO::StandardRuleChecker::Text, 0, RF_IO::OptionRule::Required);
  rules[ApplicationOptions::Destination].Init(
      "-d", "--destination", RF_IO::StandardRuleChecker::Text,
      "Output directory", RF_IO::OptionRule::Required);
  rules[ApplicationOptions::DisableColorOutput].Init(
      nullptr, "--nocolor", nullptr, "Disable color output",
      RF_IO::OptionRule::Optional);

  RF_IO::Parameter parameters;
  parameters.ParsingWithLogging(argv, argc, rules);
  if(parameters.Values()[ApplicationOptions::DisableColorOutput].IsSet())
  {
    RF_IO::LogInfo("Disable color output.");
  }

  RF_Thread::ThreadPool::Global().DisableAndWaitTillDone();
  return 0;
}