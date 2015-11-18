#ifndef Led_H
#define Led_H
#include <QObject>
#include <QTimer>

//#include "Timer.h"
//#include <Arduino.h>

class Led : public QObject {

    Q_OBJECT

   public slots:
       void timerElapsed();

   signals:
       void valueChanged();

public:
       Led(int pin);
       ~Led();
  void On();
  void Off();
  void Blink(float frequency);
  void beActive(); // must be NON BLOCKING!!!


private:

  enum  LEDSTATE
  {
    LedStateOff,
    LedStateOn,
    LedStateBlinkOn,
    LedStateBlinkOff
  };
  enum LEDEVENT
  {
    LEDEvtOn,
    LEDEvtOff,
    LEDEvtBlink,
    LEDEvtTimerElapsed
  };
  void HandleEvent(LEDEVENT evt);
    void ledHWOn();
    void ledHWOff();

  QTimer* mytimer;
  LEDSTATE state;
  int LedPin;
  int BlinkTime;

};
#endif


