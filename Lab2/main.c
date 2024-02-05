#include "stm32l476xx.h"
#include "SysClock.h"

// PA.5  <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN    5
#define BUTTON_PIN 13
// Global variable 
int eligChange = 1; 

int main(void){
// Switch System Clock = 80 MHz
System_Clock_Init(); 
	
 // Enable the clock to GPIO Port C
RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  
	
	//Program GPIOC->MODER to set the mode of Pin PC 13 as input (by default, they are analog).
GPIOC->MODER &= ~((uint32_t)0x03FF03FF);
GPIOC->MODER |= ((uint32_t)0x01550155);


//Program the port A output type register (OTYPER) to set Pin 5 as push-pull
GPIOC->OTYPER &= ~((uint32_t)0x0001F1F);
GPIOC->OTYPER |= 0x0;


//Program the port A pull-up/pull-down register (PUPDR) to set Pin 5 as no-pull-up no pull-down.
GPIOC->PUPDR &= ~((uint32_t)0x03FF03FF);
GPIOC->PUPDR |= 0x0;


//Finally, program the port A output data register (ODR) to set the output of Pin 5 to 1 or 0, which enables or disables the LED, respectively.
GPIOC->ODR &= ~((uint32_t)0x00001F1F);
GPIOC->ODR |= ((uint32_t)0x00001F1F);


	while(1){}


	
	

	}

