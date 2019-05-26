/*
===============================================================================
 Name        : pwm.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(BOARD_NXP_LPCXPRESSO_54114)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#if defined (__MULTICORE_MASTER_SLAVE_M0SLAVE) || \
    defined (__MULTICORE_MASTER_SLAVE_M4SLAVE)
#include "boot_multicore_slave.h"
#endif

// TODO: insert other include files here

// TODO: insert other definitions and declarations here
#define SCT_PWM            LPC_SCT
#define SCT_PWM_PIN_OUT    7		/* COUT7 Generate square wave */
#define SCT_PWM_OUT        1		/* Index of OUT PWM */
#define SCT_PWM_RATE   10000		/* PWM frequency 10 KHz */


static void app_setup_pin(void)
{
#if defined(BOARD_NXP_LPCXPRESSO_54114)
	/* SCT_OUT5 on PIO1_1 mapped to FUNC2: Oscilloscope input */
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 15, IOCON_FUNC3 | IOCON_MODE_INACT | IOCON_DIGITAL_EN | IOCON_INPFILT_OFF);
#else
#warning "No SCT pin muxing defined"
#endif
}



int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
                          SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
#if defined (__MULTICORE_MASTER) || defined (__MULTICORE_NONE)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
#endif
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

#if defined (__MULTICORE_MASTER_SLAVE_M0SLAVE) || \
    defined (__MULTICORE_MASTER_SLAVE_M4SLAVE)
    boot_multicore_slave();
#endif



    app_setup_pin();

    Chip_SCTPWM_Init(SCT_PWM);
    Chip_SCTPWM_SetRate(SCT_PWM, SCT_PWM_RATE);

    Chip_SCTPWM_SetOutPin(SCT_PWM, SCT_PWM_OUT, SCT_PWM_PIN_OUT);

    Chip_SCTPWM_SetDutyCycle(SCT_PWM, SCT_PWM_OUT, Chip_SCTPWM_PercentageToTicks ( SCT_PWM, 95 ));

    Chip_SCTPWM_Start(SCT_PWM);

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        i++ ;
    }
    return 0 ;
}
