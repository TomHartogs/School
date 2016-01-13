#pragma once

#include "sluice.h"
#include <QObject>

class SluiceController : public QObject
{
  Q_OBJECT
public:
  SluiceController();
  ~SluiceController();
  void StopButtonPressed();

signals:
  void stopButtonPressed();

private:
  Sluice* Sluices[3];
};

