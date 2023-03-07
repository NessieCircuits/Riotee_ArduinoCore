#include "SHTC3.h"
#include "i2c.h"
#include "timing.h"

#include <cstring>

#define DEVICE_ADDRESS (0x70)
#define SHTC3_ID 0x0807

static volatile enum {
  STATE_BUSY,
  STATE_IDLE,
  STATE_ERROR,
} i2c_state;

typedef enum {
  ORDER_T_FIRST,
  ORDER_RH_FIRST,
} shtc3_order_t;

enum shtc3_cmd_e {
  CMD_SLEEP = 0xB098,
  CMD_WAKEUP = 0x3517,
  CMD_MEAS_NORM_TF = 0x7CA2,
  CMD_MEAS_NORM_RHF = 0x5C24,
  CMD_MEAS_LP_TF = 0x6458,
  CMD_MEAS_LP_RHF = 0x44DE,
  CMD_RESET = 0x805D,
  CMD_READ_ID = 0xEFC8,
};

typedef uint16_t shtc3_cmd_t;
static void cmd2bytes(uint8_t *buf, shtc3_cmd_t cmd) {
  buf[1] = *((uint8_t *)&cmd);
  cmd = cmd >> 8;
  buf[0] = *((uint8_t *)&cmd);
}

static uint8_t rx_buf[6];

static uint8_t crc8(uint8_t *data, size_t length) {
  uint16_t polynomial = 0x131;
  uint8_t bit;        // bit mask
  uint8_t crc = 0xFF; // calculated checksum
  uint8_t index;      // byte counter

  // calculates 8-Bit checksum with given polynomial
  for (index = 0; index < length; index++) {
    crc ^= (data[index]);
    for (bit = 8; bit > 0; --bit) {
      if (crc & 0x80) {
        crc = (crc << 1) ^ polynomial;
      } else {
        crc = (crc << 1);
      }
    }
  }

  return crc;
}

int SHTC3Class::begin() {
  int ret;
  uint8_t cmd_buf[2];

  cmd2bytes(cmd_buf, CMD_WAKEUP);
  if ((ret = i2c_write(DEVICE_ADDRESS, cmd_buf, sizeof(shtc3_cmd_t))))
    return -1;

  unsigned int retries = 5;
  cmd2bytes(cmd_buf, CMD_READ_ID);

  while (1) {
    if ((ret = i2c_write(DEVICE_ADDRESS, cmd_buf, sizeof(shtc3_cmd_t))) == 0)
      break;
    if (--retries == 0)
      return -1;
  }

  if ((ret = i2c_read(rx_buf, 3, DEVICE_ADDRESS)))
    return ret;

  if (crc8(rx_buf, 2) != rx_buf[2])
    return -1;

  uint16_t id = (rx_buf[0] << 8) + rx_buf[1];
  if ((id & 0x83F) != SHTC3_ID)
    return -1;

  cmd2bytes(cmd_buf, CMD_SLEEP);

  /* Put device to sleep */
  i2c_write(DEVICE_ADDRESS, cmd_buf, sizeof(shtc3_cmd_t));
  return ERR_OK;
}

static int convert(shtc3_res_t *res, uint8_t *buf, shtc3_order_t order) {
  uint16_t measurements[2];
  measurements[0] = (buf[0] << 8) + buf[1];
  measurements[1] = (buf[3] << 8) + buf[4];

  if (crc8(buf, 2) != buf[2])
    return -ERR_CRC;

  if (crc8(buf + 3, 2) != buf[5])
    return -ERR_CRC;

  if (order == ORDER_T_FIRST) {
    res->temp = -45.0f + 175.0f * ((float)measurements[0]) / 65536.0f;
    res->humidity = 100.0 * ((float)measurements[1]) / 65536.0f;
  } else {
    res->temp = -45.0f + 175.0f * ((float)measurements[1]) / 65536.0f;
    res->humidity = 100.0 * ((float)measurements[0]) / 65536.0f;
  }
  return 0;
}

int SHTC3Class::read(shtc3_res_t *res) {
  int ret;
  uint8_t cmd_buf[2];
  cmd2bytes(cmd_buf, CMD_WAKEUP);

  if ((ret = i2c_write(DEVICE_ADDRESS, cmd_buf, sizeof(shtc3_cmd_t))))
    return ret;

  unsigned int retries = 10;

  cmd2bytes(cmd_buf, CMD_MEAS_LP_TF);

  while (1) {
    if ((ret = i2c_write(DEVICE_ADDRESS, cmd_buf, sizeof(shtc3_cmd_t))) == 0)
      break;
    if (--retries == 0)
      return ret;
  }
  nrf_delay_us(850);

  if ((ret = i2c_read(rx_buf, 6, DEVICE_ADDRESS)))
    return ret;

  ret = convert(res, rx_buf, ORDER_T_FIRST);

  cmd2bytes(cmd_buf, CMD_SLEEP);
  i2c_write(DEVICE_ADDRESS, cmd_buf, sizeof(shtc3_cmd_t));
  return ret;
}

SHTC3Class SHTC3;