#include "Serial.h"
#include "nrf_uart.h"
#include "uart.h"

#include <stdint.h>

int SerialClass::available() { return -1; }
int SerialClass::read() { return -1; }
int SerialClass::peek() { return -1; }
void SerialClass::flush() { return; }

void SerialClass::begin(unsigned long baudrate) {
  uint32_t nrf_baudrate;

  if (baudrate <= 1200) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud1200;
  } else if (baudrate <= 2400) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud2400;
  } else if (baudrate <= 4800) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud4800;
  } else if (baudrate <= 9600) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud9600;
  } else if (baudrate <= 14400) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud14400;
  } else if (baudrate <= 19200) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud19200;
  } else if (baudrate <= 28800) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud28800;
  } else if (baudrate <= 38400) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud38400;
  } else if (baudrate <= 57600) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud57600;
  } else if (baudrate <= 76800) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud76800;
  } else if (baudrate <= 115200) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud115200;
  } else if (baudrate <= 230400) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud230400;
  } else if (baudrate <= 250000) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud250000;
  } else if (baudrate <= 460800) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud460800;
  } else if (baudrate <= 921600) {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud921600;
  } else {
    nrf_baudrate = UART_BAUDRATE_BAUDRATE_Baud1M;
  }
  NRF_UART0->BAUDRATE = nrf_baudrate;
}

size_t SerialClass::write(const uint8_t *buffer, size_t size) {
  size_t n = 0;
  for (unsigned int i = 0; i < size; i++)
    _putchar(*buffer++);
  return size;
}

size_t SerialClass::write(uint8_t c) {
  _putchar(c);
  return 1;
}

SerialClass Serial;