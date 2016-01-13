#include "sluicecontroller.h"

SluiceController::SluiceController()
{
  Sluices[0] = new Sluice(5555, Normal);
  Sluices[1] = new Sluice(5556, Normal);
  Sluices[2] = new Sluice(5558, OneSecond);
}

SluiceController::~SluiceController()
{
  delete Sluices[0];
  delete Sluices[1];
  delete Sluices[2];
}

void SluiceController::StopButtonPressed()
{
  emit stopButtonPressed();
}

