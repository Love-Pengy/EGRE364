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

;;PB12 = 4
; PB13 = 3
;PB14 = 2
;PB15 = 1
LED_PIN	EQU	5
delayAmt DCD 2000
	
	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	ENTRY
	

Delay PROC
	push {r1}
	ldr r1, =delayAmt ;initial value for loop counter
continue NOP ;execute two no-operation instructions
	NOP
	subs r1, #1
	bne continue ; if not equal 
	pop {r1}
	bx lr
	ENDP
	
; enable clocks for GPIOC
RCC_Init PROC
	PUSH {R0,R1}
	LDR R0, =RCC_BASE
	LDR R1, [R0,#RCC_AHB2ENR]
	ORR R1,R1,#RCC_AHB2ENR_GPIOCEN
	STR R1, [R0,#RCC_AHB2ENR]
	POP {R1,R0}
	BX LR ; return from subroutine
	ENDP
	
; PB12-15
GPIO_Init PROC
	PUSH {R0,R1,R2}
	LDR R0, =GPIOB_BASE
	LDR R1, [R0,#GPIO_MODER]
	LDR R2, =0x0FF
	BIC R1,R1,R2, LSL #24
	LDR R2, =0x55; output 01
	ORR R1, R1, R2, LSL #24
	STR R1, [R0,#GPIO_MODER]
	LDR R1, [R0,#GPIO_OSPEEDR]
	LDR R2, =0x0FF
	ORR R1, R1, R2, LSL #24
	STR R1, [R0,#GPIO_OSPEEDR]
	LDR R1, [R0,#GPIO_PUPDR]
	LDR R2, =0x0FF
	BIC R1,R1,R2, LSL #24
	STR R1, [R0,#GPIO_PUPDR]
	LDR R1, [R0,#GPIO_OTYPER]
	LDR R2, =0x0F
	BIC R1, R1, R2, LSL #12
	STR R1, [R0,#GPIO_OTYPER]
	POP {R2,R1,R0}
	BX LR
	ENDP


	
;2_ in front of these allocates these values in binary
seq1 DCB 2_0101,2_0110,2_1010,2_1001,2_0000 ; full step
seq2 DCB 2_0101,2_1001,2_1010,2_0110,2_0000 ; reverse full step 
seq3 DCB 2_0001,2_0100,2_0010,2_1000,2_0000 ; wave step
seq4 DCB 2_0001,2_1000,2_0010,2_0100,2_0000 ; reverse wave step
seq5 DCB 2_0001,2_0101,2_0100,2_0110,2_0010,2_1010,2_1000,2_1001,2_0000 ; half step
seq6 DCB 2_0001,2_1001,2_1000,2_1010,2_0010,2_0110,2_0100,2_0101,2_0000 ; reverse half step

start_mode DCB 1


__main	PROC
	
	; Enable the clock to GPIO port C
	LDR r2, =RCC_BASE
	LDR r3, [r2, #RCC_AHB2ENR]
	ORR r3, r3, #RCC_AHB2ENR_GPIOCEN
	STR r3, [r2, #RCC_AHB2ENR]
	
	;; Program GPIOC->MODER to set the mode of Pin PC 13 as input
	LDR r2, =GPIOC_BASE
	LDR r3, [r2, #GPIO_MODER]
	BIC r3, r3, #(3<<(5*(LED_PIN)+1))
	ORR r3, r3, #0
	STR r3, [r2, #GPIO_MODER]
	
	;Program GPIOC->PUPDR to set the pull-up/pull-down setting of Pin PC 13 as no pull-up no pull-down
	LDR r2, =GPIOC_BASE
	LDR r3, [r2, #GPIO_PUPDR]
	BIC r3, r3, #(3<<(5*(LED_PIN)+1))
	ORR r3, r3, #0
	STR r3, [r2, #GPIO_PUPDR]
	
	
	BL RCC_Init ; init RCC
	BL GPIO_Init ; init GPIO
	LDR R0,=GPIOB_BASE
	ADR R1, seq1; full step
	MOV R5, R1; move the address of r1 into r5
	
	;checker for full or half step
	LDR r6, =start_mode
	
	
loop
	LDR r6, =GPIOC_BASE
	LDR r7, [r6, #GPIO_IDR]
	TST r7, #GPIO_IDR_IDR_13
	BNE switch_mode
	
	LDRB R2,[R1],#1; load single byte from r1 into r2 and then increment address
	CBNZ R2,next; if r2 is 0 go to next 
	MOV R1, R5 ; sets r1 to the original array
	B loop
	
switch_mode  EOR r6, r6
	TST r6, #1
	BNE set_seq_1
	BEQ set_seq_2
	B loop
set_seq_1
	ADR R1, seq1; full step
	MOV R5, R1; move the address of r1 into r5
	B loop
set_seq_2

	ADR R1, seq5; full step
	MOV R5, R1; move the address of r1 into r5
	B loop


next
	LDR R3,[R0,#GPIO_ODR] ; load r3 with value from odr
	LDR R4,=0x0F
	BIC R3,R3,R4, LSL #12 ; clear byte starting from 12 of r3
	ORR R3,R3,R2,LSL #12 ; set r3 to r2 
	STR R3, [R0,#GPIO_ODR] ; store into r0's odr r3
	BL Delay
	B loop


	ENDP		
	ALIGN			
	AREA    myData, DATA, READWRITE
	ALIGN
array	DCD   1, 2, 3, 4
	END
