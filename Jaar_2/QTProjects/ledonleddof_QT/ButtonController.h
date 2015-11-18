#ifndef ButtonController_H
#define ButtonController_H
#include <QObject>
#include "Led.h"
#include "Button.h"



class ButtonController : public QObject {
    Q_OBJECT

public slots:
    void buttonPressed(Button&);
    void timerElapsed();
    void valueChanged();


  public:
    ButtonController(Led& theled, Button& theButton);
    void beActive();

  private:

    enum  BUTTONCONTROLLERSTATE
    {
      BcStateBlinking,
      BcStateWaiting,
      BcStateOff
    };
    enum BUTTONCONTROLLEREVENT
    {
      BCEvtButtonPressed,
      BCEvtTimerElapsed
    };
    BUTTONCONTROLLERSTATE state;

    void HandleEvent(BUTTONCONTROLLEREVENT evt);

    Led& myLed;
    Button& myButton;
    QTimer* mytimer;

};

#endif
