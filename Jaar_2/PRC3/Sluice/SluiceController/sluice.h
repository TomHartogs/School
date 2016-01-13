#pragma once

#include "client.h"
#include "state_enum.h"
#include "sluicedoor.h"
#include <iostream>

class Sluice
{
public:
  Sluice(int portNumber, VALVETYPE type);
  ~Sluice();
  void StopButtonPressed();

public slots:
  void OpenButtonPressed();
  void CloseButtonPressed();
  void stopButtonPressed();

private:
  Client* sluiceCommunicator;
  SluiceDoor sluiceDoors[2];

  void HandleEvent(EVENT evt);
};
