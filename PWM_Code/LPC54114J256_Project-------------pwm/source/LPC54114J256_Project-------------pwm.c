/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    LPC54114J256_Project-------------pwm.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC54114_cm4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include "fsl_sctimer.h"
/* TODO: insert other definitions and declarations here. */

#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define LEFT_MOTOR_SIGNAL1 kSCTIMER_Out_5                //D5 pin
#define LEFT_MOTOR_SIGNAL2 kSCTIMER_Out_7				//D7 pin

uint32_t eventNumberOutput,eventNumberOutput1;
/*
 * @brief   Application entry point.
 */
int main(void) {


	sctimer_config_t sctimerInfo;
			    sctimer_pwm_signal_param_t pwmParam_left1,pwmParam_left2;
			    uint32_t event1,event2;
			    uint32_t sctimerClock;

			    sctimerClock = SCTIMER_CLK_FREQ;





  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    SCTIMER_GetDefaultConfig(&sctimerInfo);


    pwmParam_left1.output = LEFT_MOTOR_SIGNAL1;
    pwmParam_left1.level = kSCTIMER_HighTrue;
    pwmParam_left1.dutyCyclePercent = 40;


   			             /* Configure first PWM with frequency 24kHZ from LEFT MOTOR SECOND SIGNAL output
   			              *
   			              */
    pwmParam_left2.output = LEFT_MOTOR_SIGNAL2;
   	pwmParam_left2.level = kSCTIMER_HighTrue;
   	pwmParam_left2.dutyCyclePercent = 20;




               /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);
    SCTIMER_SetupPwm(SCT0, &pwmParam_left1, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event1);
    SCTIMER_SetupPwm(SCT0, &pwmParam_left2, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event2);
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);

            SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL1,50,event1);
              	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL2,85,event2);
              	 SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL1,50,event1);

    /* Force the counter to be placed into memory. */

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    }
    return 0 ;
}
