#ifndef Arduino_h
#define Arduino_h

#include "timing.h"

#ifdef __cplusplus
#include "Serial.h"
#endif

#define LOW (0x0)
#define HIGH (0x1)

#define INPUT (0x0)
#define OUTPUT (0x1)
#define INPUT_PULLUP (0x2)
#define INPUT_PULLDOWN (0x3)

#define LED_BUILTIN 3

#ifdef __cplusplus
extern "C" {
#endif

void pinMode(uint32_t pin, uint32_t mode);
void digitalWrite(uint32_t ulPin, uint32_t ulVal);

#ifdef __cplusplus
}
#endif

#endif // Arduino_h
