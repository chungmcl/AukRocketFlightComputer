#include "Altimeter.h"
#include "Orientation.h"

// Pointer to singleton altimeter instance
Altimeter* altimeter;
Orientation* orientation;

void setup() 
{
    // delay(Time before systems are activated for safety and power saving);

    // Get pointer to singleton instance of Altimeter and Orientation
    altimeter = Altimeter::GetInstance();
    orientation = Orientation::GetInstance();

    // Set charge activation pin outputs to OUTPUT mode
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
}

void loop() 
{
    //altimeter->AltimeterDebug();
    orientation->OrientationDebug();
    delay(100);
}
