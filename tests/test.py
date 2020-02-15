import time
import board
import busio
import adafruit_bmp3xx


# NOTE: ENSURE RUNNING THIS SCRIPT WITH PYTHON v3! 
i2c = busio.I2C(board.SCL, board.SDA)
bmp = adafruit_bmp3xx.BMP3XX_I2C(i2c)

print(bmp.pressure)
print(bmp.temperature)
