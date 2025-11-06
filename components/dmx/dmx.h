#pragma once
#include "esphome/core/component.h"

#include "esp_dmx.h"
#include "sniffer.h"
#include "device.h"
#include "driver.h"
#include "parameter.h"
#include "service.h"
#include "types.h"
#include "gpio.h"
#include "nvs.h"
#include "timer.h"
#include "uart.h"
#include "controller.h"
#include "responder.h"

namespace esphome {
namespace dmx {

class DMXComponent : public Component {
 public:
  gpio_num_t tx_pin_;
  gpio_num_t rx_pin_;
  gpio_num_t en_pin_;

  void set_pins(GPIOPin *tx, GPIOPin *rx, GPIOPin *en) {
    tx_pin_ = (gpio_num_t)tx->get_pin();
    rx_pin_ = (gpio_num_t)rx->get_pin();
    en_pin_ = (gpio_num_t)en->get_pin();
  }

  void setup() override {
    dmx_config_t config = DMX_CONFIG_DEFAULT;
    dmx_driver_install(DMX_NUM_1, &config, nullptr, 0);
    dmx_set_pin(DMX_NUM_1, tx_pin_, rx_pin_, en_pin_);
    ESP_LOGI("dmx", "DMX initialized on TX:%d RX:%d EN:%d", tx_pin_, rx_pin_, en_pin_);
  }

  void loop() override {
    static uint8_t data[512] = {0};
    dmx_write_packet(DMX_NUM_1, data, sizeof(data));
    dmx_send_packet(DMX_NUM_1);
  }
};

}  // namespace dmx
}  // namespace esphome
