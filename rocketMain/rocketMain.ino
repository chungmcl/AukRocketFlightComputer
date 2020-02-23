#include "Altimeter.h"

// Pointer to singleton altimeter instance
Altimeter* altimeter = Altimeter::GetInstance();

void setup() 
{
  // put your setup code here, to run once:
  altimeter->SetupAltimeter();

  // Set charge activation pin outputs to OUTPUT mode
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() 
{
  altimeter->AltimeterDebug();
}
