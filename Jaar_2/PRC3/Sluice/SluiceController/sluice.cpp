#include "sluice.h"

Sluice::Sluice(int portNumber, VALVETYPE type)
{  
  bool debug = false;
  QString url = "ws://localhost:" + QString::number(portNumber);
  sluiceCommunicator = new Client(QUrl(url), debug);

  //TODO:
  //
  //Connect buttons
  //

  sluiceDoors[0] = SluiceDoor(portNumber, type);
  sluiceDoors[1] = SluiceDoor(portNumber, type);
}

Sluice::~Sluice()
{
  delete sluiceCommunicator;
}

void Sluice::OpenButtonPressed()
{
    HandleEvent(Open);
}

void Sluice::CloseButtonPressed()
{
    HandleEvent(Close);
}

void Sluice::StopButtonPressed()
{
    HandleEvent(Stop);
}


void Sluice::HandleEvent(EVENT evt)
{
    std::cout << "Sluice eventhandler: "<<  evt << std::endl;

  switch (evt)
  {
    case Open:
      {
        sluiceDoors[0].Openup();
        sluiceDoors[1].Openup();
        break;
      }
    case Close:
      {
        sluiceDoors[0].Closeup();
        sluiceDoors[1].Closeup();
        break;
      }
    case Stop:
      {
        sluiceDoors[0].StopActions();
        sluiceDoors[1].StopActions();
        break;
      }
    default:
      break;
  }

}

