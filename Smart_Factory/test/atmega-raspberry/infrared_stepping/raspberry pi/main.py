import RPi.GPIO as GPIO
import time
import serial

ser = serial.Serial(port = '/dev/ttyS0',
                    baudrate = 9600,
                    timeout = 1)

#
infrared_A = 18
infrared_B = 20
                               
GPIO.setmode(GPIO.BCM)        # setmode를 BCM으로 설정
GPIO.setup(infrared_A, GPIO.IN) # 적외선 장애물 감지 센서 설정
GPIO.setup(infrared_B, GPIO.IN)

stop_receive = 0

while True:
    data = ser.readline().decode('utf-8').strip()
    if (data == "====stepping motor===="):
        print(f"Received data: {data}")
        stop_receive = 1
        while (stop_receive != 0):
            state_A = GPIO.input(infrared_A)
            state_B = GPIO.input(infrared_B)
            if (state_A == 0):
                ser.write(b'mov$')
                print(f"send data A : {state_A}")
                # time.sleep(1)
                stop_receive = 2
            elif (stop_receive == 2 and state_B == 1):
                ser.write(b'mov$')
            elif (state_B == 0):
                ser.write(b'stp$')
                for i in range(10):
                    print(f"send data B : {state_B}")
                stop_receive = 0