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
int8_t setNormalMode(struct bmp3_dev *dev)
{
    int8_t rslt;
    /* Used to select the settings user needs to change */
    uint16_t settings_sel;

    /* Select the pressure and temperature sensor to be enabled */
    dev->settings.press_en = BMP3_ENABLE;
    dev->settings.temp_en = BMP3_ENABLE;
    /* Select the output data rate and oversampling settings for pressure and temperature */
    dev->settings.odr_filter.press_os = BMP3_NO_OVERSAMPLING;
    dev->settings.odr_filter.temp_os = BMP3_NO_OVERSAMPLING;
    dev->settings.odr_filter.odr = BMP3_ODR_200_HZ;
    /* Assign the settings which needs to be set in the sensor */
    settings_sel = BMP3_PRESS_EN_SEL | BMP3_TEMP_EN_SEL | BMP3_PRESS_OS_SEL | BMP3_TEMP_OS_SEL | BMP3_ODR_SEL;
    rslt = bmp3_set_sensor_settings(settings_sel, dev);

    /* Set the power mode to normal mode */
    dev->settings.op_mode = BMP3_NORMAL_MODE;
    rslt = bmp3_set_op_mode(dev);

    return rslt;
}

// The i2c handle
static unsigned pigpioHandle;

static int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) 
{
	return i2cReadByteData(pigpioHandle, reg_addr); 
	/* Read from registers using I2C. Return 0 for a successful execution. */
    uint16_t count = 0;
    int res;
    while (count < 0x32) 
    {
		res = i2cReadByteData(pigpioHandle, (reg_addr + count));
		if (res < 0) 
       {
			printf("*** ERROR in i2c_reg_read %d\n", res);
			return 1;
		}
		else
		{
			printf("%d", (uint8_t)(res & 0xff));
			printf(" ");
			printf("%d\n", reg_addr + count);
		}
		reg_data[count] = (uint8_t)(res & 0xff);
		count++;
   }
   return i2cReadByteData(pigpioHandle, reg_addr);
}

static int8_t i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) 
{
    return (int8_t)i2cWriteByteData(pigpioHandle, reg_addr, *reg_data);
}

static void delay_msec(uint32_t ms)
{
	int signedMs = ms;
    std::this_thread::sleep_for(std::chrono::milliseconds(signedMs));
}

void Debug(int8_t rslt)
{
		switch (rslt)
		{
			case BMP3_OK:
				printf("OK\n");
				break;
			case BMP3_E_NULL_PTR:
				printf("NULL PTR\n");
				break;
			case BMP3_E_DEV_NOT_FOUND:
				printf("DEV NOT FOUND\n");
				break;
			case BMP3_E_INVALID_ODR_OSR_SETTINGS:
				printf("INVALID ODR OSR SETTINGS\n");
				break;
			case BMP3_E_CMD_EXEC_FAILED:
				printf("CMD EXEC FAILED\n");
				break;
			case BMP3_E_CONFIGURATION_ERR:
				printf("CONFIGURATION ERROR\n");
				break;
			case BMP3_E_INVALID_LEN:
				printf("INVALID LENGTH\n");
				break;
			case BMP3_E_COMM_FAIL:
				printf("COMM FAIL\n");
				break;
			case BMP3_E_FIFO_WATERMARK_NOT_REACHED:
				printf("FIFO WATERMARK NOT REACHED\n");
				break;
			default:
				printf("NO FAILURE CODE\n");
				break;
		}
}


int main(int argc, char* argv[])
{
	// Initialise the pigpio library and ensure it is running
	if (gpioInitialise() >= 0)
	{
		// i2cOpen(i2c bus 1, altimeter uses register BMP3_I2C_ADDR_SEC, flags should be 0 according to pigpio docs)
		pigpioHandle = i2cOpen(1, BMP3_I2C_ADDR_SEC, 0);
	
		struct bmp3_dev dev;
		int8_t rslt = BMP3_OK;

		dev.dev_id = BMP3_I2C_ADDR_PRIM;
		dev.intf = BMP3_I2C_INTF;
	
		// Connect
		dev.read = &i2c_read;
		dev.write = &i2c_write;
		dev.delay_ms = &delay_msec;
		
		rslt = bmp3_init(&dev);
		printf("Finished initialization of dev\n");
		Debug(rslt);

		int8_t setNormalModeResult = setNormalMode(&dev);
		printf("Finished setting normal mode\n");
		Debug(setNormalModeResult);
		
		get_sensor_data(&dev);
		
		i2cClose(pigpioHandle);
	}
}