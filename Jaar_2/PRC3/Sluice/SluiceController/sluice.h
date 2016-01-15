#pragma once

#include "client.h"
#include "enum.h"
#include "sluicedoor.h"
#include "normalsluicedoor.h"
#include "onesecondsluicedoor.h"
#include "water.h"
#include <iostream>

class Sluice: public QObject
{
  Q_OBJECT

public:
  Sluice(int portNumber, DOOR_TYPE type);
  ~Sluice();

  void Schut();
  void StopActions();
  SLUICE_STATE GetState() { return _state; }

private:
  Client* _sluiceCommunicator;
  SluiceDoor* _leftDoor;
  SluiceDoor* _rightDoor;
  SLUICE_STATE _state;
  Water* _water;

  void HandleEvent(EVENT state);
};
