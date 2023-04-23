#define F_CPU 16000000L
#include <avr/io.h> // include the AVR IO library
#include <util/delay.h> // include the delay library
#include "../ServoDriver/pca9685.h" // include the PCA9685 

#define servo1 (uint8_t)0
#define servo2 (uint8_t)1
#define servo3 (uint8_t)2
#define servo4 (uint8_t)3
#define servo5 (uint8_t)4

#define min_angle (uint16_t)600
#define test_angle (uint16_t)2400
#define max_angle (uint16_t)2400

// LED (상태등)
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED1 PB0
#define LED2 PB1

// 스위치
#define switch1 PB2

#define SERVO_A(x) (uint8_t)(x - 1)		// SERVO_A(1) = 0, 1, 2, 3, 4
#define SERVO_B(x) (uint8_t)(x + 7)		// SERVO_B(1) = 5, 6, 7, 8, 9

// pulse
#define ANGLE(x) (uint16_t)((10 * x) + 600)		// 600 ~ 2400

#define servo_max 10

uint16_t move_Aarm_coord[9][servo_max][3] = {
	{
		{1, 90, 120}, {1, 120, 90}, {2, 90, 120}, {2, 120, 90}, {3, 90, 120}, {3, 120, 90}, {4, 90, 180}, {4, 180, 90}, {5, 45, 0}, {5, 0, 45}
	}
};


void INIT_SERVO();
// 서보모터 움직이기
void MoveServo(uint8_t, uint16_t, uint16_t);
// 로봇암 쉽게 움직이기
void MoveRobotArm(uint8_t, uint8_t);

int main(void)
{
	LED_DDR |= (1 << LED1) | (1 << LED2);
	//LED_PORT |= (1 << LED2);
	
	//pca9685_init(0x00, 50); // start PCA9685 device 0x00 at 50 Hz output

	//LED_PORT |= (1 << LED1);
	_delay_ms(5);
	
	//uint16_t angle = 0;
	_delay_ms(1000);

	INIT_SERVO();

	while (1) {
		LED_PORT |= (1 << LED1);
		//INIT_SERVO();
		
		//MoveRobotArm(1, 0);
		
		//MoveServo(SERVO_A(1), ANGLE(90), ANGLE(70));
		//_delay_ms(100);
		//MoveServo(SERVO_A(1), ANGLE(70), ANGLE(90));
		//_delay_ms(100);
		
		int i;
		for (i = 1; i <= 4; i++) {
			MoveServo(SERVO_A(i), ANGLE(90), ANGLE(70));
			_delay_ms(100);
			MoveServo(SERVO_A(i), ANGLE(71), ANGLE(90));
			_delay_ms(100);
		}
		MoveServo(SERVO_A(5), ANGLE(45), ANGLE(0));
		_delay_ms(100);
		MoveServo(SERVO_A(5), ANGLE(0), ANGLE(45));
		_delay_ms(100);
		
		_delay_ms(5000);
		
		for (i = 1; i <= 5; i++) {
			MoveServo(SERVO_B(i), ANGLE(90), ANGLE(70));
			_delay_ms(100);
			MoveServo(SERVO_B(i), ANGLE(71), ANGLE(90));
			_delay_ms(100);
		}
		
		_delay_ms(5000);
		
		//for (i = 2; i <= 3; i++) {
			//MoveServo(SERVO_B(i), ANGLE(0), ANGLE(180));
			//_delay_ms(100);
			//MoveServo(SERVO_B(i), ANGLE(180), ANGLE(0));
			//_delay_ms(100);
		//}
		
		//MoveServo(SERVO_B(1), ANGLE(120), ANGLE(75));
		//_delay_ms(100);
		//MoveServo(SERVO_B(1), ANGLE(75), ANGLE(120));
		//_delay_ms(100);
		
		//MoveServo(SERVO_B(1), ANGLE(90), ANGLE(120));
		//MoveServo(SERVO_B(1), ANGLE(120), ANGLE(90));
		//_delay_ms(500);
		
		//MoveServo(SERVO_A(5), ANGLE(45), ANGLE(0));
		//MoveServo(SERVO_A(5), ANGLE(0), ANGLE(45));
		//_delay_ms(500);

		//pca9685_pwm(SERVO_B(3), ANGLE(100));
		
		LED_PORT &= ~(1 << LED1);
		
	}
	return 0;
}

void INIT_SERVO() {

	pca9685_init(0x00, 50); // start PCA9685 device 0x00 at 50 Hz output
	int i;

	for (i = 1; i <= 4; i++){
		pca9685_pwm(SERVO_A(i), ANGLE(90));
		pca9685_pwm(SERVO_B(i), ANGLE(90));
		_delay_ms(20);
	}

	pca9685_pwm(SERVO_A(5), ANGLE(45));
	pca9685_pwm(SERVO_B(3), ANGLE(130));
	pca9685_pwm(SERVO_B(5), ANGLE(90));
	_delay_ms(200);
}

void MoveServo(uint8_t servo, uint16_t start_angle, uint16_t end_angle) {
	int angle;

	if (start_angle <= end_angle) {
		for (angle = start_angle; angle <= end_angle; ) {
			if (PINB & (1 << switch1)) {
				PORTB &= ~0x02;
				pca9685_pwm(servo, angle);
				angle += 10;
			}
			else {
				PORTB |= 0x02;
				break;
			}
			_delay_ms(15);
		}
	}
	
	else {
		for (angle = start_angle; angle >= end_angle; ) {
			if (PINB & (1 << switch1)) {
				PORTB &= ~0x02;
				pca9685_pwm(servo, angle);
				angle -= 10;
			}
			else {
				PORTB |= 0x02;
				break;
			}
			_delay_ms(15);
		}
	}

	_delay_ms(100);
}

void MoveRobotArm(uint8_t servo, uint8_t count) {
	
	int i;
	
	switch (servo){
		case 1:
		PORTB |= (1 << LED2);
		for(i = 0; i < servo_max; i++){
			MoveServo(SERVO_A(move_Aarm_coord[count][i][0]), ANGLE(move_Aarm_coord[count][i][1]), ANGLE(move_Aarm_coord[count][i][2]));
		}
		break;
		//case 2:
		//for(i = 0; i < servo_max; i++){
		//MoveServo(SERVO_B(move_Barm_coord[count][i][0]), ANGLE(move_Barm_coord[count][i][1]), ANGLE(move_Barm_coord[count][i][2]));
		//break;
		//}
	}
	
}