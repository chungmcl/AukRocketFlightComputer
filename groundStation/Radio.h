#ifndef RADIO_H
#define RADIO_H

#include <SPI.h>
#include <RH_RF69.h>

// UNO or Feather 328P w/wing
  #define RFM69_INT     3  // 
  #define RFM69_CS      4  //
  #define RFM69_RST     2  // "A"

// Define frequency
#define RF69_FREQ 915.0

class Radio
{
public:
    bool isSetup;

    static Radio* GetInstance();

    // Expect EXPECTED_FLOAT_COUNT floats that contain this data:
    // [0] = altitude, [1] = orientation.x, [2] = orientation.y, [3] = orientation.z
    void Receive(float* returnData);
    ~Radio();

private:
    static Radio* instance;

    // Radio driver is instantiated as a singleton instance in SetupRadio()
    RH_RF69* theRadio;

    Radio();
    void SetupRadio();
};

#endif
