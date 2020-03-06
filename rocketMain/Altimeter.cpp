#include "Altimeter.h"

Altimeter* Altimeter::instance = 0;

// Empty constructor for singleton pattern
Altimeter::Altimeter()
{}

// Destructor for deleting instance to prevent memory leaks
Altimeter::~Altimeter()
{
    delete instance;
}

// Get singleton instance of Altimeter
Altimeter* Altimeter::GetInstance()
{
    if (instance == 0)
    {
        instance = new Altimeter();
        instance->SetupAltimeter();
    }

    return instance;
}

// Begin setup of Altimeter class
void Altimeter::SetupAltimeter() 
{
    if (!theBmp.begin()) {
        Serial.println("Could not find a valid BMP3 sensor, check wiring!");
        while (1);
    }
    // *END DEBUG*
    
    isSetup = true;
  
    // Set up oversampling and filter initialization
    // Changed oversampling from 8X to 2X for temperature
    // Change oversampling from 4X to 2X for pressure
    theBmp.setTemperatureOversampling(BMP3_OVERSAMPLING_2X);
    theBmp.setPressureOversampling(BMP3_OVERSAMPLING_2X);
    theBmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    //theBmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

// Get pressure in hPa
float Altimeter::GetPressureHpa()
{
    if (isSetup)
        return theBmp.pressure / 100.0;
}

// Get altitude in Meters
float Altimeter::GetAltitudeMeters(float groundLevelPressureHpa)
{
    if (isSetup)
        return theBmp.readAltitude(groundLevelPressureHpa);
}

// Get temperature in degrees Celsius
float Altimeter::GetTemperatureCelsius()
{
    if (isSetup)
        return theBmp.temperature;
}
