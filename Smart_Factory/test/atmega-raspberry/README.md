# uart  

## 1. Raspberry pi4 설정  

### ㄱ. raspbian환경  

1. config.txt파일 들어가기
``` bash
sudo vim /bash/config.txt
```

2. 블루투스 끄는 설정 입력하기 (uart통신할 때 bluetooth를 꺼야함)
``` bash
dtoverlay=disable-bt
```

3. uart 포트 열기
``` bash
dtoverlay=uart0  # 0~6번까지 존재
```

4. raspi-config에서 Debug Console 끄기  
> ㄱ. raspi-config 들어가기
>> ``` bash
>> sudo raspi-config
>> ```
> ㄴ. **3. Interfacing Options** 들어가기  
> ㄷ. **6. Serial** 선택  
> ㄹ. 로그인 쉘 오픈(login shell to be accessible) -> NO,  
> 시리얼포트 하드웨어(serial port hardwore enable) -> YES   

5. reboot
``` bash
sudo reboot
```

6. UART 포트 확인
``` bash
dmesg | grep tty
```

ttyAMA0가 나타나면 uart포트가 열린 것이다.  
단, 간혹 ttyS0만 보이지만 ttyS0으로 uart가 될 때가 있다.  
확인이 필요하면 가장 간단한 실험방법인 putty를 사용하거나 [led](https://github.com/ndg5778/smartfactory/tree/main/test/atmega-raspberry/UART_led)를 이용해보아라
