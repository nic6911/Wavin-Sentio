## ESPHome custom components


Example:
```
########################################################################################
#                                                                                      #
#      WAVIN SENTIO FLOOR HEATING CONTROLLER SOFTWARE FOR HOME ASSISTANT               #
#                                                                                      #   
#        Code developed by : Mogens Groth Nicolaisen                                   #
#                                                                                      #
# https://github.com/heinekmadsen/esphome_components/tree/main/components/wavinAhc9000 #    
#                                                                                      #
# Hardware by : Mogens Groth Nicolaisen https://github.com/nic6911/Wavin-AHC-9000-mqtt #                                                                                       
#                                                                                      #
########################################################################################


########################################################################################
#                      CONFIGURATION PART OF YOUR CHOICE :)                            #
########################################################################################

substitutions:
  device_name: 'wavin_sentio'
  friendly_name: 'Sentio'
  log_level: DEBUG
 
  # UPDATE TIME (GATEWAY)
  update_interval: 10s
  
  # CHANNEL ID´S
  channel_1:  Arnes værelse
  channel_2:  Bad børn
  channel_3:  Bad voksen
  channel_4:  Bryggers
  channel_5:  Ellens værelse
  channel_6:  Entré
  channel_7:  Fars kontor
  channel_8:  Mors kontor
  channel_9:  Soveværelse
  channel_10: Stue
  channel_11: <Unused>
  channel_12: <Unused>
  channel_13: <Unused>
  channel_14: <Unused>
  channel_15: <Unused>
  channel_16: <Unused>
  
  # TEMP STEP + CLIMATE MIN/MAX LIMIT TEMP SETPOINT
  temp_step:   '0.5'
  climate_min_temp: '12'  
  climate_max_temp: '30'
  
  # PIN DEFINITIONS (Should in most cases not be changed) 
  rx_pin: RX
  tx_pin: TX

  # WiFi settings
  ssid_set: "My Wi-Fi Network"
  password_set: "password"
  
########################################################################################
#                        CODE BELOW SHOULD NOT BE CHANGED                              #
########################################################################################  

esphome:
  name: ${device_name}
  platform: ESP8266
  board: esp01_1m
  project:
    name: "home.wavin_sentio_gulvvarme"
    version: "1.0.0"


# Enable logging
logger:
  baud_rate: 0
    
# Enable Home Assistant API
api:
  
ota:
  password: "945ac67ddcae11048f6a488672b6aadb"

wifi:
  ssid: ${ssid_set}
  password: ${password_set}

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Wavin Fallback Hotspot"
    password: "12345678"

captive_portal:  

uart:
  rx_pin: ${rx_pin}
  tx_pin: ${tx_pin}
  baud_rate: 19200
  id: uart_modbus
  parity: NONE
  stop_bits: 1
  
modbus:
  id: modbus_id
  uart_id: uart_modbus
  
modbus_controller:
  id: sentio_modbus_controller
  address: 1
  modbus_id: modbus_id
  update_interval: ${update_interval}
  


sentio:

sensor:

#########################
#### INPUT REGISTERS ####
#########################

  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "Modbus baud rate"
    id: sentio_baud_rate
    register_type: holding
    address: 0x00004

  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_1} temperatur"
    id: temperatur_channel_1
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 104
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_1} luftfugtighed"
    id: luftfugtighed_channel_1
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 106
    filters:
      - multiply: 0.01      

      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_2} temperatur"
    id: temperatur_channel_2
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 204
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_2} luftfugtighed"
    id: luftfugtighed_channel_2
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 206
    filters:
      - multiply: 0.01            

number:

  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_1} temperatur setpunkt"
    id: temperatur_setpunkt_channel_1
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 119
    force_new_range: true
    use_write_multiple: true 
    write_lambda: "payload = modbus_controller::float_to_payload(x*100, modbus_controller::SensorValueType::U_WORD); return x;"
    lambda: "return x*0.01;"
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_1} temperatur setpunkt"
    id: temperatur_setpunkt_channel_2
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 219
    force_new_range: true
    use_write_multiple: true 
    write_lambda: "payload = modbus_controller::float_to_payload(x*100, modbus_controller::SensorValueType::U_WORD); return x;"
    lambda: "return x*0.01;"      

climate:
  - platform: sentio
    name: ${channel_1}
    current_temp_sensor_id: temperatur_channel_1
    target_temp_sensor_id: temperatur_setpunkt_channel_1

  - platform: sentio
    name: ${channel_2}
    current_temp_sensor_id: temperatur_channel_2
    target_temp_sensor_id: temperatur_setpunkt_channel_2

```