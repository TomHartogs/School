#include "normalvalve.h"

NormalValve::NormalValve(Client* clientPtr, POS position, SIDE side)
  :Valve(clientPtr, position, side)
{

}

NormalValve::~NormalValve()
{

}

void NormalValve::Open()
{
  QString message = _startOfMessage;
  message += "open";
  _sluiceCommunicator->sendMessage(message);
  _state = Opened;
}

void NormalValve::Close()
{
  QString message = _startOfMessage;
  message += "close";
  _sluiceCommunicator->sendMessage(message);
  _state = Closed;
}

