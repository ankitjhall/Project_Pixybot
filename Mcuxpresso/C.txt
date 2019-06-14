/**
 * @file    lpc-54114----motor_control_with_button.c
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
#define LEFT_MOTOR_SIGNAL1 kSCTIMER_Out_2                //D5 pin
#define LEFT_MOTOR_SIGNAL2 kSCTIMER_Out_7				//D7 pin
#define RIGHT_MOTOR_SIGNAL1 kSCTIMER_Out_4				//D10 pin
#define RIGHT_MOTOR_SIGNAL2 kSCTIMER_Out_5				//D9 pin
uint32_t eventNumberOutput;


/*
 * @brief   Application entry point.
 */
int main(void) {
	uint32_t dutycycle_left=50,dutycycle_right=50,a=0,b=0;

		/* Define the init structure for the output LED pin*/
	    gpio_pin_config_t left_motor_speedup = {
	        kGPIO_DigitalInput, 1,
	    };
	    gpio_pin_config_t left_motor_speeddn = {
	    	        kGPIO_DigitalInput, 1,
	    	    };

	    gpio_pin_config_t right_motor_speedup = {
	   	        kGPIO_DigitalInput, 1,
	   	    };

	    gpio_pin_config_t right_motor_speeddn = {
	   	        kGPIO_DigitalInput, 1,
	   	    };

	    gpio_pin_config_t left_motor_dir = {
	   	        kGPIO_DigitalInput, 1,
	   	    };
	    gpio_pin_config_t right_motor_dir = {
	   	        kGPIO_DigitalInput, 1,
	   	    };

	 sctimer_config_t sctimerInfo;
		    sctimer_pwm_signal_param_t pwmParam_left1,pwmParam_left2,pwmParam_right1,pwmParam_right2;
		    uint32_t event;
		    uint32_t sctimerClock;










  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    /* enable clock for GPIO*/
       CLOCK_EnableClock(kCLOCK_Gpio0);
       CLOCK_EnableClock(kCLOCK_Gpio1);


      // GPIO_PortInit(GPIO, BOARD_lefft_motor_speedup_PORT);
     GPIO_PinInit(GPIO, BOARD_left_motor_speedup_PORT, BOARD_left_motor_speedup_PIN, &left_motor_speedup);
     GPIO_PinInit(GPIO, BOARD_left_motor_speeddn_PORT, BOARD_left_motor_speeddn_PIN, &left_motor_speeddn);

     GPIO_PinInit(GPIO, BOARD_right_motor_speedup_PORT, BOARD_right_motor_speedup_PIN, &right_motor_speedup);
     GPIO_PinInit(GPIO, BOARD_right_motor_speeddn_PORT, BOARD_right_motor_speeddn_PIN, &right_motor_speeddn);

     GPIO_PinInit(GPIO, BOARD_left_motor_dir_PORT, BOARD_left_motor_dir_PIN, &left_motor_dir);
     GPIO_PinInit(GPIO, BOARD_right_motor_dir_PORT, BOARD_right_motor_dir_PIN, &right_motor_dir);


    sctimerClock = SCTIMER_CLK_FREQ;

    /* Configure first PWM with frequency 24kHZ from LEFT MOTOR FIRST SIGNAL output */
        pwmParam_left1.output = LEFT_MOTOR_SIGNAL1;
        pwmParam_left1.level = kSCTIMER_HighTrue;
        pwmParam_left1.dutyCyclePercent = 10;


           /* Configure first PWM with frequency 24kHZ from LEFT MOTOR SECOND SIGNAL output */
        pwmParam_left2.output = LEFT_MOTOR_SIGNAL2;
        pwmParam_left2.level = kSCTIMER_HighTrue;
        pwmParam_left2.dutyCyclePercent = 50;

              /* Configure first PWM with frequency 24kHZ from RIGHT MOTOR FIRST SIGNAL output */
        pwmParam_right1.output = RIGHT_MOTOR_SIGNAL1;
        pwmParam_right1.level = kSCTIMER_HighTrue;
        pwmParam_right1.dutyCyclePercent = 10;

                 /* Configure first PWM with frequency 24kHZ from RIGHT MOTOR SECOND SIGNAL output */
        pwmParam_right2.output = RIGHT_MOTOR_SIGNAL2;
        pwmParam_right2.level = kSCTIMER_HighTrue;
        pwmParam_right2.dutyCyclePercent = 50;

        SCTIMER_GetDefaultConfig(&sctimerInfo);

           /* Initialize SCTimer module */
        SCTIMER_Init(SCT0, &sctimerInfo);

        SCTIMER_SetupPwm(SCT0, &pwmParam_left1, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event);
        SCTIMER_SetupPwm(SCT0, &pwmParam_left2, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event);

        SCTIMER_SetupPwm(SCT0, &pwmParam_right1, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event);
        SCTIMER_SetupPwm(SCT0, &pwmParam_right2, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event);

        SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);





    /* Force the counter to be placed into memory. */

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	if(GPIO_PinRead(GPIO, BOARD_left_motor_speedup_PORT, BOARD_left_motor_speedup_PIN)==0)
    	{
    		while(GPIO_PinRead(GPIO, BOARD_left_motor_speedup_PORT, BOARD_left_motor_speedup_PIN)==0);
    		dutycycle_left=dutycycle_left+20;
    		if(dutycycle_left==100)
    			dutycycle_left=20;

    	}

    	if(GPIO_PinRead(GPIO, BOARD_left_motor_speeddn_PORT, BOARD_left_motor_speeddn_PIN)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, BOARD_left_motor_speeddn_PORT, BOARD_left_motor_speeddn_PIN)==0);
    		dutycycle_left=dutycycle_left-20;
    	    	}


    	if(GPIO_PinRead(GPIO, BOARD_right_motor_speedup_PORT, BOARD_right_motor_speedup_PIN)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, BOARD_right_motor_speedup_PORT, BOARD_right_motor_speedup_PIN)==0);
    		dutycycle_right=dutycycle_right+20;
    		 if(dutycycle_right==100)
    		    dutycycle_right=10;
    	    	}


    	if(GPIO_PinRead(GPIO, BOARD_right_motor_speeddn_PORT, BOARD_right_motor_speeddn_PIN)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, BOARD_right_motor_speeddn_PORT, BOARD_right_motor_speeddn_PIN)==0);
    		dutycycle_right=dutycycle_right-20;
    	    	}

    	if(GPIO_PinRead(GPIO, BOARD_left_motor_dir_PORT, BOARD_left_motor_dir_PIN)==0)
    	{
    		while(GPIO_PinRead(GPIO, BOARD_left_motor_dir_PORT, BOARD_left_motor_dir_PIN)==0);
    		a=a+1;
    		if (a==2)
    		{
    			a=0;

    		}

    	}

    	if(GPIO_PinRead(GPIO, BOARD_right_motor_dir_PORT, BOARD_right_motor_dir_PIN)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, BOARD_right_motor_dir_PORT, BOARD_right_motor_dir_PIN)==0);
    		b=b+1;
    		  if (b==2)
    		   {
    		   	b=0;

    		    }}
    if(a==0){
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL1,dutycycle_left,eventNumberOutput);
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL2,10,eventNumberOutput);
    }
    if(a==1)
    {
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL1,1,eventNumberOutput);
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL2,dutycycle_left,eventNumberOutput);

    }

    if(b==0){
    	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL1,dutycycle_right,eventNumberOutput);
    	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL2,1,eventNumberOutput);
    }
    if(b==0){
        	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL1,1,eventNumberOutput);
        	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL2,dutycycle_right,eventNumberOutput);
        }


}
return 0;
}
