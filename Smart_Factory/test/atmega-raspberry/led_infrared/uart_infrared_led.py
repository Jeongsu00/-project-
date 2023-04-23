import RPi.GPIO as GPIO
import serial
import time

ser = serial.Serial(port = '/dev/ttyS0',
                    baudrate = 9600,
                    timeout = 1)

infrared = 20
GPIO.setmode(GPIO.BCM)        # setmode를 BCM으로 설정
GPIO.setup(infrared, GPIO.IN) # 적외선 장애물 감지 센서 설정

while 1:
    state = GPIO.input(infrared)

    t = time.localtime()
    print(f"{t.tm_hour}:{t.tm_min}:{t.tm_sec} : {state}")

    if (state == 1):
        ser.write(b'h')
        print("h")
    elif (state == 0):
        ser.write(b'l')
        print("l")
