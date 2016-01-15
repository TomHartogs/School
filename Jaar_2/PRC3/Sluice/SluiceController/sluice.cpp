#include "sluice.h"
#include <QtCore/QCoreApplication>

Sluice::Sluice(int portNumber, DOOR_TYPE type)
{  
  bool debug = true;
  QString url = "ws://localhost:" + QString::number(portNumber);
  _sluiceCommunicator = new Client(QUrl(url), debug);

  _water = new Water(_sluiceCommunicator);

  switch(type)
  {
    case Normal:
    {
      _leftDoor = new NormalSluiceDoor(LEFT, _sluiceCommunicator);
      _rightDoor = new NormalSluiceDoor(RIGHT, _sluiceCommunicator);
      break;
    }
    case OneSecond:
    {
      _leftDoor = new OneSecondSluiceDoor(LEFT, _sluiceCommunicator);
      _rightDoor = new OneSecondSluiceDoor(RIGHT, _sluiceCommunicator);
      break;
    }
    case Damaged:
      break;
  }
  connect(_water, SIGNAL(levelChanged(WATER_LEVEL)), _leftDoor, SLOT(waterLevelChanged(WATER_LEVEL)));
  connect(_water, SIGNAL(levelChanged(WATER_LEVEL)), _rightDoor, SLOT(waterLevelChanged(WATER_LEVEL)));
  connect(_leftDoor, SIGNAL(StartUpdating()), _water, SLOT(StartUpdating()));
  connect(_leftDoor, SIGNAL(StopUpdating()), _water, SLOT(StopUpdating()));
  connect(_rightDoor, SIGNAL(StartUpdating()), _water, SLOT(StartUpdating()));
  connect(_rightDoor, SIGNAL(StopUpdating()), _water, SLOT(StopUpdating()));
}

Sluice::~Sluice()
{
  delete _sluiceCommunicator;
  delete _leftDoor;
  delete _rightDoor;
}

void Sluice::Schut()
{
  HandleEvent(Open);
}

void Sluice::HandleEvent(EVENT event)
{
  std::cout << "Sluice eventhandler: "<<  event << std::endl;

  switch (event)
  {
    case Open:
      {
        qDebug() << "Opening";
        if(_water->GetWaterLevel() == high)
        {
          _rightDoor->Closeup();
          while(_rightDoor->GetState() != doorClosed)
          {
            QCoreApplication::processEvents();
          }
          _leftDoor->Openup();
        }
        else
        {
          _leftDoor->Closeup();
          while(_leftDoor->GetState() != doorClosed)
          {
            QCoreApplication::processEvents();
          }
          _rightDoor->Openup();
        }
        break;
      }
    case Close:
      {
        break;
      }
    case Stop:
      {
        break;
      }
    default:
      break;
  }

}

