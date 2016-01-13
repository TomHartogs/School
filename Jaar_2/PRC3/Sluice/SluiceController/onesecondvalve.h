#pragma once

#include "sluicevalve.h"

class OneSecondValve: public SluiceValve
{
public:
  OneSecondValve(int portNumber);
  void Open();
  void Close();
};
