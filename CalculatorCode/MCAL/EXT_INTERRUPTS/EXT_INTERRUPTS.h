/*
 * EXT_INTERRUPTS.h
 *
 *  Created on: Sep 22, 2022
 *      Author: 10
 */

#ifndef MCAL_EXT_INTERRUPTS_EXT_INTERRUPTS_H_
#define MCAL_EXT_INTERRUPTS_EXT_INTERRUPTS_H_

#include "EXT_INTERRUPTSConfig.h"

void EXTI_init();
void EXTI_enable(EXTI_type interrupt);
void EXTI_disable(EXTI_type interrupt);

#endif /* MCAL_EXT_INTERRUPTS_EXT_INTERRUPTS_H_ */
