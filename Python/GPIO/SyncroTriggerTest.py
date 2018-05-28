import RPi.GPIO as GPIO
import time

LEFT_READY= 17
LEFT_BUSY = 18
RIGHT_READY= 22
RIGHT_BUSY = 23
TRIGGER =27

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(LEFT_READY, GPIO.IN)
GPIO.setup(LEFT_BUSY ,GPIO.IN)
GPIO.setup(RIGHT_READY, GPIO.IN)
GPIO.setup(RIGHT_BUSY ,GPIO.IN)
GPIO.setup(TRIGGER, GPIO.OUT)

print('LEFT OFFLINE - BUSY and READY are False')
while not GPIO.input(LEFT_READY) and not GPIO.input(LEFT_BUSY):
    pass
print('RIGHT OFFLINE - BUSY and READY are False')
while not GPIO.input(RIGHT_READY) and not GPIO.input(RIGHT_BUSY):
    pass
print("Initiating")
while True:
    print('waiting on READY')
    while True:
        if GPIO.input(LEFT_READY) and not GPIO.input(LEFT_BUSY) and GPIO.input(RIGHT_READY) and not GPIO.input(RIGHT_BUSY):
            break;
    print('Trigger')
    GPIO.output(TRIGGER,True)
    while  GPIO.input(LEFT_READY) or GPIO.input(RIGHT_READY):
        pass;
    print('Dropping Trigger')
    GPIO.output(TRIGGER,False)