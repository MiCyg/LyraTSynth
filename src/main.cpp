#include <Arduino.h>
#include <ArduinoLog.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <ProjectConfig.h>
#include <MidiWrapper.h>



MidiCCVal param1 = MidiCCVal(10, "Param1");
MidiCCVal param2 = MidiCCVal(74, "Param2");

void setup()
{
	Serial.begin(115200);
	
	Log.begin(LOG_LEVEL_INFO, &Serial);

	pinMode(GPIO_LED_LYRAT, OUTPUT);
	digitalWrite(GPIO_LED_LYRAT, HIGH);
	
	MidiWrapper::getInstance().begin(GPIO_MIDI_RX, GPIO_MIDI_TX);


	MidiWrapper::getInstance().AddCCMapping(&param1);
	MidiWrapper::getInstance().AddCCMapping(&param2);
}

void loop()
{
	delay(100);
	digitalWrite(GPIO_LED_LYRAT, digitalRead(GPIO_LED_LYRAT) ^ 1);
	Log.info("Param1: %d, Param2: %d\n", param1.Value, param2.Value);
}
