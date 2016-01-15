#include "valve.h"
#include <stdio.h>
Valve::Valve(Client* clientPtr, POS position, SIDE side)
  :_sluiceCommunicator(clientPtr), _position(position), _side(side)
{
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
   _startOfMessage += "Valve";
   switch(position)
    {
     case bottom:
       _startOfMessage += "1";
       break;
     case middle:
       _startOfMessage += "2";
       break;
     case top:
       _startOfMessage += "3";
       break;
    }

   _startOfMessage += ":";
}

VALVE_STATE Valve::GetState()
{
  QString valveStatusRequest = _startOfMessage;
  valveStatusRequest.remove(0, 1);
  valveStatusRequest.remove(valveStatusRequest.size()-1, 1);
  valveStatusRequest.prepend("G");
  valveStatusRequest = _sluiceCommunicator->sendMessage(valveStatusRequest);
  if(QString::compare(valveStatusRequest, "open", Qt::CaseSensitive) == 0)
    return Opened;
  else
    return Closed;
}
