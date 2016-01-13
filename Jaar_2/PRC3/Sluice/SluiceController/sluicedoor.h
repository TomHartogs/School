#pragma once

#include "state_enum.h"
#include "sluicevalve.h"
#include "onesecondvalve.h"
#include <iostream>
#include <QObject>

class SluiceDoor
{
private:
  STATE state;
   SluiceValve* sluiceValves[3];
   void HandleEvent(EVENT evt);

public:
  SluiceDoor();
  SluiceDoor(int portNumber, VALVETYPE type);
  ~SluiceDoor();
  void Openup();
  void Closeup();
  void StopActions();
  STATE GetState();

public slots:
  void stopButtonPressed();
};
