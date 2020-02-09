#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using std::cout;

class GpioWrapper
{
public:
    GpioWrapper(std::mutex* lock)
    {
        writeLock = lock;
    }
    void GpioWrapper::write(int gpioNumber, int milliseconds)
    {
        writeLock->lock();
        gpioWrite(gpioNumber, milliseconds);
        writeLock->unlock();
    }
private:
    std::mutex* writeLock;
};



void Switch(GpioWrapper* writer, int gpioIdNumber, int milliseconds)
{
	while (true)
	{
        (*writer).write(gpioIdNumber, millseconds);
	}
}

int main(int argc, char* argv[])
{
    std::mutex lock;
    GpioWrapper redGpioWrapper(&lock);
    GpioWrapper blueGpioWrapper(&lock);
    GpioWrapper greenGpioWrapper(&lock);
	if (gpioInitialise() >= 0)
	{
		std::thread redThread(Switch, &redGpioWrapper, 12, 1000);
		std::thread greenThread(Switch, &blueGpioWrapper, 23, 750);
		std::thread blueThread(Switch, &greenGpioWrapper, 18, 500);
	}
}
