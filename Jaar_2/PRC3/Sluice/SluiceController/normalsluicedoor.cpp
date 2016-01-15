#include "normalsluicedoor.h"

NormalSluiceDoor::NormalSluiceDoor(SIDE side, Client* clientPtr)
  :SluiceDoor(side, clientPtr)
{

}

void NormalSluiceDoor::waterLevelChanged(WATER_LEVEL waterLevel)
{
  if((_side == LEFT && waterLevel == low) || (_side == RIGHT && waterLevel == high))
  {
    _sluiceCommunicator->sendMessage(_startOfMessage + "open");
    //emit StopUpdating();
  }
  else if(_side == RIGHT)
  {
    switch(waterLevel)
    {
      case aboveValve2:
      {
        _middle->Open();
        break;
      }
      case aboveValve3:
      {
        _middle->Open();
        _top->Open();
        break;
      }
      case low:
      case belowValve2:
      case high:
        break;
    }
  }
}

void NormalSluiceDoor::HandleEvent(EVENT event)
{
  DOOR_STATE state = GetState();
  switch(state)
  {
    case doorLocked:
    case doorClosed:
    {
      if(event == Open || _rememberEvent == Open)
      {
        WATER_LEVEL waterLevel = GetWaterLevel();
        if((_side == LEFT && waterLevel == low) || (_side == RIGHT && waterLevel == high))
        {
          _sluiceCommunicator->sendMessage(_startOfMessage + "open");
          //emit StopUpdating();
        }
        else
        {
          if(_side == LEFT)
          {
            _bottom->Open();
            _middle->Open();
            _top->Open();
          }
          else
            _bottom->Open();
          emit StartUpdating();
        }
        if(_rememberEvent != Open)
          _rememberEvent = Open;
        else
           _rememberEvent = Stop;
      }
      else if(event == Close)
      {
            _bottom->Close();
            _middle->Close();
            _top->Close();
      }
      break;
    }
    case doorOpen:
    {
      if(event == Close || _rememberEvent == Close)
      {
        _sluiceCommunicator->sendMessage(_startOfMessage + "close");
        _bottom->Close();
        _middle->Close();
        _top->Close();
        Lock();
        if(_rememberEvent != Close)
          _rememberEvent = Close;
        else
           _rememberEvent = Stop;
      }
      break;
    }
    case doorClosing:
    case doorOpening:
    {
      if(event == Stop)
        _sluiceCommunicator->sendMessage(_startOfMessage + "stop");
      break;
    }
    case motorDamage:
    {
      qDebug() << "MotorFailure";
      break;
    }
    case doorStopping:
    {
      HandleEvent(event);
      break;
    }
  }
}
