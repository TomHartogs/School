#include <QCoreApplication>
#include "ButtonController.h"
#include "Button.h"
#include "Led.h"
int main(int argc, char *argv[])
{
  // the QCoreApplication MUST be instantiated first, othwerise runtime errors!!!!
  //
  QCoreApplication a(argc, argv);

  // Led led2(9);
  // Led led3(11);
  // Led led4(10);

  // Button button1 (6);
  //ButtonController bc(led1,button1);

  Led led1(13);
  //Led led4(10);
  //led4.Blink(2);
  Button b1(' '); // we'll use the space bar as the key for this button
  ButtonController bc(led1,b1);
  return a.exec();
}
