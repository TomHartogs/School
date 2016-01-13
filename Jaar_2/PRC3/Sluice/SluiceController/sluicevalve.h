#pragma once

#include "state_enum.h"
#include "client.h"
#include <QObject>

class SluiceValve
{

private:
  STATE state;
  Client* sluiceCommunicator;

public:
  SluiceValve(int portNumber);
  virtual void Open();
  virtual void Close();
};
