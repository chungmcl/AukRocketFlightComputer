#ifndef ALTIMETER_H
#define ALTIMETER_H

// Library dependencies (Can be found in the "dependencies" subfolder):
// "Adafruit_ADXL343"
// "Adafruit_BMP3XX_Library"
// "Adafruit_Unified_Sensor"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>
#include <Arduino.h> //needed for Serial.println
#include <string.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

//Adafruit_BMP3XX theBmp(BMP_CS); // hardware SPI
//Adafruit_BMP3XX theBmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

// Definition of Altimeter class
// Wrapper class of Adafruit's wrapper class of Bosch's BMP388 Barometer/Thermometer driver code
// Follows singleton pattern
class Altimeter
{
public:
    bool isSetup;

    static Altimeter* GetInstance();
    ~Altimeter();
  
    float GetPressureHpa();
    float GetAltitudeMeters(float groundLevelPressureHpa);
    float GetTemperatureCelsius();
private:
    static Altimeter* instance;
    Adafruit_BMP3XX theBmp;
  
    Altimeter();
    void SetupAltimeter();
};

#endif
