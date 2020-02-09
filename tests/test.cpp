#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using std::cout;

void Switch(int gpioIdNumber, int milliseconds, std::mutex* lock)
{
	while (true)
	{
		lock->lock();
		if (gpioInitialise() >= 0)
		{
			gpioWrite(gpioIdNumber, 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
			gpioWrite(gpioIdNumber, 0);
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
			gpioTerminate();
		}
		lock->unlock();
	}
}

int main(int argc, char* argv[])
{
	std::mutex lock;
	std::thread redThread(Switch, 12, 1000, &lock);
	std::thread greenThread(Switch, 23, 750, &lock);
	std::thread blueThread(Switch, 18, 500, &lock);
		
	redThread.join();
	greenThread.join();
	blueThread.join();
}
