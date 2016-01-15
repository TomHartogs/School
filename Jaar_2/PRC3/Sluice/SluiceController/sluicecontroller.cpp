#include "sluicecontroller.h"

SluiceController::SluiceController()
{
  Sluices.push_back(new Sluice(5555, Normal));
  //Sluices.push_back(new Sluice(5556, Normal));
  //Sluices.push_back(new Sluice(5557, Normal)); //Should be damaged
  //Sluices.push_back(new Sluice(5558, OneSecond));
}

SluiceController::~SluiceController()
{
  for(int i = 0; i < Sluices.size(); i++)
    delete Sluices[i];
}

void SluiceController::SchutSluice(int SluiceNumber)
{
   Sluices[SluiceNumber]->Schut();
}

void SluiceController::StopButtonPressed()
{

}

