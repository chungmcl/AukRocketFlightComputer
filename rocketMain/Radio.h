#ifndef RADIO_H
#define RADIO_H

#include <SPI.h>
#include <RH_RF69.h>

// UNO or Feather 328P w/wing
#if defined (__AVR_ATmega328P__)  // Feather 328P w/wing
  #define RFM69_INT     3  // 
  #define RFM69_CS      4  //
  #define RFM69_RST     2  // "A"
  #define LED           13
#endif

#define RF69_FREQ 915.0


class Radio
{
public:
    bool isSetup;

    static Radio* GetInstance();
    void TransmitData(float* dataList, int dataListSize);
    ~Radio();

private:
    static Radio* instance;

    // Radio driver is instantiated as a singleton instance
    RH_RF69* theRadio;
    int16_t packetNumber;

    Radio();
    void SetupRadio();
};
#endif
