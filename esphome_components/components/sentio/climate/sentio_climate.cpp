#include "sentio_climate.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace sentio {
static const char *TAG = "sentio.climate";

void SentioClimate::setup() {
  current_temp_sensor_->add_on_state_callback([this](float state) {
    // ESP_LOGD(TAG, "CURRENT TEMP SENSOR CALLBACK: %f", state);
    current_temperature = state;
    publish_state();
  });
  temp_setpoint_number_->add_on_state_callback([this](float state) {
    // ESP_LOGD(TAG, "TEMP SETPOINT SENSOR CALLBACK: %f", state);
    target_temperature = state;
    publish_state();
  });
  rel_humid_sensor_->add_on_state_callback([this](float state) {
    // ESP_LOGD(TAG, "HUMIDITY SENSOR CALLBACK: %f", state);
    rel_humid = state;
    publish_state();
  });

  current_temperature = current_temp_sensor_->state;
  target_temperature  = temp_setpoint_number_->state;
  rel_humid = rel_humid_sensor_->state;
}

void SentioClimate::control(const climate::ClimateCall& call) {
  if (call.get_target_temperature().has_value())
  {
    this->target_temperature = *call.get_target_temperature();
    float target = target_temperature;
    ESP_LOGD(TAG, "Target temperature changed to: %f", target);
    temp_setpoint_number_->set(target);
  }
}


climate::ClimateTraits SentioClimate::traits() {
  auto traits = climate::ClimateTraits();

  traits.set_supports_current_temperature(true);
  traits.set_visual_temperature_step(0.5);
  traits.set_visual_min_temperature(5);
  traits.set_visual_max_temperature(30);

  return traits;
}

void SentioClimate::dump_config() {
  LOG_CLIMATE("", "Sentio Climate", this);
}

} // namespace sentio
} // namespace esphome
