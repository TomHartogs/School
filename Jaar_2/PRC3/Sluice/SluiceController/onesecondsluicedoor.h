#pragma once

#include "sluicedoor.h"

class OneSecondSluiceDoor : public SluiceDoor
{
public:
  OneSecondSluiceDoor(SIDE side, Client* clientPtr);
  void waterLevelChanged(WATER_LEVEL waterLevel);
  void HandleEvent(EVENT event);
};

