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
    sensors_event_t GetEvent();
    ~Orientation();

private:
    static Orientation* instance;
    Adafruit_BNO055 theBno;

    Orientation();
    void SetupOrientation();
};


#endif
