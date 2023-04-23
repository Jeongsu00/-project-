//#include <avr/io.h>
//#include <util/delay.h>
//#include "uart.h"
//#include "use_UART.h"
//
//// uart
//int uart_index = 0;				// 수신 버퍼에 저장할 위치
//int process_data = 0;		// 문자열 처리
//char buffer[20] = "";		// 수신 데이터 버퍼
//char buffer_data[20];
//char data;					// 수신 데이터
//
//#define TERMINATOR '$'
//
//void uart_RasToAt() {
	//data = UART_receive();	// 데이터 수신
	//if (data != ""){
		//if(data == TERMINATOR) {	// 종료 문자를 수신한 경우
			//buffer[uart_index] = '\0';
			//process_data = 1;		// 수신 문자열 처리 지시
			//uart_index = 0;
		//}
		//else {
			//buffer[uart_index] = data;	// 수신 버퍼에 저장
			//uart_index++;
		//}
	//}
//}
//
//int WhichCanMove(void) {
	//
	//int pass = 0;
	////char temp[20];
	//
	//while (pass == 0){
		////// 로봇팔 움직일 수 있는지 확인
		////UART_printString("====Fisrt Robot Arm====");
		////UART_printString("\n");
		//
		//uart_RasToAt();
		//
		//if(process_data == 1){
			//strcpy(buffer_data, buffer);
			//
			//// 0 ~ 8의 값이 들어오면
			//if ((strcmp(buffer_data, "0") == 0) || (strcmp(buffer_data, "1") == 0) || (strcmp(buffer_data, "2") == 0) || (strcmp(buffer_data, "3") == 0) || (strcmp(buffer_data, "4") == 0) || (strcmp(buffer_data, "5") == 0) || (strcmp(buffer_data, "6") == 0) || (strcmp(buffer_data, "7") == 0) || (strcmp(buffer_data, "8") == 0)) {
				//UART_printString("pass");
				//UART_printString(buffer_data);
				//UART_printString("\n");
				//pass = 1;
				//
				//if ((strcmp(buffer_data, "0") == 0)) return 0;
				//else if ((strcmp(buffer_data, "1") == 0)) return 1;
				//else if ((strcmp(buffer_data, "2") == 0)) return 2;
				//else if ((strcmp(buffer_data, "3") == 0)) return 3;
				//else if ((strcmp(buffer_data, "4") == 0)) return 4;
				//else if ((strcmp(buffer_data, "5") == 0)) return 5;
				//else if ((strcmp(buffer_data, "6") == 0)) return 6;
				//else if ((strcmp(buffer_data, "7") == 0)) return 7;
				//else if ((strcmp(buffer_data, "8") == 0)) return 8;
			//}
			//// 9의 값일 들어오면 (배열이 꽉 찼음)
			//else if (strcmp(buffer_data, "9") == 0) {
				//UART_printString("end");
				//PORTB &= ~(1 << LED1);
				//return 9;
			//}
			//// 다른 값이 들어온다면...
			//else {
				//UART_printString("not a 0 to 9. : ");
			//}
		//}
	//}
	//
	//
	//return 0;
//}
//
