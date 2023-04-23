#define F_CPU 160000L
#include <avr/io.h> // include the AVR IO library
#include <util/delay.h> // include the delay library
#include "pca9685.h" // include the PCA9685 library

// switch
void INIT_PORT();
// servo
void INIT_SERVO();

int main(void)
{
	INIT_PORT();
	INIT_SERVO();
	
	int8_t angle;
	
	while (1) {
		for (angle = -90; angle <= 90; ) {
			if(PIND & 0x04){
				_delay_ms(5);
			}
			else {
				pca9685_servo(0, angle);
				_delay_ms(200);
				 angle += 5;
			}
		}
	}
	
	return 0;
}


void INIT_PORT()
{
	DDRB = 0x20; // PB5 (디지털 13번 핀) 출력으로 설정
	PORTB = 0x00; // LED는 꺼진 상태에서 시작
	DDRD = 0x00; // 버튼 입력
	PORTD = 0x04; // PD2 (디지털 2번 핀) 풀업 저항 사용
}

// servo
void INIT_SERVO()
{
	pca9685_init(0x00, 50); // start PCA9685 device 0x00 at 50 Hz output
	_delay_ms(5);
	pca9685_servo(0, 0);
	_delay_ms(100);
}
