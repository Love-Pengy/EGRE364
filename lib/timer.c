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
