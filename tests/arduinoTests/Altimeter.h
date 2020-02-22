#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#include <Arduino.h> //needed for Serial.println
#include <string.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

#define SEALEVELPRESSURE_HPA (1021)
//Adafruit_BMP3XX theBmp(BMP_CS); // hardware SPI
//Adafruit_BMP3XX theBmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

class Altimeter
{
public:
  bool isSetup;
  
  void SetupAltimeter();
  float GetPressureHpa();
  float GetAltitudeMeters(float seaLevelPressureHpa);
  float GetTemperatureCelsius();
  void AltimeterDebug();
private:
  Adafruit_BMP3XX theBmp;
};
