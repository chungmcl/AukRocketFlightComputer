#include "Altimeter.h"

// Pointer to singleton altimeter instance
Altimeter* altimeter;

void setup() 
{
  // Get pointer to singleton instance of altimeter
  altimeter = Altimeter::GetInstance();

  // Set charge activation pin outputs to OUTPUT mode
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() 
{
  altimeter->AltimeterDebug();
}
