#include <Arduino.h>
#include <ArduinoLog.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <ProjectConfig.h>
#include <MidiWrapper.h>





void setup()
{
	Serial.begin(115200);
	
	Log.begin(LOG_LEVEL_INFO, &Serial);

	pinMode(GPIO_LED_LYRAT, OUTPUT);
	digitalWrite(GPIO_LED_LYRAT, HIGH);
	
	MidiWrapperInit(GPIO_MIDI_RX, GPIO_MIDI_TX);

}

void loop()
{
	delay(1000);
	digitalWrite(GPIO_LED_LYRAT, digitalRead(GPIO_LED_LYRAT) ^ 1);
}
