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

GPIO.output(READY,True)
GPIO.output(BUSY,False)
print("READY, !BUSY")
x = input("Waiting...")
GPIO.output(READY,False)
GPIO.output(BUSY,True)
print("!READY, BUSY")
x = input("Waiting...")
GPIO.output(READY,True)
GPIO.output(BUSY,True)
print("READY, BUSY")
x = input("Waiting...")
GPIO.output(BUSY, False)
GPIO.output(READY, False)
time.sleep(1)
GPIO.output(BUSY,True)
while True:
    GPIO.output(READY,True)
    time.sleep(3)
    GPIO.output(BUSY,False)

    while not GPIO.input(TRIGGER):
        pass
    print('Triggered')
    GPIO.output(BUSY,True)
    GPIO.output(READY,False)
    time.sleep(5)
    print('pass')