#include <pigpio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	if (gpioInitialise() >= 0)
	{
		//gpioSetMode(23, 1);
		//gpioSetMode(12, 1);
		while (1)
		{        		
			gpioWrite(23, 0);
			gpioWrite(12, 1);
			gpioWrite(18, 0);
			std::cout << "RED";
			getchar();
			gpioWrite(23, 1);
			gpioWrite(12, 0);
			gpioWrite(18, 0);
			std::cout<< "GREEN";
			getchar();
			gpioWrite(23, 0);
			gpioWrite(12, 0);
			gpioWrite(18, 1);
			std::cout << "BLUE";
			getchar();	
		}
	}
}

