#pragma once

namespace RadonFramework::IO::ConsoleUI
{

struct Component;

struct ComponentOperator
{
  virtual void operator()(Component& Receiver) = 0;
};

}

namespace RF_CUI = RadonFramework::IO::ConsoleUI;