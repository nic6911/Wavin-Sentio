# Wavin-Sentio-mqtt
This is a simple Esp8266 mqtt interface for Wavin AHC9000, Wavin Sentio and Nilan ventilation, with the goal of being able to control this heating controller from a home automation system. The fork here is just an edit to fit a ESP-01 for which I have made a PCB giving a very compact unit.

## Disclaimer
Do this at your own risk ! You are interfacing with hardware that you can potentially damage if you do not connect things as required !
Using the hardware and code presented here is done at you own risk. The hardware has been tested on Wavin AHC9000 and Nilan Comfort 300 without issues.

## Hardware

The Hardware used here is a design done by me (nic6911) and is a mutli-purpose ESP-01 Modbus module that was intended for Wavin AHC9000, Wavin Sentio and Nilan ventilation. But since it is pretty generic it will suit most modus applications.
The hardware includes buck converter supplying the ESP-01 and Modbus module with 3.3V from anything going from 8-24V (28V absolute max rating) as 12V and 24V are usually available on these systems for powering something like this.

### Revision 2.1
To facilitate code versions using Modbus converters without the data direction controlled from the ESP I have implemented Automatic Direction Control. This also makes one more IO available for other uses.
I have decided to add 2 x Optocoupler, one on each available IO, to have isolated outputs which I intend to use for my Nilan system.
This effectively means that the rev 2.1 is a more general purpose hardware platform that in my case will be used for both my Wavin and Nilan setups.

The following schematic shows how my board is constructed in rev 2.1
![Schematic](/electronics/schematic.PNG)

My board design rev 2.1 is seen here:
![Bottom](/electronics/Bottom.PNG)
![Top](/electronics/Top.PNG)

A wiring example on a Comfort 300 and Wavin is shown here:
![Top](/electronics/Connections.png)

On the Wavin you simply use a patch cable (straight) and connect it from the module to the Modbus port and then you are done :)


For this setup to work you need:
My ESP-01 Modus Interface board or similar
An ESP-01
A programmer for the ESP-01

I use the widely available FTDI interface suited for the ESP-01 which requires a minor modification to enable programming mode. To enable programming of the board you need to short two pins for going into programming mode. I solved this with a pin-row and a jumper for selecting programming or not.
Look in the electronics folder for pictures of the programmer and the modification.

## Software
