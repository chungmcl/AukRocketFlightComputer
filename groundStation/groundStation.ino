#include <SPI.h>
#include <RH_RF69.h>

// UNO or Feather 328P w/wing
  #define RFM69_INT     3  // 
  #define RFM69_CS      4  //
  #define RFM69_RST     2  // "A"
  #define LED           13

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);
// Define frequency
#define RF69_FREQ 900.0

void setup() 
{
    Serial.begin(115200);
    pinMode(RFM69_RST, OUTPUT);
    digitalWrite(RFM69_RST, LOW);

    // manual reset
    digitalWrite(RFM69_RST, HIGH);
    delay(10);
    digitalWrite(RFM69_RST, LOW);
    delay(10);
  
    if (!rf69.init()) 
    {
        Serial.println("RFM69 radio init failed");
        while (1);
    }
    
    Serial.println("RFM69 radio init OK!");
  
    if (!rf69.setFrequency(RF69_FREQ)) 
    {
        Serial.println("setFrequency failed");
    }

    // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
    // ishighpowermodule flag set like this:
    rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW
  
    pinMode(LED, OUTPUT);

    Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}

void loop() 
{
 if (rf69.available()) 
    {
        // Should be a message for us now   
        uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        // len is updated to be true length of buf in .recv()
        if (rf69.recv(buf, &len)) 
        {
            PrintReceivedData(buf, len);
        } 
        else 
        {
            Serial.println("Receive failed");
        }
    }
}

// Expect EXPECTED_FLOAT_COUNT floats that contain this data:
// [0] = altitude, [1] = orientation.x, [2] = orientation.y, [3] = orientation.z
#define EXPECTED_FLOAT_COUNT 4
#define FLOAT_BYTE_SIZE 4
void PrintReceivedData(uint8_t buf[], uint8_t len) 
{
    if (!len) { return; }

    Serial.println("Data: Altitude, Orientation.X, Orientation.Y, Orientation.Z");
    if (len == EXPECTED_FLOAT_COUNT * FLOAT_BYTE_SIZE)
    {
        for (int i = 0; i < EXPECTED_FLOAT_COUNT * FLOAT_BYTE_SIZE; i+= FLOAT_BYTE_SIZE)
        {
            float f;
            uint8_t b[] = { buf[i], buf[i+1], buf[i+2], buf[i+3] };
            memcpy(&f, &b, sizeof(f));
            Serial.println(f);
        }
    }
    Serial.println();   
}
