# watering

This sketch is intended for controller which should rule grass watering system. It can control several watering zones. Each zone has its own relay which controls water valve. Controller connected to home automation system through RS485 using Modbus protocol. It exposes current state of each relay and provides ability to remotely turn them on and off. It also has RTC onboard, so has ability to handle (and remember in EEPROM) set of timers, which provide ability to implement simple watering schedule during the day. Timers are also controled through Modbus.

Current version of the sketch provides basic functionality for relay state manipulation using Modbus through RS485.

## Modbus registers structure
Current list describes each Modbus register by its addres.
- 0 - number of relay channels available in device [O]
- 1 - number of timers available in device [O]
- 2 - current device time hours [I/O]
- 3 - current device time minutes [I/O]
- 4 - current device time seconds [I/O]
- 5 - 5+[number of channels] - current state of each relay channel
- 5+[number of channels] - 5+[number of channels]+[number of timers]*6 - device timers data

## led.py

This is a simple example script which provides ability to write specific register with specific value. Usage:
> python led.py [com port] [register number] [value]

Example (for Windows)
> python led.py COM4 4 1


