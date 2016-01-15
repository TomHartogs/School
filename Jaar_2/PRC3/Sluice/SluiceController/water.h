#pragma once

#include <QObject>
#include <QTimer>
#include "client.h"
#include "enum.h"

class Water: public QObject
{
  Q_OBJECT

private:
  QTimer* _checkLevelTimer;
  WATER_LEVEL _lastLevel;
  Client* _sluiceCommunicator;

private slots:
  void update();

public slots:
  void StartUpdating();
  void StopUpdating();

signals:
    void levelChanged(WATER_LEVEL currentLevel);

public:
  Water(Client* clientPtr);
  WATER_LEVEL GetWaterLevel();
};
