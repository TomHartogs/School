#include "sluicedoor.h"

SluiceDoor::SluiceDoor()
{
  sluiceValves[0] = new SluiceValve(0000);
  sluiceValves[1] = new SluiceValve(0000);
  sluiceValves[2] = new SluiceValve(0000);
}

SluiceDoor::SluiceDoor(int portNumber, VALVETYPE type)
{
  if(type == Normal)
  {
    sluiceValves[0] = new SluiceValve(portNumber);
    sluiceValves[1] = new SluiceValve(portNumber);
    sluiceValves[2] = new SluiceValve(portNumber);
  }
  else if(type == OneSecond)
  {
      sluiceValves[0] = new OneSecondValve(portNumber);
      sluiceValves[1] = new OneSecondValve(portNumber);
      sluiceValves[2] = new OneSecondValve(portNumber);
  }
  //QObject::connect(sender, SIGNAL(stopButtonPressed()), this, SLOT(StopActions()));
}

SluiceDoor::~SluiceDoor()
{
  delete sluiceValves[0];
  delete sluiceValves[1];
  delete sluiceValves[2];
}

STATE SluiceDoor::GetState() { return state; }

void SluiceDoor::Openup()
{
    HandleEvent(Open);
}

void SluiceDoor::Closeup()
{
    HandleEvent(Close);
}

void SluiceDoor::StopActions()
{
    HandleEvent(Stop);
}

void SluiceDoor::HandleEvent(EVENT evt)
{
    std::cout << "Door eventhandler: "<<  evt << std::endl;

  switch (state)
  {
    case Opened:
      {
        if (evt == Close)
        {
          sluiceValves[0]->Close();
          sluiceValves[1]->Close();
          sluiceValves[2]->Close();
          state = Closing;
        }
        break;
      }
    case Closed:
      {
        if (evt == Open)
        {
            sluiceValves[0]->Open();
            sluiceValves[1]->Open();
            sluiceValves[2]->Open();
            state = Opening;
        }
        break;
      }
    case Opening:
      {
        if (evt == Stop)
        {

        }
        break;
      }
    case Closing:
      {
        if (evt == Stop)
        {

        }
        break;
      }
    default:
      break;
  }

}
