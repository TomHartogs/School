#include "Led.h"
#include <iostream>



Led::Led(int pin)
{
    state = LedStateOff;
    LedPin = pin;
    ledHWOff();
    //pinMode(LedPin, OUTPUT); // set hardware off to match te state
    // changed for QT
    mytimer = new QTimer(this);
    connect(mytimer, SIGNAL(timeout()), this, SLOT(timerElapsed()));
    mytimer->start(1000);

    std::cout << "led constructor \n";

}

Led::~Led()
{
   // cleanup all QT stuff
    disconnect(mytimer);
    delete mytimer;
}
void Led::On() {
    HandleEvent (LEDEvtOn);
}

void Led::Off()
{
    HandleEvent (LEDEvtOff);
}

void Led::Blink(float frequency) {

    BlinkTime = (unsigned long) 1000.0 / frequency;
    mytimer->start(BlinkTime);
    HandleEvent (LEDEvtBlink);
}
void Led::ledHWOn()
{
    std::cout << "led: "<< LedPin<<" on\n";
}
void Led::ledHWOff()
{
    std::cout << "led: "<<LedPin<<" off\n";
}

void Led::timerElapsed()
{
    HandleEvent (LEDEvtTimerElapsed);

}

void Led::HandleEvent(LEDEVENT evt)
{
    switch (evt )
    {
    case LEDEvtOn:
    {
        emit valueChanged();
        state = LedStateOn;
        ledHWOn();
        //digitalWrite(LedPin, 1);
        break;
    }
    case LEDEvtOff:
    {
        emit valueChanged();
        state = LedStateOff;
        ledHWOff();
        // digitalWrite(LedPin, 0);
        break;
    }
    case LEDEvtBlink:
    {
        switch (state)
        {
        case LedStateOn:
        case LedStateOff:
        {
            emit valueChanged();
            state = LedStateBlinkOn;
            ledHWOn();
            //mytimer.Start(BlinkTime);
            //  digitalWrite(LedPin, 1);
            break;
        }
        default:
            break;
        }
    }
    case LEDEvtTimerElapsed:
    {
        switch (state)
        {

        case LedStateBlinkOn:
        {
            state = LedStateBlinkOff;
            ledHWOff();

            break;
        }
        case LedStateBlinkOff:
        {
            state = LedStateBlinkOn;
            ledHWOn();

            break;
        }
        default:
            break;
        }
    }
    default:
        break;
    }
}
//
// following code not used anymore with QT
// its here for the sake of the example
//

void Led::beActive()
{
    // here we poll the time, if it is elapsed we will generate an event
    //if (mytimer.Elapsed())
    //{
    //HandleEvent (LEDEvtTimerElapsed);
    //}
}


















