#include "Altimeter.h"

Altimeter altimeter;

void setup() {
  // put your setup code here, to run once:
  altimeter.SetupAltimeter();
}

void loop() {
  // put your main code here, to run repeatedly:
  altimeter.AltimeterDebug();
}
