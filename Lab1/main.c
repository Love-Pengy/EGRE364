#include "stm32l476xx.h"
#include "SysClock.h"

// PA.5  <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN    5
#define BUTTON_PIN 13
int eligChange = 1; 

int main(void){

System_Clock_Init(); // Switch System Clock = 80 MHz
// Enable the clock to GPIO Port A
RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

 // Enable the clock to GPIO Port C
RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  


//Program the port A mode register (MODER) to set Pin 5 as output, as calculated in the prelab.
GPIOA->MODER &= ~GPIO_MODER_MODE5;
GPIOA->MODER |= GPIO_MODER_MODE5_0;

//Program GPIOC->MODER to set the mode of Pin PC 13 as input (by default, they are analog).
GPIOC->MODER &= ~GPIO_MODER_MODE13;
GPIOC->MODER |= 0x0;
	
//Program the port A output type register (OTYPER) to set Pin 5 as push-pull
GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
GPIOA->OTYPER |= 0x0;

//Program the port A pull-up/pull-down register (PUPDR) to set Pin 5 as no-pull-up no pull-down.
GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
GPIOA->PUPDR |= 0x0;

//Program GPIOC->PUPDR to set the pull-up/pull-down setting of Pin PC 13 as no pull-up no pull-down
GPIOC->PUPDR &= ~GPIO_PUPDR_PUPD13;
GPIOC->PUPDR |= 0x0;

//Finally, program the port A output data register (ODR) to set the output of Pin 5 to 1 or 0, which enables or disables the LED, respectively.
GPIOA->ODR &= ~GPIO_ODR_OD5;
GPIOA->ODR |= GPIO_ODR_OD5;

 



	while(1){
		while(GPIOC->IDR & GPIO_IDR_IDR_13){
			if(eligChange){
				GPIOA->ODR ^= GPIO_ODR_OD5;
				eligChange = 0;
			}
		}
		eligChange = 1;
	}

}


	
	



