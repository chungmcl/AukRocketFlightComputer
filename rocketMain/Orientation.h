#ifndef ORIENTATION_H
#define ORIENTATION_H

// Library dependencies (Can be found in the "dependencies" subfolder):
// "Adafruit_BNO055"
// "Adafruit_Unified_Sensor"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Orientation
{
public:
    bool isSetup;

    static Orientation* GetInstance();

    // In order to get data from a sensors_event_t,
    // Simply use:
    // sensors_event_t.orientation.x
    // sensors_event_t.orientation.y
    // sensors_evenet_t.orientation.z
    // Data is in degrees.
    sensors_event_t GetEvent();
    ~Orientation();

private:
    static Orientation* instance;
    Adafruit_BNO055 theBno;

    Orientation();
    void SetupOrientation();
};

#endif
