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
	volatile char previousInput = 0xFF; 
	System_Clock_Init(); // Switch System Clock = 80 MHz
	I2C_GPIO_init();
	I2C_Initialization(I2C1);
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2,0);
	ssd1306_WriteString("BF_EO", Font_16x26, White);
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
			continue;
		}
		else{
			if((previousInput == 0xFF) && (temp == '#')){
				delayMs(100);
				continue;
			}
			if((temp == '#') && (previousInput != 0xFF)){
				temp = previousInput;
			}
			if(strlen(message) >= 7){
				strcpy(tempMessage, message);
				for(i = 0; i < 7; i++){
					if(i == 0){
						message[i] = temp;
					}
					else{
						message[i] = tempMessage[i-1];
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
		previousInput = temp;
		ssd1306_SetCursor(2,0);
		ssd1306_WriteString(message, Font_16x26, White);
		ssd1306_UpdateScreen();
		
	}

}

