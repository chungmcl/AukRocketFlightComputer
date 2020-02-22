#include "Altimeter.h"

Altimeter altimeter;
void setup() 
{
  altimeter.SetupAltimeter();
}

void loop() 
{
  altimeter.AltimeterDebug();
}
