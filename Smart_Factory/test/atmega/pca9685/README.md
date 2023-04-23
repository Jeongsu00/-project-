# PCA9685 사용하기
>출처 : https://github.com/prestonsn/PCA9685-Multi-Channel-Servo-Controller-Driver-for-AVR-ATmega

ATmgea328p로 서보모터 드라이버(pca9685)를 이용하여 서보모터 움직이기
---

``` C
#define F_CPU 16000000L
#include <avr/io.h> // include the AVR IO library
#include <util/delay.h> // include the delay library
#include "pca9685.h" // include the PCA9685 library

int main(void)
{
	pca9685_init(0x00, 50); // start PCA9685 device 0x00 at 50 Hz output
	_delay_ms(5);
	int8_t angle = 0;
	pca9685_servo(0, 0);
	// pca9685_servo(1, 0);
	_delay_ms(1000);

	while (1) {
		//pca9685_servo(1, 0); // set servo0 position to 0 degrees
		for (angle = -90; angle <= 90; angle += 5) {
			pca9685_servo(0, angle);
			//pca9685_servo(1, angle);
			_delay_ms(25);
		}
		for (angle = 90; angle >= -90; angle -= 5) {
			pca9685_servo(0, angle);
			// pca9685_servo(1, angle);
			_delay_ms(25);
		}
	}
	return 0;
}
```
