#include <string.h>
#include <stdio.h>
#include "stm32l476xx.h"
#include "SysClock.h"
#include "I2C.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "keypad.h"

int main(void){
	
	volatile int i;
	char message[64]="";
	int counter = 0;
	char oneMessage;
	char temp; 
	System_Clock_Init(); // Switch System Clock = 80 MHz
	I2C_GPIO_init();
	I2C_Initialization(I2C1);
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,0);
	ssd1306_WriteString("Meow", Font_16x26, White);
	ssd1306_UpdateScreen();
  delayMs(1000);
	Keypad_Pin_Init();
	while(1){
		for(counter = 0; counter < 3; counter++){
			temp = keypad_scan();
			if(temp == 0xFF){
				delayMs(100);
				continue;
			}
			message[(sizeof(char) * counter)] = keypad_scan();
			delayMs(1000);
		}
		
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2,0);
		ssd1306_WriteString(message, Font_16x26, White);
		ssd1306_UpdateScreen();
		delayMs(1000);
	}

}

