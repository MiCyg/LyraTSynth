#ifndef __MIDI_WRAPPER_H__
#define __MIDI_WRAPPER_H__

// Project includes
#include <Arduino.h>
#include <ArduinoLog.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// #include <list>
#include <vector>

class MidiCCVal
{
	public:
		MidiCCVal(uint16_t midiCc, String name) : MidiCc(midiCc), Value(0), Name(name) {}
		uint16_t Value;
		uint16_t GetMidiCc() const { return MidiCc; }
		String GetName() const { return Name; }

	private:
		uint16_t MidiCc;
		String Name;
};






class MidiWrapper 
{
	public:
		// Singleton accessor
		static MidiWrapper& getInstance();

		// Public API
		void begin(int8_t rx_pin, int8_t tx_pin);
		void begin(HardwareSerial& serial);
		void ChangeMidiChannel(uint8_t channel);
		
		void AddCCMapping(uint16_t midi_cc, String name);
		void AddCCMapping(MidiCCVal *mapping);

		uint16_t GetCCValue(uint16_t midi_cc);
		uint16_t GetCCValue(String name);


	private:
		// Private constructor
		MidiWrapper();

		// Delete copy/assign
		MidiWrapper(const MidiWrapper&) = delete;
		MidiWrapper& operator=(const MidiWrapper&) = delete;

		// Private members
		int8_t gpioRx;
		int8_t gpioTx;
		TaskHandle_t taskHandle;

		std::vector<MidiCCVal*> ccMappings;

		// FreeRTOS task
		static void taskEntry(void* parameter);
};








#endif // __MIDI_WRAPPER_H__