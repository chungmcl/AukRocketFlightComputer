#include "Radio.h"

Radio* Radio::instance = 0;

// Empty constructor for singleton pattern
Radio::Radio()
{}

// Destructor for deleting instance to prevent memory leaks
Radio::~Radio()
{
    delete instance;
    delete theRadio;
}

// Get singleton instance of Radio
Radio* Radio::GetInstance()
{
    if (instance == 0)
    {
        instance = new Radio();
        instance->SetupRadio();
    }

    return instance;
}

// Begin setup of Radio class
void Radio::SetupRadio() 
{
    theRadio = new RH_RF69(RFM69_CS, RFM69_INT);
    packetNumber = 0;
    
    //pinMode(LED, OUTPUT);     
    pinMode(RFM69_RST, OUTPUT);
    digitalWrite(RFM69_RST, LOW);
 
    // manual reset
    digitalWrite(RFM69_RST, HIGH);
    delay(10);
    digitalWrite(RFM69_RST, LOW);
    delay(10);


     if (!theRadio->init()) {
        Serial.println("RFM69 radio init failed");
        while (1);
      }
      Serial.println("RFM69 radio init OK!");
      
      // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
      // No encryption
      if (!theRadio->setFrequency(RF69_FREQ)) {
        Serial.println("setFrequency failed");
      }
     
      // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
      // ishighpowermodule flag set like this:
      theRadio->setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW
}

// dataList:
// dataList[0] = altitude
// dataList[1] = orientationX
// dataList[2] = orientationY
// dataList[3] = orientationZ
#define FLOAT_BYTE_COUNT 4
void Radio::TransmitData(float* dataList, int dataListSize) 
{
    
    int radioPacketLength = dataListSize * FLOAT_BYTE_COUNT;
    uint8_t radioPacket[radioPacketLength];

    for (int i = 0; i < dataListSize; i++) 
    {
        uint8_t* current = reinterpret_cast<uint8_t*>(dataList + i);
        for (int j = 0; j < FLOAT_BYTE_COUNT; j++) 
        {
            radioPacket[(i * FLOAT_BYTE_COUNT) + j] = *(current + j);
        }
    }
  
    // Send the message
    theRadio->send((uint8_t*)radioPacket, radioPacketLength);
    theRadio->waitPacketSent();
    Serial.println("Sent data");
}
