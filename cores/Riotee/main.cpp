#include "FreeRTOS.h"
#include "nrf.h"
#include "nrf_gpio.h"
#include "semphr.h"
#include "task.h"

#include "ble.h"
#include "gpint.h"
#include "printf.h"
#include "riotee_module_pins.h"
#include "runtime.h"
#include "thresholds.h"
#include "timing.h"
#include "uart.h"

void setup(void);
void loop(void);

/* This gets called one time after flashing new firmware */
void bootstrap_callback(void) { printf("All new!"); }

/* This gets called after every reset */
void reset_callback(void) { setup(); }

void user_task(void *pvParameter) {
  UNUSED_PARAMETER(pvParameter);
  for (;;) {
    loop();
  }
}
