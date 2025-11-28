#ifndef __MIDI_WRAPPER_H__
#define __MIDI_WRAPPER_H__

// Project includes
#include <Arduino.h>
#include <ArduinoLog.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void MidiWrapperInit(int8_t rx_pin, int8_t tx_pin);


#endif // __MIDI_WRAPPER_H__