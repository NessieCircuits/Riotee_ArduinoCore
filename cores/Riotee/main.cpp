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

void startup(void);
void bootstrap(void);
void setup(void);
void loop(void);

__attribute__((weak)) void startup(void){};
__attribute__((weak)) void bootstrap(void){};

/* This gets called very early, before setting up memory */
void startup_callback(void) { startup(); }

/* This gets called one time after flashing new firmware */
void bootstrap_callback(void) { bootstrap(); }

/* This gets called after every reset */
void reset_callback(void) { setup(); }

void user_task(void *pvParameter) {
  UNUSED_PARAMETER(pvParameter);
  for (;;) {
    loop();
  }
}
