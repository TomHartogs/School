#pragma once

#include "valve.h"

class NormalValve : public Valve
{
public:
  NormalValve(Client* clientPtr, POS position, SIDE side);
  ~NormalValve();
  void Open();
  void Close();
};

