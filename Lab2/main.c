#include "stm32l476xx.h"
#include "SysClock.h"
// PA.5  <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN    5
#define BUTTON_PIN 13
// Global variable 


/* if actual timer method doesnt work use this
//time passed is in ms
// this is assuming that clock s 80Mhz therefore one clock is 1.25e-8
void delay(int time){
    for(uint32_t i = 0; i < (uint32_t)(time/(1.25e-8)); i++){
           //eat "cycle" 
        }
}
*/

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
void delay(int timeInMs){
    initTimer();
    while(TIM2->CNT < timeInMs){
    }

}

void assign(uint32_t t){
    //clear 0-4 and 8-12
    GPIOC->ODR &=~((0x001F)|(0x001F<<8));
    //assign 0-4
    GPIOC->ODR |= t & 0x001F;
    //assign 8-12
    GPIOC->ODR |= (t>>5)<<8;
}

uint32_t  valueMap(uint32_t value){
    switch(value){
        case 0x200: 
            return((1<<12));
        case 0x100:
            return((1<<11));
        case 0x080:
            return((1<<10));
        case 0x040:
            return((1<<9));
        case 0x020:
            return((1<<8));
        case 0x10:
            return((1<<4));
        case 0x08:
            return((1<<3));
        case 0x04: 
            return((1<<2));
        case 0x02:
            return((1<<1));
        case 0x01:
            return(1);
        default:
            return(0);
    }
}

uint32_t val = 0x200;
int reverse = 0;
uint32_t val1;
uint32_t val2;
uint32_t val3;
uint32_t val4;
int i = 0;
int k = 0;
int main(void){
    // Switch System Clock = 80 MHz
    System_Clock_Init(); 

    // Enable the clock to GPIO Port C
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  

    //set prescaler to ___

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
   // GPIOC->ODR &= ~((uint32_t)0x00001F1F);
    //GPIOC->ODR |= ((uint32_t)0x00001F1F);



    while(1){				
        if(reverse){
            val1 =  (val);
            val2 =  (val>>1);
            val3 =  (val>>2);
            val4 =  (val>>3);
        }
        else{
            val1 =  (val);
            val2 =  (val<<1);
            val3 =  (val<<2);
            val4 =  (val<<3);
        }	
				
        //this is for dimming		
        for(i = 0;i < 3; i++){
                        //val is the highest pin that should be active therefore if we're in reverse the others should be to the left
                        assign(val1|val2|val3|val4);
                        //need to do math to see how much this needs to be 
                        delay(15);
                        assign(val1|val2|val3);
                        delay(20);
                        assign(val1|val2);
                        delay(25);
                        assign(val1);
                        delay(30);        
        }

        k++;
        //keep previous value of val so that we can calculate 0x001 and 0x200 correctly
        //update value
        if(reverse){
            val = val<<1;
        }
        else{
            val = val>>1;
        }
        if(val == 0x001){
            reverse = 1;
        }
        else if(val == 0x200){
            reverse = 0;
        }
    }
}



