#include "water.h"

Water::Water(Client* clientPtr)
  :_sluiceCommunicator(clientPtr)
{
  _checkLevelTimer = new QTimer(this);
  connect(_checkLevelTimer, SIGNAL(timeout()), this, SLOT(update()));
}

WATER_LEVEL Water::GetWaterLevel()
{
  QString valveStatusRequest = "GetWaterLevel";
  QString valveStatusReply = _sluiceCommunicator->sendMessage(valveStatusRequest);
  if(QString::compare(valveStatusReply, "low", Qt::CaseSensitive))
    return low;
  else if(QString::compare(valveStatusReply, "belowValve2", Qt::CaseSensitive) == 0)
    return belowValve2;
  else if(QString::compare(valveStatusReply, "aboveValve2", Qt::CaseSensitive) == 0)
    return aboveValve2;
  else if(QString::compare(valveStatusReply, "aboveValve3", Qt::CaseSensitive) == 0)
    return aboveValve3;
  else if(QString::compare(valveStatusReply, "high", Qt::CaseSensitive) == 0)
    return high;
}

void Water::StartUpdating()
{
  _lastLevel = GetWaterLevel();
  _checkLevelTimer->start(500);
}

void Water::StopUpdating()
{
  _checkLevelTimer->stop();
}

void Water::update()
{
  WATER_LEVEL currentLevel = GetWaterLevel();
  //if(currentLevel != _lastLevel)
  //{
   // _lastLevel = currentLevel;
    emit levelChanged(currentLevel);
  //}
}
