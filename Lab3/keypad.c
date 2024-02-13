//rows are output 
//columns are input
#include "stm32l476xx.h"


void initTimer(void){
    //enable clock for TIM2
    RCC->APB1ENR1 |= (1<<0);
    //set prescaler value for 1000hz (1ms)
    TIM2->PSC = 80000 - 1;
    //set auto reset value to max
    TIM2->ARR = 0xFFFF;
    //reset the counter registers 
    TIM2->EGR |= (1<<0);
    //reset the actual count value | this holds the amoutn of times reset
    TIM2->CNT = 0x0;
    //enable the timer 
    TIM2->CR1 |= (1<<0);
}

//delay assuming clock is set to 80 Mhz
void delayMs(int timeInMs){
    initTimer();
    while(TIM2->CNT < timeInMs){
    }

}



unsigned char keypad_scan(void){
	
	unsigned char key_mapping[4][4] = {'1', '2', '3', 'A', 
																	 '4', '5', '6', 'B', 
																	 '7', '8', '9', 'C', 
																	 '*', '0', '#', 'D'};
	volatile int i = 0;
	int rows[] = {0, 1, 2, 3};
	int cols[] = {4, 10, 11, 12};
	unsigned char key = 0xFF;
	int colPressed = 0;
	
	uint32_t inputMask = 0;
	uint32_t outputMask = 0;
	
	for(i = 0; i < 4; i++){
			inputMask |= 1<<cols[i];
	}
	
	for(i = 0; i < 4; i++){
			outputMask |= 1<<rows[i];
	}
	
	GPIOC->ODR &= ~outputMask;
	delayMs(5);
	
	if((GPIOC->IDR & inputMask) == inputMask){
		return(0xFF);
	}
	
	for(i = 0; i < 4; i++){
		if((GPIOC->IDR & (1<<cols[i])) == 0){
			colPressed = i;
		}
	}
	for(i = 0; i < 4; i++){
		GPIOC->ODR |= outputMask;
		GPIOC->ODR &= ~(1<<rows[i]);
		
		if((GPIOC->ODR & (1<<rows[i])) == 0){
			key = key_mapping[i][colPressed];
		}
		
	}
	return(key);
	
}

void Keypad_Pin_Init(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  
	  GPIOC->MODER &= ~(1|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<10)|(1<<11)|(1<<12));
    GPIOC->MODER |= (0x00000055);
}
