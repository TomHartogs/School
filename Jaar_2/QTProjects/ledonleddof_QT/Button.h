#ifndef Button_H
#define Button_H
#include <QObject>
#include <QTimer>
//#include "Timer.h"

#define POLLTIME 10


class Button: public QObject {

  Q_OBJECT

  public:


  public slots:
       void timerElapsed();
  signals:
       void buttonpressed(Button&);

  public:
    Button(int inputpin);
    void beActive();
    bool IsPressed();
    
  private:
    int inputpin;
    QTimer* mytimer;
    //Timer mytimer;
    bool readButtonHardware();


    enum  BUTTONSTATE
    {
      ButtonStatePressed,
      ButtonStateReleased,
      ButtonStateDebouncing
    };
    enum BUTTONEVENT
    {
      ButtonEvtTimerElapsed
    };
    BUTTONSTATE state;

    void HandleEvent(BUTTONEVENT evt);
    bool buttonIsPressed;
};

#endif
