#include "sluicevalve.h"
#include <stdio.h>
SluiceValve::SluiceValve(int portNumber)
{
  QString url = "ws://localhost:" + QString::number(portNumber);
  sluiceCommunicator = new Client(QUrl(url), false);
}

void SluiceValve::Close()
{

}

void SluiceValve::Open()
{
  //sluiceCommunicator->sendMessage();
}
