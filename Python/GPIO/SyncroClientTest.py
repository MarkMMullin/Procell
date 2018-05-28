import RPi.GPIO as GPIO
import time
READY= 17
BUSY = 18
TRIGGER =27

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(READY, GPIO.OUT)
GPIO.setup(BUSY ,GPIO.OUT)
GPIO.setup(TRIGGER, GPIO.IN)

GPIO.output(READY,False)
GPIO.output(BUSY,False)
print("OFFLINE: !READY, !BUSY")
x = input("Waiting...")
GPIO.output(READY,True)
GPIO.output(BUSY,True)
print("BLOCKED: READY, BUSY")
x = input("Waiting...")
print("Start free running")
while True:
    GPIO.output(READY,True)
    GPIO.output(BUSY,False)
    print("READY")
    while True:
        x = GPIO.input(TRIGGER)
        if x == 1:
            break
    print("Triggered")
    GPIO.output(BUSY,True)
    GPIO.output(READY,False)
    time.sleep(0.1)
    print("uuid transfer")
    GPIO.output(BUSY,True)
    GPIO.output(READY,True)


