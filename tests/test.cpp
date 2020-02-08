#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
using std::cout;

void Switch(int gpioIdNumber, int milliseconds)
{
	while (true)
	{
		gpioWrite(gpioIdNumber, 1);
		//std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		gpioWrite(gpioIdNumber, 0);
		//std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
}

int main(int argc, char* argv[])
{
	if (gpioInitialise() >= 0)
	{
		std::thread redThread(Switch, 12, 1000);
		std::thread greenThread(Switch, 23, 750);
		std::thread blueThread(Switch, 18, 500);
	}
}
