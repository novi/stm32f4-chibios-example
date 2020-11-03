/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "hal.h"
#include "osal.h"
// #include "rt_test_root.h"
// #include "oslib_test_root.h"
#include "chprintf.h"

static SerialConfig usart2_config = {
  115200,
  0,
  0,
  0
};

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  osalInit();
  osalSysEnable();

  /*
   * Activates the serial driver 2 using the driver default configuration.
   */
  sdStart(&SD2, &usart2_config);

  static uint8_t counter = 0;
  while (true) {
    palClearPad(GPIOC, GPIOC_LED_BLUE);
    osalThreadSleepMilliseconds(500);
    palSetPad(GPIOC, GPIOC_LED_BLUE);
    osalThreadSleepMilliseconds(500);
    // sdWrite(&SD2, (uint8_t*)"Hello\r\n", 7);
    chprintf((BaseSequentialStream*)&SD2, "hello %d, tick=%d\r\n", counter, osalOsGetSystemTimeX() );
    counter++;
  }  
}
