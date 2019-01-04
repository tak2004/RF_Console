#include <RadonFramework/Radon.hpp>
#include <RadonFramework/IO/Console.hpp>
#include <RadonFramework/IO/StringStyle.hpp>
#include <RadonFramework/IO/LogConsole.hpp>

using Style = RF_IO::StringStyle;

int main(int argc, char** argv)
{
  RadonFramework::Radon framework;

  RadonFramework::IO::Console console;
  auto size = console.GetScreenSize();
  RF_Type::String line;
  for (auto i = 0; i < size.First; ++i)
  {
    line += " "_rfs;
  }
  for (auto i = 0; i < size.Second; ++i)
  {
    console.Log(Style().RGB({0, (255.f / size.Second) * i, 0}, false).Text(line).Reset());
  }
  console.Question(Style().Reset().Text("Continue ?"_rfs));
  console.Clear();
  console.Log(Style().Green("Radon Framework\n"_rfs));
  console.Log(Style()
                  .Bold("bold"_rfs)
                  .Dim("dim"_rfs)
                  .Italic("italic"_rfs)
                  .Underline("underline"_rfs)
                  .Inverse("inverse"_rfs)
                  .Strikethrough("strikethrough"_rfs)
                  .Black("black"_rfs)
                  .Red("red"_rfs)
                  .Green("green"_rfs)
                  .Yellow("yellow"_rfs)
                  .Blue("blue"_rfs)
                  .Magenta("magenta"_rfs)
                  .Cyan("cyan"_rfs)
                  .White("white"_rfs)
                  .Gray("gray"_rfs)
                  .Black("bgBlack"_rfs, false)
                  .Black()
                  .Red("bgRed"_rfs, false)
                  .Green("bgGreen"_rfs, false)
                  .Yellow("bgYellow"_rfs, false)
                  .White()
                  .Blue("bgBlue"_rfs, false)
                  .Black()
                  .Magenta("bgMagenta"_rfs, false)
                  .Cyan("bgCyan"_rfs, false)
                  .White("bgWhite"_rfs, false)
                  .RGB({70, 150, 255})
                  .Text("rgb(70,150,255)\n"_rfs));
  auto username = console.Question(Style().Reset().Text("Username: "_rfs));
  RF_Type::String pwd;
  pwd = console.SecretQuestion(
      Style().Reset().Bold("Password: "_rfs), [](const auto& Answer) {
        RF_Type::String result;
        auto& hashService =
            RF_Hash::HashfunctionServiceLocator::Find("SHA512"_rfs);
        if(!RF_Hash::HashfunctionServiceLocator::IsNullService(hashService))
        {
          auto* hashFunction = hashService.Create();
          if(hashFunction)
          {
            hashFunction->Update(Answer.ByteData(), Answer.Size());
            hashFunction->Final();
            result = hashFunction->ToString();
            hashService.Free(hashFunction);
          }
        }
        return result;
      });
  console.Log(Style().Red(pwd + "\n"_rfs));
  console.Log(Style().Gradient({{255, 0, 0, 0.0f}, {0, 0, 255, 1.0f}},
                               "This is a test gradient\n"_rfs));
  
  RF_IO::Log::AddAppender(RF_Mem::AutoPointer<RF_IO::Appender>(new RF_IO::LogConsole()));
  RF_IO::LogInfo("info");
  RF_IO::LogDebug("debug");
  RF_IO::LogError("error");
  RF_IO::LogFatalError("fatal error");

  RF_Thread::ThreadPool::Global().DisableAndWaitTillDone();
  return 0;
}