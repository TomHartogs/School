#pragma once

#include "enum.h"
#include "valve.h"
#include "normalvalve.h"
#include "client.h"
#include <iostream>
#include <QObject>
#include <QTimer>

class SluiceDoor: public QObject
{
  Q_OBJECT

  friend class NormalSluiceDoor;
  friend class OneSecondSluiceDoor;

public slots:
    virtual void waterLevelChanged(WATER_LEVEL) = 0;

signals:
  void StartUpdating();
  void StopUpdating();

private:
  Valve* _bottom;
  Valve* _middle;
  Valve* _top;
  Client* _sluiceCommunicator;
  SIDE _side;
  QString _startOfMessage;
  WATER_LEVEL GetWaterLevel();
  EVENT _rememberEvent;
  void Unlock();
  void Lock();
  virtual void HandleEvent(EVENT event) = 0;

public:
  SluiceDoor(SIDE side, Client* clientPtr);
  virtual ~SluiceDoor() = 0;
  void Openup();
  void Closeup();
  void StopActions();
  void ResumeActions();
  DOOR_STATE GetState();
  QString GetTrafficLight();
};
