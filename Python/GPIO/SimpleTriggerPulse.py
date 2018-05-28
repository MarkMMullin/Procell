import RPi.GPIO as GPIO
import time

READY= 17
BUSY = 18
TRIGGER =27

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(READY, GPIO.IN)
GPIO.setup(BUSY ,GPIO.IN)
GPIO.setup(TRIGGER, GPIO.OUT)

print('powerup - BUSY and READY are False')
while not GPIO.input(READY) and not GPIO.input(BUSY):
    pass
print('powerup - waiting on READY')
while True:
    if GPIO.input(READY) and not GPIO.input(BUSY):
        break;
print('Trigger')
GPIO.output(TRIGGER,True)
while  GPIO.input(READY):
    pass;
GPIO.output(TRIGGER,False)