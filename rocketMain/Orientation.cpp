#include "Orientation.h"

Orientation* Orientation::instance = 0;

// Empty constructor for singleton pattern
Orientation::Orientation()
{}

// Destructor for deleting instance to prevent memory leaks
Orientation::~Orientation()
{
    delete instance;
}

// Get singleton instance of Orientation
Orientation* Orientation::GetInstance()
{
    if (instance == 0)
    {
        instance = new Orientation();
        instance->SetupOrientation();
    }

    return instance;
}

// Begin setup of Orientation class
void Orientation::SetupOrientation() 
{
    theBno = Adafruit_BNO055(55);
  
    /* Initialise the sensor */
    if(!theBno.begin())
    { 
        /* There was a problem detecting the BNO055 ... check your connections */
        /* DEBUG - REMOVE ON RELEASE */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        /* END DEBUG */
        while(1);
    }
  
    delay(1000);
    
    theBno.setExtCrystalUse(true);
}

sensors_event_t Orientation::GetEvent()
{
    sensors_event_t event; 
    theBno.getEvent(&event);
    return event;
}
