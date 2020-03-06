#include "Altimeter.h"
#include "Orientation.h"
#include "CircularBuffer.h"
#include "rocketMain.h"

#define GROUNDLEVELPRESSURE_HPA (1006.7)
#define SENSOR_SAMPLE_RATE_MS (5000.00)
#define LAUNCH_DETECTION_ACCELERATION (14.30)

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

    Serial.begin(115200);
}

void loop() 
{
    delay((int)SENSOR_SAMPLE_RATE_MS);
    
    UpdateBuffers();
    Serial.println(altitudeBuffer.first());
    Serial.println(verticalVelocityBuffer.first());
    Serial.println(verticalAccelerationBuffer.first());
    Serial.println("\n\n");
    if (DetectLaunch())
    {
        digitalWrite(4, HIGH);
        delay(1000);
        digitalWrite(4, LOW);
    }
}

void UpdateBuffers()
{
    if (altitudeBuffer.isFull())
        altitudeBuffer.pop();
    
    altitudeBuffer.unshift((int)altimeter->GetAltitudeMeters(GROUNDLEVELPRESSURE_HPA));

    if (verticalVelocityBuffer.isFull())
        verticalVelocityBuffer.pop();

    if (altitudeBuffer.size() >= 2)
        verticalVelocityBuffer.unshift((altitudeBuffer[0] - altitudeBuffer[1]) / (SENSOR_SAMPLE_RATE_MS / 1000.00));

    if (verticalAccelerationBuffer.isFull())
        verticalAccelerationBuffer.pop();

    if (verticalVelocityBuffer.size() >= 2)
        verticalAccelerationBuffer.unshift((verticalVelocityBuffer[0] - verticalVelocityBuffer[1]) / (SENSOR_SAMPLE_RATE_MS / 1000.00));
}

bool DetectLaunch()
{
    if (verticalAccelerationBuffer.first() > LAUNCH_DETECTION_ACCELERATION)
        return true;

    return false;
}
