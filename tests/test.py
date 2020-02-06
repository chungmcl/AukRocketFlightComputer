import RPi.GPIO as GPIO
import time

pinNumber = 23
sleepInterval = 0.5

def Setup():
        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)
        GPIO.setup(pinNumber,GPIO.OUT)

Setup()
while (True):
    time.sleep(sleepInterval)
    print("LED ON")
    GPIO.output(pinNumber, GPIO.HIGH)
    time.sleep(sleepInterval)
    print("LED OFF")
    GPIO.output(23,GPIO.LOW)
    
    

