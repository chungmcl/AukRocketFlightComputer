#include "Altimeter.h"
#include "Orientation.h"
#include "Radio.h"
#include "CircularBuffer.h"
#include "rocketMain.h"

#define GROUNDLEVELPRESSURE_HPA (1006.7)
#define SENSOR_SAMPLE_RATE_MS (1000.00)
#define LAUNCH_DETECTION_ACCELERATION (14.30)

void setup()
{
    // Get pointer to singleton instance of Altimeter and Orientation
    altimeter = Altimeter::GetInstance();
    orientation = Orientation::GetInstance();
    radio = Radio::GetInstance();
    
    Serial.begin(115200);
}

void loop() 
{
    delay((int)SENSOR_SAMPLE_RATE_MS);
    UpdateBuffers();
    sensors_event_t orientationEventData = orientation->GetEvent();

    float currentSensorData[4];
    currentSensorData[0] = altitudeBuffer.first();
    currentSensorData[1] = orientationEventData.orientation.x;
    currentSensorData[2] = orientationEventData.orientation.y;
    currentSensorData[3] = orientationEventData.orientation.z;
    
    radio->TransmitData(currentSensorData, sizeof(currentSensorData) / sizeof(*currentSensorData));
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
    {
        verticalAccelerationBuffer.unshift(
            (verticalVelocityBuffer[0] - verticalVelocityBuffer[1]) / (SENSOR_SAMPLE_RATE_MS / 1000.00)
            );
    }
}

bool DetectLaunch()
{
    if (verticalAccelerationBuffer.first() > LAUNCH_DETECTION_ACCELERATION)
        return true;

    return false;
}
