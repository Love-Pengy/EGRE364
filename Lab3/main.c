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
	char message[8]="";
	volatile int counter = 0;
	volatile char oneMessage;
	volatile char temp; 
	volatile char last;
	char tempMessage[8]="";
	System_Clock_Init(); // Switch System Clock = 80 MHz
	I2C_GPIO_init();
	I2C_Initialization(I2C1);
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,0);
	ssd1306_WriteString("Meow", Font_16x26, White);
	ssd1306_UpdateScreen();
  delayMs(5000);
	Keypad_Pin_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,0);
	ssd1306_UpdateScreen();
	
	while(1){
		
		temp = keypad_scan();
		
		if(temp == 0xFF){
			delayMs(100);
		}
		else{
			if(strlen(message) == 8){
				strcpy(tempMessage, message);
				for(i = 0; i < 8; i++){
					if(i == 0){
						message[i] = temp;
					}
					else{
						message[i] = tempMessage[i];
					}
				}
				delayMs(100);
			}
			else{
			message[(sizeof(char) * counter)] = temp;
			counter++;
			delayMs(100);
			}
		}
		
		//ssd1306_Fill(Black);
		ssd1306_SetCursor(2,0);
		ssd1306_WriteString(message, Font_16x26, White);
		ssd1306_UpdateScreen();
		
	}

}

