#pragma once

#include "esphome/core/component.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/select/select.h"

namespace esphome {
namespace sentio {
class SentioClimate : public climate::Climate, public Component {
public:

  SentioClimate() {}

  void setup() override;
  void dump_config() override;

  void current_temp_sensor(sensor::Sensor *sensor) {
    this->current_temp_sensor_ = sensor;
  }

  void set_temp_setpoint_number(number::Number *number) {
    this->temp_setpoint_number_ = number;
  }

  void rel_humid_sensor(sensor::Sensor *sensor) {
    this->rel_humid_sensor_ = sensor;
  }

protected:
  /// Override control to change settings of the climate device.
  void control(const climate::ClimateCall& call) override;

  /// Return the traits of this controller.
  climate::ClimateTraits traits() override;

  /// The sensor used for getting the current temperature
  sensor::Sensor *current_temp_sensor_{ nullptr };

  /// The number component used for getting the temperature setpoint
  number::Number *temp_setpoint_number_{ nullptr };

  /// The sensor used for getting the current humidity
  sensor::Sensor *rel_humid_sensor_{ nullptr };

};
} // namespace sentio
} // namespace esphome
