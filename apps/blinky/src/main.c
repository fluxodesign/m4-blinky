/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <string.h>

#include "sysinit/sysinit.h"
#include "os/os.h"
#include "bsp/bsp.h"
#include "hal/hal_gpio.h"
#ifdef ARCH_sim
#include "mcu/mcu_sim.h"
#endif
#include "misc.h"

static volatile int g_task1_loops;

/* For LED toggling */
int g_led_pin, g_orange_pin, g_blue_pin, g_red_pin;

/**
 * main
 *
 * The main task for the project. This function initializes packages,
 * and then blinks the BSP LED in a loop.
 *
 * @return int NOTE: this function should never return!
 */
int
main(int argc, char **argv)
{
    int rc;

#ifdef ARCH_sim
    mcu_sim_parse_args(argc, argv);
#endif

    sysinit();

    g_led_pin = LED_BLINK_PIN;
    g_orange_pin = LED_BLINK_ORANGE;
    g_blue_pin = LED_BLINK_BLUE;
    g_red_pin = LED_BLINK_RED;
    hal_gpio_init_out(g_led_pin, 0);
    hal_gpio_init_out(g_orange_pin, 0);
    hal_gpio_init_out(g_blue_pin, 0);
    hal_gpio_init_out(g_red_pin, 0);

    while (1) {
        ++g_task1_loops;

        cycleLed(g_led_pin);
        cycleLed(g_orange_pin);
        cycleLed(g_red_pin);
        cycleLed(g_blue_pin);
    }
    assert(0);

    return rc;
}

void cycleLed(int led)
{
	hal_gpio_toggle(led);
	os_time_delay(OS_TICKS_PER_SEC/5);
	hal_gpio_toggle(led);
	os_time_delay(OS_TICKS_PER_SEC/5);
}

