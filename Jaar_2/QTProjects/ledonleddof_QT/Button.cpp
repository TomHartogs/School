#include "ButtonController.h"
#include "Button.h"
#include <iostream>

Button::Button(int inputpin) :
    inputpin(inputpin), buttonIsPressed(false), state(ButtonStateReleased)
{
    //changed for QT
    //pinMode(inputpin, INPUT);
    // read the spacebar of the keyboard, we ignore inputping
    // changed for QT
    mytimer = new QTimer(this);
    connect(mytimer, SIGNAL(timeout()), this, SLOT(timerElapsed()));
    mytimer->start(10000);

    std::cout << "button constructor \n";
    //mytimer.Start(POLLTIME);
}

bool Button::readButtonHardware()
{
    //return digitalRead(inputpin) == HIGH;
    // inputpint is misused to check for a certain character
    // it will only return true if the key desctribed by the pin is pressed
    // problem with this is that other key presses go down the drain....
    // so when other button class is instantiated it will go wrong
    // but for rhe sake of the example, we leave it here as is..
    // BUT BE WARNED!
    return true;
}

void Button::timerElapsed()
{
    // QT: state machine not needed
    // the OS will debounce button for us.
    // so only read it and emit if necessary.
    if (readButtonHardware())
    {
        std::cout << "button pressed \n";
        emit buttonpressed(*this);
        buttonIsPressed = true;
    }
   // HandleEvent(ButtonEvtTimerElapsed);
}

//
// following code until the end is not use anymore in QT
// it is left here from the arduino code as an example
//
bool Button::IsPressed()
{
    bool retval = buttonIsPressed;
    buttonIsPressed = false;  // only once we return that I'm pressed
    return retval;
}
void Button::beActive() {
    /*if (mytimer.Elapsed())
  {
    HandleEvent(ButtonEvtTimerElapsed);
    mytimer.Start(POLLTIME);
  }
  */
}

// state machine comes here...
void Button::HandleEvent(BUTTONEVENT evt)
{
    switch (state)
    {
    case ButtonStatePressed:
    {
        if (evt == ButtonEvtTimerElapsed)
        {
            if (!readButtonHardware())
            {
                state = ButtonStateReleased;

            }
        }
        break;
    }
    case ButtonStateReleased:
    {
        if (evt == ButtonEvtTimerElapsed)
        {
            if (readButtonHardware())
            {
                state = ButtonStateDebouncing;

            }
        }
        break;
    }
    case ButtonStateDebouncing:
    {
        if (evt == ButtonEvtTimerElapsed)
        {

            if (readButtonHardware())
            {
                state = ButtonStatePressed;
                std::cout << "button pressed "<< evt<< std::endl;
                emit buttonpressed(*this);
                buttonIsPressed = true;
                //Serial.println("button pressed");
            }
            else state = ButtonStateReleased;
        }
        break;
    }
    default:
        break;
    }
}






