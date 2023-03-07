#include "RioteeBLE.h"
#include "ble.h"

#include <cstring>

ble_ll_addr_t adv_address = {
    .addr_bytes = {0xBE, 0xEF, 0xDE, 0xAD, 0x00, 0x01}};

void RioteeBLE::begin(const char adv_name[], size_t data_len) {
  ble_init();
  ble_prepare_adv(&adv_address, adv_name, strlen(adv_name), data_len);
}

void RioteeBLE::advertise(void *data) { ble_advertise(data, ADV_CH_ALL); }

RioteeBLE BLE;