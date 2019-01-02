#include "RadonFramework/IO/StringStyle.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/Drawing/Color/Converter.hpp"

namespace RadonFramework::IO{

class StringStyle::StyleCommand
{
public:
  StyleCommand() : Next(nullptr) {}
  void (*Command)(const StyleCommand& Cmd);
  RF_Type::String Text;
  RF_Type::UInt8 R, G, B;
  StyleCommand* Next;
  void operator()()
  {
    if(Next)
    {
      (*Next)();
    }
    Command(*this);
  }
};

StringStyle::StringStyle():m_Commands(nullptr) {}

StringStyle& StringStyle::RGB(RF_Color::RGB Color,
                              RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  cmd->R = Color.R;
  cmd->G = Color.G;
  cmd->B = Color.B;
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Hex(RF_Type::UInt32 RGB, RF_Type::Bool Forground)
{
  return *this;
}

StringStyle& StringStyle::HSL(RF_Color::HSL Color,
                              RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  auto rgb = RF_Color::HSLConverter::ToColor(Color);
  cmd->R = rgb.R;
  cmd->G = rgb.G;
  cmd->B = rgb.B;
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::HSV(RF_Color::HSV Color,
                              RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  auto rgb = RF_Color::HSVConverter::ToColor(Color);
  cmd->R = rgb.R;
  cmd->G = rgb.G;
  cmd->B = rgb.B;
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::HWB(RF_Color::HWB Color,
                              RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  auto rgb = RF_Color::HWBConverter::ToColor(Color);
  cmd->R = rgb.R;
  cmd->G = rgb.G;
  cmd->B = rgb.B;
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(Cmd.R, Cmd.G, Cmd.B);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Bold()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Bold);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Bold(const RF_Type::String& Text)
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Bold);
    RF_SysConsole::Write(Cmd.Text);
    RF_SysConsole::ResetModifier(RF_SysConsole::Modifiers::Bold);
  };
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Italic()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Italic);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Italic(const RF_Type::String& Text)
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Italic);
    RF_SysConsole::Write(Cmd.Text);
    RF_SysConsole::ResetModifier(RF_SysConsole::Modifiers::Italic);
  };
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Underline()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Underline);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Underline(const RF_Type::String& Text)
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Underline);
    RF_SysConsole::Write(Cmd.Text);
    RF_SysConsole::ResetModifier(RF_SysConsole::Modifiers::Underline);
  };
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Strikethrough()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Strikethrough);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Strikethrough(const RF_Type::String& Text)
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Strikethrough);
    RF_SysConsole::Write(Cmd.Text);
    RF_SysConsole::ResetModifier(RF_SysConsole::Modifiers::Strikethrough);
  };
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Reset()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Reset);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Dim()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Dim);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Dim(const RF_Type::String& Text)
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Dim);
    RF_SysConsole::Write(Cmd.Text);
    RF_SysConsole::ResetModifier(RF_SysConsole::Modifiers::Dim);
  };
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Hidden()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Hidden);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Visible()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::ResetModifier(RF_SysConsole::Modifiers::Hidden);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Inverse()
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Inverse);
  };
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Inverse(const RF_Type::String& Text)
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::SetModifier(RF_SysConsole::Modifiers::Inverse);
    RF_SysConsole::Write(Cmd.Text);
    RF_SysConsole::ResetModifier(RF_SysConsole::Modifiers::Inverse);
  };
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Black(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 0, 0);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 0, 0);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Black(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if (Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 0, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 0, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }  
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Red(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 0, 0);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 0, 0);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Red(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 0, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 0, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Green(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 255, 0);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 255, 0);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Green(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 255, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 255, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Yellow(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 255, 0);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 255, 0);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Yellow(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 255, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 255, 0);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Blue(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 0, 255);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 0, 255);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Blue(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 0, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 0, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Magenta(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 0, 255);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 0, 255);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Magenta(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 0, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 0, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Cyan(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 255, 255);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 255, 255);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Cyan(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(0, 255, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(0, 255, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::White(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 255, 255);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 255, 255);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::White(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 255, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 255, 255);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Gray(RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(127, 127, 127);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(127, 127, 127);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle&
StringStyle::Gray(const RF_Type::String& Text, RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(127, 127, 127);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetForgroundColor();
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(127, 127, 127);
      RF_SysConsole::Write(Cmd.Text);
      RF_SysConsole::ResetBackgroundColor();
    };
  }
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Text(const RF_Type::String& Text)
{
  auto* cmd = new StyleCommand();
  cmd->Command = [](const StyleCommand& Cmd) {
    RF_SysConsole::Write(Cmd.Text);
  };
  cmd->Text = Text;
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Gradient(const RF_Color::Gradient& Gradient,
                                   RF_Type::Bool Forground)
{
  auto* cmd = new StyleCommand();
  if(Forground)
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetForgroundColor(255, 255, 255);
    };
  }
  else
  {
    cmd->Command = [](const StyleCommand& Cmd) {
      RF_SysConsole::SetBackgroundColor(255, 255, 255);
    };
  }
  cmd->Next = m_Commands;
  m_Commands = cmd;
  return *this;
}

StringStyle& StringStyle::Gradient(const RF_Color::Gradient& Gradient,
                                   const RF_Type::String& Text,
                                   RF_Type::Bool Forground)
{
  for (auto i= 0; i< Text.Length(); ++i)
  {
    auto* cmd = new StyleCommand();
    auto rgb = Gradient.ComputeAt(i/RF_Type::Float32(Text.Length()));
    cmd->R = rgb.R;
    cmd->G = rgb.G;
    cmd->B = rgb.B;

    if(Forground)
    {
      cmd->Command = [](const StyleCommand& Cmd) {
        RF_SysConsole::SetForgroundColor(Cmd.R, Cmd.G, Cmd.B);
        RF_SysConsole::Write(Cmd.Text);
        RF_SysConsole::ResetForgroundColor();
      };
    }
    else
    {
      cmd->Command = [](const StyleCommand& Cmd) {
        RF_SysConsole::SetBackgroundColor(Cmd.R, Cmd.G, Cmd.B);
        RF_SysConsole::Write(Cmd.Text);
        RF_SysConsole::ResetBackgroundColor();
      };
    }
    cmd->Text = Text.SubString(i,1);
    cmd->Next = m_Commands;
    m_Commands = cmd;
  }
  return *this;
}

void StringStyle::ToString() const
{
  (*m_Commands)();
}



}