import RPi.GPIO as GPIO
import time

infrared1 = 20
infrared2 = 21
                               
GPIO.setmode(GPIO.BCM)        # setmode를 BCM으로 설정
GPIO.setup(infrared1, GPIO.IN) # 적외선 장애물 감지 센서 설정
GPIO.setup(infrared2, GPIO.IN) 


while 1:
    state1 = GPIO.input(infrared1)
    state2 = GPIO.input(infrared2)
    
    t = time.localtime()
    print(f"{t.tm_hour}:{t.tm_min}:{t.tm_sec} : ", end=" ")
    print(f"first : {state1}", end=" ")
    print(f"second : {state2}")

    time.sleep(1)