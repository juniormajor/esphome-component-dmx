import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import CONF_TX_PIN, CONF_RX_PIN, CONF_ID

dmx_ns = cg.esphome_ns.namespace("dmx")
DMXComponent = dmx_ns.class_("DMXComponent", cg.Component)

CONF_ENABLE_PIN = "enable_pin"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(DMXComponent),
    cv.Required(CONF_TX_PIN): pins.gpio_output_pin_schema,
    cv.Required(CONF_RX_PIN): pins.gpio_input_pin_schema,
    cv.Optional(CONF_ENABLE_PIN, default="GPIO4"): pins.gpio_output_pin_schema
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    tx_pin = await cg.gpio_pin_expression(config[CONF_TX_PIN])
    rx_pin = await cg.gpio_pin_expression(config[CONF_RX_PIN])
    en_pin = await cg.gpio_pin_expression(config[CONF_ENABLE_PIN])
    cg.add(var.set_pins(tx_pin, rx_pin, en_pin))
