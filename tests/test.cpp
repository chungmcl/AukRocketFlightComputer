#include <pigpio.h>
#include "bmp3.h"
#include "bmp3.c"

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
using std::cout;

// Code from BMP388 Driver READ.ME 
int8_t get_sensor_data(struct bmp3_dev *dev)
{
    int8_t rslt;
    /* Variable used to select the sensor component */
    uint8_t sensor_comp;
    /* Variable used to store the compensated data */
    struct bmp3_data data;

    /* Sensor component selection */
    sensor_comp = BMP3_PRESS | BMP3_TEMP;
    /* Temperature and Pressure data are read and stored in the bmp3_data instance */
    rslt = bmp3_get_sensor_data(sensor_comp, &data, dev);

    /* Print the temperature and pressure data */
    printf("Temperature in deg celsius\t Pressure in Pascal\t\n");
	#ifdef BMP3_DOUBLE_PRECISION_COMPENSATION
    printf("%0.2f\t\t %0.2f\t\t\n",data.temperature, data.pressure);
	#else
	/* for fixed point the compensated temperature and pressure output has a multiplication factor of 100 */
    printf("%lld\t\t %llu\t\t\n",data.temperature, data.pressure);
	#endif

    return rslt;
}

// The i2c handle
static unsigned pigpioHandle;

static int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) 
{
    return (int8_t)i2cReadByteData(pigpioHandle, reg_addr);
}

static int8_t i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) 
{
    return (int8_t)i2cWriteByteData(pigpioHandle, reg_addr, *reg_data);
}

static void delay_msec(uint32_t ms){
	int signedMs = ms;
    std::this_thread::sleep_for(std::chrono::milliseconds(signedMs));
}


int main(int argc, char* argv[])
{
	// Initialise the pigpio library and ensure it is running
	if (gpioInitialise() >= 0)
	{
		// i2cOpen(i2c bus 1, altimeter uses register 0x77, flags should be 0 according to pigpio docs)
		pigpioHandle = i2cOpen(1, 0x77, 0);
	
		struct bmp3_dev dev;
		int8_t rslt = BMP3_OK;

		dev.dev_id = BMP3_I2C_ADDR_PRIM;
		dev.intf = BMP3_I2C_INTF;
	
		// Connect
		dev.read = &i2c_read;
		dev.write = &i2c_write;
		dev.delay_ms = &delay_msec;

		rslt = bmp3_init(&dev);

		int setNormalModeResult = set_normal_mode(&dev);
		get_sensor_data(&dev);
	}
}
