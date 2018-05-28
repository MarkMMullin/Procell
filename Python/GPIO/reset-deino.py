import RPi.GPIO as GPIO
import time
READY= 17
BUSY = 18
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(READY, GPIO.OUT)
GPIO.setup(BUSY ,GPIO.OUT)

GPIO.output(BUSY,False)
GPIO.output(READY,False)