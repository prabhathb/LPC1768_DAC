#include <LPC17xx.h>
#include "DAC.h"

//initialize DAC
void DAC_Init( void ){
	//turn power on
	LPC_SC->PCLKSEL0 |= (1 << 23); //select PERIPHERAL clock for DAC 
	LPC_SC->PCLKSEL0 |= (1 << 22);
	LPC_PINCON->PINSEL1 |=  (1 << 21); //enable AOUT in P0.26 - set PINSEL1.21
	LPC_PINCON->PINSEL1 &= ~(1 << 20); //enable AOUT in P0.26 - clear PINSEL1.20
	LPC_PINCON->PINMODE1 |= (1 << 21);
	LPC_PINCON->PINMODE1 |= (1 << 20); //enable pull-down resistor in P0.26
}
//Turn DAC ON
void DAC_turn_ON( void ){
	LPC_DAC->DACCTRL |=  (1 << 2);
}

//Turn DAC OFF
void DAC_turn_OFF( void ){
	LPC_DAC->DACCTRL &=  ~(1 << 2);
}	
	
//Set high speed operation
void DAC_high_speed ( void ){
	LPC_DAC->DACR &= ~(1 << 16); //operate at 1MHz
}
//Set low speed operation	
void DAC_low_speed ( void ){
	LPC_DAC->DACR |= (1 << 16); //operate at 400kHz
}

//Update DAC with new digital value
void DAC_update ( uint16_t value ) {
	LPC_DAC->DACR = ((LPC_DAC->DACR & 0x00010000) | (value << 6));
}

