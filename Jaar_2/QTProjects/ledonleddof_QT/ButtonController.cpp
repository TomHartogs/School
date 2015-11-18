#include <iostream>
#include "ButtonController.h"


ButtonController::ButtonController(Led& theLed, Button& theButton) :
  myLed(theLed), myButton(theButton)
{

  state = BcStateOff;

  // qt adaptions, attach to button signals
   mytimer = new QTimer(this);
   connect(&myButton, SIGNAL(buttonpressed(Button&)), this, SLOT(buttonPressed(Button&)));
   connect(mytimer, SIGNAL(timeout()), this, SLOT(timerElapsed()));
   connect(&myLed ,SIGNAL(valueChanged()) ,this, SLOT(valueChanged()));
}

void ButtonController::buttonPressed(Button& b)
{
    HandleEvent(BCEvtButtonPressed);
}
void ButtonController::timerElapsed()
{
    HandleEvent(BCEvtTimerElapsed);
}
void ButtonController::valueChanged()
{
    std::cout << "Mode/Value changed" << std::endl;
}
void ButtonController::beActive()
{
  /*if (mytimer.Elapsed())
    HandleEvent(BCEvtTimerElapsed);
  if (myButton.IsPressed())
    HandleEvent(BCEvtButtonPressed);
    */
}

void ButtonController::HandleEvent(BUTTONCONTROLLEREVENT evt)
{
    std::cout << "Controller eventhandler: "<<  evt << std::endl;

  switch (state)
  {
    case BcStateBlinking:
      {
        if (evt == BCEvtButtonPressed)
        {
          mytimer->start(5000);
          myLed.On();
          state = BcStateWaiting;
        }
        break;
      }
    case BcStateWaiting:
      {
        if (evt == BCEvtTimerElapsed)
        {
          myLed.Off();
          state = BcStateOff;
          mytimer->stop();
        }
        break;
      }
    case BcStateOff:
      {
        if (evt == BCEvtButtonPressed)
        {
          myLed.Blink(3);
          state = BcStateBlinking;
        }
        break;
      }
    default:
      break;
  }

}





