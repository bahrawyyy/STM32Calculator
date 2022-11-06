/*
 * EXT_INTERRUPTS.c
 *
 *  Created on: Sep 22, 2022
 *      Author: 10
 */

#include "EXT_INTERRUPTS.h"
#include <avr/interrupt.h>
#include "../../Bit_Math.h"

void EXTI_init(){
	if(EXT_INT0_MODE == ENABLE){
		EXTI_enable(EXTI0);
		if(INT0_SENSE_MODE == LOW_LEVEL_TRIG){
			CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
		}else if(INT0_SENSE_MODE == ANY_LOGIC_TRIG){
			SET_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
		}else if(INT0_SENSE_MODE == FAL_EDGE_TRIG){
			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
		}else if(INT0_SENSE_MODE == RIS_EDGE_TRIG){
			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);
		}
	}
	if (EXT_INT1_MODE == ENABLE) {
		EXTI_enable(EXTI1);
		if (INT0_SENSE_MODE == LOW_LEVEL_TRIG) {
			CLR_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
		} else if (INT0_SENSE_MODE == ANY_LOGIC_TRIG) {
			SET_BIT(MCUCR, ISC10);
			CLR_BIT(MCUCR, ISC11);
		} else if (INT0_SENSE_MODE == FAL_EDGE_TRIG) {
			CLR_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
		} else if (INT0_SENSE_MODE == RIS_EDGE_TRIG) {
			SET_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
		}
	}
}
void EXTI_enable(EXTI_type interrupt){
	switch(interrupt){
	case EXTI0:
		SET_BIT(GICR,INT0);
		break;
	case EXTI1:
		SET_BIT(GICR,INT1);
		break;
	case EXTI2:
		SET_BIT(GICR,INT2);
		break;
	}
}
void EXTI_disable(EXTI_type interrupt){
	switch (interrupt) {
	case EXTI0:
		CLR_BIT(GICR, INT0);
		break;
	case EXTI1:
		CLR_BIT(GICR, INT1);
		break;
	case EXTI2:
		CLR_BIT(GICR, INT2);
		break;
	}
}
