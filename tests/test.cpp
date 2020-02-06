#include <pigpio.h>
#include <iostream>

int main(int argc, char* argv[])
{
	if (gpioInitialise() >= 0)
	{
		while (1)
		{        		
			//gpioSetMode(23, 1);
			gpioWrite(23, 1);
			std::cout << "finish";
			getchar();
			gpioWrite(23, 0);
			getchar();
		}
	}
}

