;******************** (C) Yifeng ZHU *******************************************
; @file    main.s
; @author  Yifeng Zhu
; @date    May-17-2015
; @note
;           This code is for the book "Embedded Systems with ARM Cortex-M 
;           Microcontrollers in Assembly Language and C, Yifeng Zhu, 
;           ISBN-13: 978-0982692639, ISBN-10: 0982692633
; @attension
;           This code is provided for education purpose. The author shall not be 
;           held liable for any direct, indirect or consequential damages, for any 
;           reason whatever. More information can be found from book website: 
;           http:;www.eece.maine.edu/~zhu/book
;*******************************************************************************

	INCLUDE core_cm4_constants.s		; Load Constant Definitions
	INCLUDE stm32l476xx_constants.s      

; Green LED <--> PA.5
LED_PIN	EQU	5
change DCD 1
	
	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	ENTRY			
				
__main	PROC
		
    ; Enable the clock to GPIO Port A	
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR r1, r1, #RCC_AHB2ENR_GPIOAEN
	STR r1, [r0, #RCC_AHB2ENR]
	
	; Enable the clock to GPIO port C
	LDR r2, =RCC_BASE
	LDR r3, [r2, #RCC_AHB2ENR]
	ORR r3, r3, #RCC_AHB2ENR_GPIOCEN
	STR r3, [r2, #RCC_AHB2ENR]
	
	; Program the port A mode register (MODER) to set Pin 5 as output
	; bic is &= ~
	LDR r0, =GPIOA_BASE
	LDR r1, [r0, #GPIO_MODER]
	BIC r1, r1, #(3<<(2*LED_PIN))
	ORR r1, r1, #(1<<(2*LED_PIN))
	STR r1, [r0, #GPIO_MODER]

	;; Program GPIOC->MODER to set the mode of Pin PC 13 as input
	LDR r2, =GPIOC_BASE
	LDR r3, [r2, #GPIO_MODER]
	BIC r3, r3, #(3<<(5*(LED_PIN)+1))
	ORR r3, r3, #0
	STR r3, [r2, #GPIO_MODER]

	; Program the port A output type register (OTYPER) to set Pin 5 as push-pull
	LDR r0, =GPIOA_BASE
	LDR r1, [r0, #GPIO_OTYPER]
	BIC r1, r1, #(1<<(LED_PIN))
	ORR r1, r1, #0
	STR r1, [r0, #GPIO_OTYPER]
	
	;Program the port A pull-up/pull-down register (PUPDR) to set Pin 5 as no-pull-up no pull-down.
	LDR r0, =GPIOA_BASE
	LDR r1, [r0, #GPIO_PUPDR]
	BIC r1, r1, #(3<<(2*LED_PIN))
	ORR r1, r1, #0
	STR r1, [r0, #GPIO_PUPDR]
	
	;Program GPIOC->PUPDR to set the pull-up/pull-down setting of Pin PC 13 as no pull-up no pull-down
	LDR r2, =GPIOC_BASE
	LDR r3, [r2, #GPIO_PUPDR]
	BIC r3, r3, #(3<<(5*(LED_PIN)+1))
	ORR r3, r3, #0
	STR r3, [r2, #GPIO_PUPDR]
	
	; Program the port A output data register (ODR) to set the output of Pin 5 to 1 or 0, which enables or disables the LED, respectively.
	LDR r0, =GPIOA_BASE
	LDR r1, [r0, #GPIO_ODR]
	BIC r1, r1, #(1<<(LED_PIN))
	ORR r1, r1, #(1<<(LED_PIN))
	STR r1, [r0, #GPIO_ODR]
  
	;Prelab part: GPIOA->ODR |= GPIO_ODR_ODR_5;
	;LDR r0, =GPIOA_BASE
	;LDR r1, [r0, #GPIO_ODR]
	;ORR r1, r1, #(1<<(LED_PIN))
	;STR r1, [r0, #GPIO_ODR]
	
	;Code for make check if the LED is on and off
	LDR r4, =change
	LDR r4, [r4]
	
while_1
while_2	LDR r2, =GPIOC_BASE
		LDR r3, [r2, #GPIO_IDR]
		CMP r3, #GPIO_IDR_IDR_13
		BNE while_break
		CMP r4,#1
		BNE i_f
		EOR	r1,r1,#(1<<(LED_PIN)) 
		STR r1, [r0, #GPIO_ODR]
		MOV r4,#0x0
	
i_f	B while_2
	
while_break	MOV r4,#0x1
	
	B while_1

	ENDP		
	ALIGN			
	AREA    myData, DATA, READWRITE
	ALIGN
array	DCD   1, 2, 3, 4
	END