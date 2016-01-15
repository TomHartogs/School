#include "onesecondsluicedoor.h"

OneSecondSluiceDoor::OneSecondSluiceDoor(SIDE side, Client* clientPtr)
  :SluiceDoor(side, clientPtr)
{

}

void OneSecondSluiceDoor::waterLevelChanged(WATER_LEVEL waterLevel)
{}

void OneSecondSluiceDoor::HandleEvent(EVENT event)
{}
