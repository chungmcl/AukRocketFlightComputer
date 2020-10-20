#include "groundStation.h"

void setup() 
{
    radio = Radio::GetInstance();
}

void loop() 
{
    float receivedDataBuffer[4];
    if (radio->Receive(receivedDataBuffer)) 
    {
        Serial.println(receivedDataBuffer[0]);
        Serial.println(receivedDataBuffer[1]);
        Serial.println(receivedDataBuffer[2]);
        Serial.println(receivedDataBuffer[3]);
        Serial.println();
    }
}
