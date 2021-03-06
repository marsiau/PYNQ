/******************************************************************************
 *  Copyright (c) 2018, Xilinx, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1.  Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2.  Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *  3.  Neither the name of the copyright holder nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION). HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/
/******************************************************************************
 *
 *
 * @file gpio.h
 *
 * Header file for GPIO related functions for PYNQ Microblaze, 
 * including the GPIO read and write.
 *
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----- --- ------- -----------------------------------------------
 * 1.00  yrq 01/30/18 add protection macro
 *
 * </pre>
 *
 *****************************************************************************/
#ifndef _GPIO_H_
#define _GPIO_H_
#ifdef __cplusplus 
extern "C" {
#endif
#include <xparameters.h>

#ifdef XPAR_XGPIO_NUM_INSTANCES
#define PYNQ_HAS_GPIO

enum {
GPIO_OUT = 0,
GPIO_IN = 1,
GPIO_INDEX_MIN = 0,
GPIO_INDEX_MAX = 31,
};

/** Class for interacting with Microblaze GPIO
 *
 * Instances should be created using `gpio_open`,
 * `gpio_open_device` or `gpio_open_grove` from the
 * `grove_interfaces` module.
 *
 */
typedef int gpio;

/** Open a physical GPIO controller
 *
 * Returns a GPIO object representing all of the pins of the designated
 * controller. To create smaller ranges, this GPIO object can be passed
 * into `gpio_configure` multiple times to create child instances for
 * different pin ranges. It is undefined to have multiple GPIO instances
 * being used to control the same pins.
 *
 * Parameters
 * ----------
 * device : int
 *     The index of the controler to open - should be less than `gpio_get_num_devices`
 *
 * Returns
 * -------
 *     A GPIO object
 *
 */
gpio gpio_open_device(unsigned int device);

#ifdef XPAR_IO_SWITCH_NUM_INSTANCES
#ifdef XPAR_IO_SWITCH_0_GPIO_BASEADDR

/** Opens a physical pin as a GPIO device
 *
 * Parameters
 * ----------
 * pin : int
 *     The index of the pin to open
 *
 * Returns
 * -------
 *     A GPIO object
 *
 */
gpio gpio_open(unsigned int pin);
#endif
#endif

/** Create a new GPIO instance corresponding to a sub-range on an existing controller
 *
 */
gpio gpio_configure(gpio device, unsigned int low, unsigned int high, 
                    unsigned int channel);

/** Set the direction of the pins controlled by the object
 *
 * Parameters
 * ----------
 * direction : GPIO_IN or GPIO_OUT
 *    The direction to set the pin
 *
 */
void gpio_set_direction(gpio device, unsigned int direction);

/** Read the value of the pins
 *
 * Assumes that pins are already set up as input pins
 *
 */
int gpio_read(gpio device);

/** Write the values of the pins
 *
 * Assumes that pins are already set up as output
 *
 * Parameters
 * ----------
 * data : int
 *     The value to set the pins to
 *
 */
void gpio_write(gpio device, unsigned int data);

/** Close the GPIO device
 *
 * Also tristates the pins
 */
void gpio_close(gpio device);

/** Get the number of physical controllers in the IOP
 *
 */
unsigned int gpio_get_num_devices(void);

#endif
#ifdef __cplusplus 
}
#endif
#endif  // _GPIO_H_
