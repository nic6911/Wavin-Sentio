# Wavin Sentio in ESPHome

This is a simple Esp8266 ESPHome interface for Wavin Sentio enabling you to control your heating from Home Assistant. 

## Disclaimer
Do this at your own risk ! You are interfacing with hardware that you can potentially damage if you do not connect things as required !
Using the hardware and code presented here is done at you own risk. The hardware has been tested on Wavin AHC9000, Wavin Sentio and Nilan Comfort 300 without issues.

## Hardware

Hardware used here is developed by me and is a mutli-purpose ESP-01 Modbus module that was intended for Wavin AHC9000, Wavin Sentio and Nilan ventilation. But since it is pretty generic it will suit most modus applications.
The hardware includes buck converter supplying the ESP-01 and Modbus module with 3.3V from anything going from 8-24V (28V absolute max rating) as 12V and 24V are usually available on these systems for powering something like this.

Contact me if you need hardware and dont want to construct it yourself.
For more details on the hardware look here: https://github.com/nic6911/Wavin-AHC-9000-mqtt

## Software

This is an ESPHome implementation of Wavin Sentio modbus interface - look at the example below to see how its used.
I made an esphome component for the Sentio supporting the code below - look here: https://github.com/nic6911/esphome_components/tree/Wavin_Sentio

## Documentation
Look in the documentation folder and more specifically from page 140 in "Sentio Technical-Handbook Sept 21.pdf"
All other documentation in the folder is complementary

## Example:
```
########################################################################################
#                                                                                      #
#      WAVIN SENTIO FLOOR HEATING CONTROLLER SOFTWARE FOR HOME ASSISTANT               #
#                                                                                      #   
#        Code developed by : Mogens Groth Nicolaisen                                   #
#                                                                                      #  
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
  channel_1:  Bryggers
  channel_2:  Entré
  channel_3:  Ellens værelse
  channel_4:  Arnes værelse
  channel_5:  Mors kontor
  channel_6:  Stue/KA
  channel_7:  Bad voksne
  channel_8:  Soveværelse
  channel_9:  Bad børn
  channel_10: <Unused>
  channel_11: Fars kontor
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

external_components:
  - source: github://nic6911/esphome_components@Wavin_Sentio
    refresh: 0s  
      
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
    
## Channel 1
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_1} mode"
    id: mode_channel_1
    register_type: read
    address: 102
      
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
      
## Channel 2
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_2} mode"
    id: mode_channel_2
    register_type: read
    address: 202
    
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
      
## Channel 3
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_3} mode"
    id: mode_channel_3
    register_type: read
    address: 302
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_3} temperatur"
    id: temperatur_channel_3
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 304
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_3} luftfugtighed"
    id: luftfugtighed_channel_3
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 306
    filters:
      - multiply: 0.01 
      
## Channel 4
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_4} mode"
    id: mode_channel_4
    register_type: read
    address: 402
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_4} temperatur"
    id: temperatur_channel_4
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 404
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_4} luftfugtighed"
    id: luftfugtighed_channel_4
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 406
    filters:
      - multiply: 0.01 
      
## Channel 5
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_5} mode"
    id: mode_channel_5
    register_type: read
    address: 502
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_5} temperatur"
    id: temperatur_channel_5
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 504
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_5} luftfugtighed"
    id: luftfugtighed_channel_5
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 506
    filters:
      - multiply: 0.01       
      
## Channel 6
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_6} mode"
    id: mode_channel_6
    register_type: read
    address: 602
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_6} temperatur"
    id: temperatur_channel_6
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 604
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_6} luftfugtighed"
    id: luftfugtighed_channel_6
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 606
    filters:
      - multiply: 0.01       
      
## Channel 7
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_7} mode"
    id: mode_channel_7
    register_type: read
    address: 702
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_7} temperatur"
    id: temperatur_channel_7
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 704
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_7} luftfugtighed"
    id: luftfugtighed_channel_7
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 706
    filters:
      - multiply: 0.01       
      
## Channel 8
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_8} mode"
    id: mode_channel_8
    register_type: read
    address: 802
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_8} temperatur"
    id: temperatur_channel_8
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 804
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_8} luftfugtighed"
    id: luftfugtighed_channel_8
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 806
    filters:
      - multiply: 0.01       
      
## Channel 9
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_9} mode"
    id: mode_channel_9
    register_type: read
    address: 902
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_9} temperatur"
    id: temperatur_channel_9
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 904
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_9} luftfugtighed"
    id: luftfugtighed_channel_9
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 906
    filters:
      - multiply: 0.01       
      
## Channel 10
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_10} mode"
    id: mode_channel_10
    register_type: read
    address: 1002
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_10} temperatur"
    id: temperatur_channel_10
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 1004
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_10} luftfugtighed"
    id: luftfugtighed_channel_10
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 1006
    filters:
      - multiply: 0.01               
      
## Channel 11
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_11} mode"
    id: mode_channel_11
    register_type: read
    address: 1102
    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_11} temperatur"
    id: temperatur_channel_11
    unit_of_measurement: °C
    accuracy_decimals: 1
    device_class: temperature
    register_type: read
    address: 1104
    filters:
      - multiply: 0.01
      
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_11} luftfugtighed"
    id: luftfugtighed_channel_11
    unit_of_measurement: '%'
    accuracy_decimals: 1
    device_class: humidity
    register_type: read
    address: 1106
    filters:
      - multiply: 0.01   
      
#########################
### SETPOINT REGISTERS ##
#########################

number:
## Channel 1
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
    multiply: 100

## Channel 2    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_2} temperatur setpunkt"
    id: temperatur_setpunkt_channel_2
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 219
    force_new_range: true
    use_write_multiple: true 
    multiply: 100

## Channel 3    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_3} temperatur setpunkt"
    id: temperatur_setpunkt_channel_3
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 319
    force_new_range: true
    use_write_multiple: true 
    multiply: 100

## Channel 4   
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_4} temperatur setpunkt"
    id: temperatur_setpunkt_channel_4
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 419
    force_new_range: true
    use_write_multiple: true 
    multiply: 100

## Channel 5   
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_5} temperatur setpunkt"
    id: temperatur_setpunkt_channel_5
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 519
    force_new_range: true
    use_write_multiple: true 
    multiply: 100

## Channel 6    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_6} temperatur setpunkt"
    id: temperatur_setpunkt_channel_6
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 619
    force_new_range: true
    use_write_multiple: true 
    multiply: 100

## Channel 7   
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_7} temperatur setpunkt"
    id: temperatur_setpunkt_channel_7
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 719
    force_new_range: true
    use_write_multiple: true 
    multiply: 100

## Channel 8    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_8} temperatur setpunkt"
    id: temperatur_setpunkt_channel_8
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 819
    force_new_range: true
    use_write_multiple: true 
    multiply: 100

## Channel 9    
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_9} temperatur setpunkt"
    id: temperatur_setpunkt_channel_9
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 919
    force_new_range: true
    use_write_multiple: true 
    multiply: 100
    
## Channel 11   
  - platform: modbus_controller
    modbus_controller_id: sentio_modbus_controller
    name: "${channel_11} temperatur setpunkt"
    id: temperatur_setpunkt_channel_11
    min_value: 10.0
    max_value: 30.0
    step: 0.5
    address: 1119
    force_new_range: true
    use_write_multiple: true 
    multiply: 100    

#########################
#### CLIMATE ENTITIES ###
#########################

climate:
  - platform: sentio
    name: ${channel_1}
    current_temp_sensor_id: temperatur_channel_1
    target_temp_sensor_id: temperatur_setpunkt_channel_1
    mode_select_id: mode_channel_1

  - platform: sentio
    name: ${channel_2}
    current_temp_sensor_id: temperatur_channel_2
    target_temp_sensor_id: temperatur_setpunkt_channel_2
    mode_select_id: mode_channel_2
    
  - platform: sentio
    name: ${channel_3}
    current_temp_sensor_id: temperatur_channel_3
    target_temp_sensor_id: temperatur_setpunkt_channel_3
    mode_select_id: mode_channel_3

  - platform: sentio
    name: ${channel_4}
    current_temp_sensor_id: temperatur_channel_4
    target_temp_sensor_id: temperatur_setpunkt_channel_4
    mode_select_id: mode_channel_4   
    
  - platform: sentio
    name: ${channel_5}
    current_temp_sensor_id: temperatur_channel_5
    target_temp_sensor_id: temperatur_setpunkt_channel_5
    mode_select_id: mode_channel_5

  - platform: sentio
    name: ${channel_6}
    current_temp_sensor_id: temperatur_channel_6
    target_temp_sensor_id: temperatur_setpunkt_channel_6
    mode_select_id: mode_channel_6  
    
  - platform: sentio
    name: ${channel_7}
    current_temp_sensor_id: temperatur_channel_7
    target_temp_sensor_id: temperatur_setpunkt_channel_7
    mode_select_id: mode_channel_7

  - platform: sentio
    name: ${channel_8}
    current_temp_sensor_id: temperatur_channel_8
    target_temp_sensor_id: temperatur_setpunkt_channel_8
    mode_select_id: mode_channel_8  
    
  - platform: sentio
    name: ${channel_9}
    current_temp_sensor_id: temperatur_channel_9
    target_temp_sensor_id: temperatur_setpunkt_channel_9
    mode_select_id: mode_channel_9

  - platform: sentio
    name: ${channel_10}
    current_temp_sensor_id: temperatur_channel_10
    target_temp_sensor_id: temperatur_setpunkt_channel_10
    mode_select_id: mode_channel_10    
    
  - platform: sentio
    name: ${channel_11}
    current_temp_sensor_id: temperatur_channel_11
    target_temp_sensor_id: temperatur_setpunkt_channel_11
    mode_select_id: mode_channel_11      

```