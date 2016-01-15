#pragma once

#include "sluicedoor.h"

class NormalSluiceDoor : public SluiceDoor
{  
public:
  NormalSluiceDoor(SIDE side, Client* clientPtr);
  void waterLevelChanged(WATER_LEVEL waterLevel);
  void HandleEvent(EVENT state);
};
