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
  rx_pin: '13'
  tx_pin: '14'

  # WiFi settings
  ssid_set: !secret wifi_ssid
  password_set: !secret wifi_password
  
########################################################################################
#                        CODE BELOW SHOULD NOT BE CHANGED                              #
########################################################################################  

esphome:
  name: ${device_name}

esp32:
  board: pico32
  framework:
    type: arduino

# Enable logging
logger:
  baud_rate: 0
    
# Enable Home Assistant API
api:
  
ota:

wifi:
  ssid: ${ssid_set}
  password: ${password_set}

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Wavin Fallback Hotspot"

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
  flow_control_pin: 26
  
modbus_controller:
  id: sentio_modbus_controller
  address: 1
  modbus_id: modbus_id
  update_interval: ${update_interval}

# Uncomment the active channels on your Wavin Sentio
packages:
  remote_package:
    url: https://github.com/nic6911/esphome_components
    ref: main
    files: 
      - components/sentio/configs/basic.yaml # REQUIRED FOR WAVIN SENTIO
      - components/sentio/configs/channel_01.yaml
      - components/sentio/configs/channel_02.yaml
      - components/sentio/configs/channel_03.yaml
      - components/sentio/configs/channel_04.yaml
      - components/sentio/configs/channel_05.yaml
      - components/sentio/configs/channel_06.yaml
      - components/sentio/configs/channel_07.yaml
      - components/sentio/configs/channel_08.yaml
      - components/sentio/configs/channel_09.yaml
      #- components/sentio/configs/channel_10.yaml #If you have combined channels you need to comment one out like I have here where my channel 9+10 has only 1 thermostat
      - components/sentio/configs/channel_11.yaml
      #- components/sentio/configs/channel_12.yaml
      #- components/sentio/configs/channel_13.yaml
      #- components/sentio/configs/channel_14.yaml
      #- components/sentio/configs/channel_15.yaml
      #- components/sentio/configs/channel_16.yaml

```