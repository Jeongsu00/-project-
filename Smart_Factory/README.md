# smartfactory

**팀원**  
장하현 : [github](https://github.com/ndg5778/smartfactory)  
김요한 : [github](https://github.com/kimyohan12/yolov5)  
김현민 :   
하정수 : [github](https://github.com/jungsu00/KoreaVCEC-project-)  


## 프로젝트 설명
객체인식 기술을 활용하여 물체 감지 시스템을 구축하고 해당 물체를 분류하는 서비스.

### 사용 부품
Raspberry pi4 B+, ATmega328p

### 사용 언어
C, Python

### 사용 서비스
Ubuntu(ver 22.10), YOLOv5, MySQL, Server, OpenCV, PyTorch, Database, Flask

## 프로젝트 실행
> ATmega328p (Atmel studio7) : [SmartFactory.c](https://github.com/ndg5778/smartfactory/blob/main/project/Atmega328p/SmartFactory.c)  

> Raspberry pi (ubuntu) : [project_detect.py](https://github.com/ndg5778/smartfactory/blob/main/project/raspberry%20pi/project_detect.py)  
> 실행 방법  
>   
> > 1. pytorch 다운로드  
> > 2. yolov5 다운로드  
> > 3. pymysql 다운로드  
> > ```sql
> > -- database = blog  
> > -- table = project로 생성  
> > 	create table project(  
> > 	id int(11) NOT NULL AUTO_INCREMENT,  
> > 	name varchar(40) NOT NULL,  
> > 	number int(11) NOT NULL,  
> > 	number1 int(11) NOT NULL,  
> > 	PRIMARY KEY(id));
> >  ```  
> >		
> > 4. Raspi Searial 연결 상태여야 함  
> > ``` python
> > port = '/dev/ttyAMA0'   # Raspi Searial port  
> > baudrate = 9600         # 보드 레이트 (통신 속도)  
> >```
> > 5. STK500을 사용하여 Atmega328P와 연결하여 Atmel studio사용  
> > 6. 명령어를 입력하여 실행  
> > ``` bash
> >python3 project_detect.py --weights project_best.pt --source 0 --conf 0.8
> > ```

## 프로젝트 설명

### 작동 원리
```
1) 로봇팔 초기화
- 로봇팔을 구동하기 전 초기화해준다.
 
2) Raspberry pi에서 몇 개의 상자를 옮겼는지 UART로 전송
- Raspberry pi에 있는 적외선센서가 인식되지 않고, 첫 번째 로봇팔이 움직일 준비가 되었다는 UART를 신호를 주면 값을 전송
- 분류한 상자의 개수를 ATmega328p에 UART로 전송.

3) ATmega328p에 UART로 받은 숫자
- 숫자가 0~8사이이면 5)로 진행.
- 숫자가 9이면(분류 할 상자가 더 이상 없으면) 프로그램 종료.

4) RobotArm1은 4)숫자+1번째 좌표의 상자를 컨테이너 위로 옮김
- 분류한 상자의 개수의 다음 상자를 집고 컨테이너에 옮김.
• 2라는 숫자가 들어왔으면 3번째 상자를 분류해야함.

5) 첫 번째 적외선 센서가 인식되었는지
- 첫 번재 적외선 센서가 인식되었는지 확인.
- 첫 번째 로봇팔이 컨베이어 벨트위에 올려놓았는지 확인.
- 컨베이어 벨트 위에 물체가 인식되면 7)로 진행.
- 20초간 적외선 센서가 인식되지 않으면 3)으로 돌아감.

6) conveyor belt 실행
- 첫 번째 로봇팔이 물체를 컨베이어 벨트 위에 올렸다면 컨베이어 벨트를 움직인다.
- 적외선 센서 두 개 모두 인식이 되지 않는다면 UART통신으로 ATmega328p에게 움직이라고 명령을 내림. 

7) 두 번째 적외선 센서가 인식되었는지
- 두 번째 적외선 센서가 인식되면 두 번째 로봇팔 근처에 도착했다는 것이므로 ATmega328p에게 멈추라는 신호를 UART로 전송.

8) 물체가 어떤 것인지 분류
- 두 번째 적외선센서 근처에 있는 카메라로 해당 물체의 색이 무엇인지 판단.
• 기존에 YOLOv5로 학습한 데이터를 통하여 컨베이어벨트 위에 멈춘 물체를 인식한다.

9) 분류한 물체를 DB에 저장
- 8)에서 분류한 물체를 토대로 DB에 저장.
- 해당 색 column에 1씩 증가시킴.
- DB가 업데이트 되면 웹에도 업데이트됨.

10) ATmega328p에게 DB내용 전달
- 두 번째 로봇팔에게 uart통신으로 무슨색이 몇 번째 인식되었는지 전달.

11) RobotArm2 분류
- 전달받은 내용으로 분류를 함.
- 분류가 끝나면 다시 2)로 이동.
```

### 구상도
**3d**  
 <img src="https://user-images.githubusercontent.com/59169163/229063158-934f780b-331e-455a-809a-951c7ca5834b.png" height="300"/>
 
**실제**  
<img src="https://user-images.githubusercontent.com/59169163/229066496-133101b7-13c9-4372-bb42-395a0974ad29.png" height="300"/>
<img src="https://user-images.githubusercontent.com/59169163/229066660-7727c91e-51d7-46d5-83c0-925ed4704f30.png" height="300"/>

**객체인식**  
<img src="https://user-images.githubusercontent.com/59169163/229067948-42227783-1b6b-4f29-bb21-922c2918c9cb.png" height="300">

### 구성도
**S/W**  
    <img src="https://user-images.githubusercontent.com/59169163/229060300-42bbb8e3-132b-49b3-b5f2-5add2ffcfd16.png" height="300"/>
    
**H/W**  
    <img src="https://user-images.githubusercontent.com/59169163/229060430-85ce3756-1e72-45da-8411-32ecb7ccba81.png" height="300"/>

### 블럭도  
<img src="https://user-images.githubusercontent.com/59169163/230075271-e4704ec9-908d-49bc-808f-eaa8d5d6a7bd.png" height="600"/>


### 회로도
![image](https://user-images.githubusercontent.com/59169163/229057838-493aee0e-893c-4f02-8198-be8c051c9ad6.png)
