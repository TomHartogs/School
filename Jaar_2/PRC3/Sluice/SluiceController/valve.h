#pragma once

#include "enum.h"
#include "client.h"
#include <QObject>

class Valve
{
friend class NormalValve;
friend class OneSecondValve;
private:
  VALVE_STATE _state;
  Client* _sluiceCommunicator;
  POS _position;
  SIDE _side;
  QString _startOfMessage;

public:
  Valve(Client* clientPtr, POS position, SIDE side);
  virtual ~Valve() {}
  virtual void Open() = 0;
  virtual void Close() = 0;
  VALVE_STATE GetState();
};
