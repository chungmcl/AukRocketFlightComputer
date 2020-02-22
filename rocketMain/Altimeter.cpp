#include "Altimeter.h"

void Altimeter::SetupAltimeter() 
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("BMP388 test");

  if (!theBmp.begin()) {
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  }
  isSetup = true;
  
  // Set up oversampling and filter initialization
  theBmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  theBmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
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
float Altimeter::GetAltitudeMeters(float seaLevelPressureHpa)
{
  if (isSetup)
    return theBmp.readAltitude(SEALEVELPRESSURE_HPA);
}

float Altimeter::GetTemperatureCelsius()
{
  if (isSetup)
    return theBmp.temperature;
}

void Altimeter::AltimeterDebug() 
{
  if (! theBmp.performReading()) 
  {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(GetTemperatureCelsius());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(GetPressureHpa());
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(GetAltitudeMeters(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}
