#include "sluicedoor.h"

#include <stdio.h>

SluiceDoor::SluiceDoor(SIDE side, Client* clientPtr)
  : _sluiceCommunicator(clientPtr), _side(side), _rememberEvent(Stop)
{
  _bottom = new NormalValve(_sluiceCommunicator, bottom, _side);
  _middle = new NormalValve(_sluiceCommunicator, middle, _side);
  _top = new NormalValve(_sluiceCommunicator, top, _side);

  _startOfMessage = "SetDoor";
  switch(_side)
   {
     case LEFT:
        _startOfMessage += "Left";
      break;
     case RIGHT:
        _startOfMessage += "Right";
      break;
   }
  _startOfMessage += ":";
}

SluiceDoor::~SluiceDoor()
{
  delete _bottom;
  delete _middle;
  delete _top;
}

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

void SluiceDoor::ResumeActions()
{
  HandleEvent(_rememberEvent);
}

void SluiceDoor::Unlock()
{
  QString sendMessage = _startOfMessage;
  sendMessage.insert(7, "Lock");
  sendMessage += "Off";
  _sluiceCommunicator->sendMessage("SetDoorLockLeft:off");
}

void SluiceDoor::Lock()
{
  QString sendMessage = _startOfMessage;
  sendMessage.insert(7, "Lock");
  sendMessage += "on";
  _sluiceCommunicator->sendMessage(sendMessage);
}

WATER_LEVEL SluiceDoor::GetWaterLevel()
{
  QString valveStatusRequest = "GetWaterLevel";
  QString valveStatusReply = _sluiceCommunicator->sendMessage(valveStatusRequest);
  if(QString::compare(valveStatusReply, "low", Qt::CaseSensitive) == 0)
    return low;
  else if(QString::compare(valveStatusReply, "belowValve2", Qt::CaseSensitive) == 0)
    return belowValve2;
  else if(QString::compare(valveStatusReply, "aboveValve2", Qt::CaseSensitive) == 0)
    return aboveValve2;
  else if(QString::compare(valveStatusReply, "aboveValve3", Qt::CaseSensitive) == 0)
    return aboveValve3;
  else if(QString::compare(valveStatusReply, "high", Qt::CaseSensitive) == 0)
    return high;
  else
    return GetWaterLevel();
}

DOOR_STATE SluiceDoor::GetState()
{
  QString valveStatusRequest = _startOfMessage;
  valveStatusRequest.remove(0, 1);
  valveStatusRequest.remove(valveStatusRequest.size()-1, 1);
  valveStatusRequest.prepend("G");
  valveStatusRequest = _sluiceCommunicator->sendMessage(valveStatusRequest);
  if(QString::compare(valveStatusRequest, "doorLocked", Qt::CaseSensitive) == 0)
    return doorLocked;
  else if(QString::compare(valveStatusRequest, "doorClosed", Qt::CaseSensitive) == 0)
    return doorClosed;
  else if(QString::compare(valveStatusRequest, "doorOpen", Qt::CaseSensitive) == 0)
    return doorOpen;
  else if(QString::compare(valveStatusRequest, "doorClosing", Qt::CaseSensitive) == 0)
    return doorClosing;
  else if(QString::compare(valveStatusRequest, "doorOpening", Qt::CaseSensitive) == 0)
    return doorOpening;
  else if(QString::compare(valveStatusRequest, "doorStopping", Qt::CaseSensitive) == 0)
    return doorStopping;
  else if(QString::compare(valveStatusRequest, "motorDamage", Qt::CaseSensitive) == 0)
    return motorDamage;
  else
    return GetState();
}
