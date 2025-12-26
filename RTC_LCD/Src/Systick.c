/*
 * Systick.c
 *
 *  Created on: Dec 26, 2025
 *      Author: mudit
 */
#include "Addresses.h"
#include "Systick.h"

void systickDelayMs(int delay)
{
	/*Configure systick*/
	/*Reload with number of clock per millisecond*/
	SYST_RVR  = SYSTICK_LOAD_VAL - 1;

	/*Clear systick current value register*/
	SYST_CVR = 0;

	/*Enable systick and select internal clock source*/
	SYST_CSR = CTRL_ENABLE | CTRL_CLKSRC ;

	for(int i=0;i<delay;i++)
	{
		/*Wait until COUNTFLAG is set*/
		while(!(SYST_CSR & CTRL_COUNTFLAG)){}

	}
	// Disable SysTick
	SYST_CSR = 0;

}



