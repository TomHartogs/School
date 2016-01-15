#pragma once

#include "sluice.h"
#include <vector>
#include <QObject>

class SluiceController : public QObject
{
  Q_OBJECT
public:
  SluiceController();
  ~SluiceController();
  void StopButtonPressed();
  void SchutSluice(int SluiceNumber);

private:
  std::vector<Sluice*> Sluices;
};

