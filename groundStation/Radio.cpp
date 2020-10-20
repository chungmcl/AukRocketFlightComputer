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
    Serial.begin(115200);
    pinMode(RFM69_RST, OUTPUT);
    digitalWrite(RFM69_RST, LOW);

    // manual reset
    digitalWrite(RFM69_RST, HIGH);
    delay(10);
    digitalWrite(RFM69_RST, LOW);
    delay(10);
  
    if (!theRadio->init()) 
    {
        Serial.println("RFM69 radio init failed");
        while (1);
    }
    
    Serial.println("RFM69 radio init OK!");
  
    if (!theRadio->setFrequency(RF69_FREQ)) 
    {
        Serial.println("setFrequency failed");
    }

    // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
    // ishighpowermodule flag set like this:
    theRadio->setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW

    Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");
}

// Expect EXPECTED_FLOAT_COUNT floats that contain this data:
// [0] = altitude, [1] = orientation.x, [2] = orientation.y, [3] = orientation.z
#define EXPECTED_FLOAT_COUNT 4
#define FLOAT_BYTE_SIZE 4
bool Radio::Receive(float* returnData) 
{
    if (theRadio->available()) 
    {
        // Should be a message for us now
        // RH_RF69_MAX_MESSAGE_LEN must be used for recv() to function properly
        uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);

        // len is updated to be true length of buf in .recv()
        if (theRadio->recv(buf, &len)) 
        {
            if (!len) { return false; }
            //Serial.println("Data: Altitude, Orientation.X, Orientation.Y, Orientation.Z");
            
            if (len == EXPECTED_FLOAT_COUNT * FLOAT_BYTE_SIZE)
            {
                // For each float returned
                // (Data is sent/received by splitting a 4 byte float into 4 individual bytes,
                //  stored in a uint8_t array)
                for (int i = 0; i < (EXPECTED_FLOAT_COUNT * FLOAT_BYTE_SIZE); i+= FLOAT_BYTE_SIZE)
                {
                    float f;
                    uint8_t b[] = { buf[i], buf[i+1], buf[i+2], buf[i+3] };

                    // Copy the four individual bytes of the float into f
                    memcpy(&f, &b, sizeof(f));

                    // Load the return buffer with f
                    *(returnData + (i / FLOAT_BYTE_SIZE)) = f;
                }
                return true;
            }
            else 
            {
                Serial.println("UNEXPECTED BUFFER LENGTH");
            }
        } 
        else 
        {
            Serial.println("Receive failed");
        }
    }
    return false;
}
