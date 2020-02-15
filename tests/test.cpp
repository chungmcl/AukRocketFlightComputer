#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using std::cout;

int main(int argc, char* argv[])
{
	if (gpioInitialise() >= 0)
	{
		i2cOpen();
		
	}
}
