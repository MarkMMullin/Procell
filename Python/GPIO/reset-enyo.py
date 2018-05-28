import RPi.GPIO as GPIO
import time
TRIGGER =27
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIGGER, GPIO.OUT)
GPIO.output(TRIGGER,False)