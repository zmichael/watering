#include "lib/ModbusRtu.h"
#include "lib/ds3231/ds3231.h"

#define SLAVE_ID 5
#define NUMBER_OF_RELAY_CHANNELS 2
#define NUMBER_OF_TIMERS 10

#define TIMER_STATE_DISABLED 0
#define TIMER_STATE_ON 1
#define TIMER_STATE_OFF 2
#define TIMER_STATE_INTERVAL 3

#define RELAY_ON HIGH
#define RELAY_OFF LOW

const uint8_t relayPinNumbers[NUMBER_OF_RELAY_CHANNELS] = { LED_BUILTIN, 7 };

// Modbus slave object
Modbus modbusSlave(SLAVE_ID, 0 /*serial iface number*/, 10 /* txen pin */);

// describes time in 24H format 
struct Time {
  uint16_t hours, minutes, timeSeconds;
};

// desribes device timer, which could be applied on specific relay channel
struct RelayTimer {
  uint16_t channelNumber = 0;
  uint16_t timerState = 0;
  Time time;
  uint16_t interval = 0;
};

// describes and exposes to Modbus current device state
struct DeviceState {
  uint16_t numberOfChannels = NUMBER_OF_RELAY_CHANNELS; // ADDR 0 
  uint16_t numberOfTimers = NUMBER_OF_TIMERS; // ADDR 1
  Time time; // ADDR 2-4 current time on device
  uint16_t relayStates[NUMBER_OF_RELAY_CHANNELS] = {0}; // ADDR 5 - 5 + NUMBER_OF_RELAY_CHANNELS state of each relay
  RelayTimer timers[NUMBER_OF_TIMERS]; // 5 + NUMBER_OF_RELAY_CHANNELS + 1 timer data for each enabled timer
} deviceState;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  modbusSlave.begin( 9600, SERIAL_8E1 );
  for(int i = 0; i < NUMBER_OF_RELAY_CHANNELS; i++) {
    pinMode(relayPinNumbers[i], OUTPUT);
  }
  Serial.println(sizeof(deviceState));
}

void loop() {
  // put your main code here, to run repeatedly:
  modbusSlave.poll((uint16_t*)&deviceState, sizeof(DeviceState));
  
  for(int i = 0; i < NUMBER_OF_RELAY_CHANNELS; i++) {
    digitalWrite(relayPinNumbers[i], deviceState.relayStates[i] ? RELAY_ON : RELAY_OFF);
  }
}
