#include <pigpio.h>
#include "bmp3.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using std::cout;

void InitializeAltimeter()
{
	struct bmp3_dev dev;
	int8_t rslt = BMP3_OK;
	
	dev.dev_id = BMP3_12C_ADDR_PRIM;
}

int main(int argc, char* argv[])
{
	if (gpioInitialise() >= 0)
	{
		//i2cOpen();
		
	}
}
