#include "groundStation.h"

void setup() 
{
    radio = Radio::GetInstance();
}

void loop() 
{
    float* receivedData = new float[4];
    radio->Receive(receivedData);
}
