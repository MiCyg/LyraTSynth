#include <Arduino.h>
#include <ArduinoLog.h>
#include <MIDI.h>
#include <config/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


void midi_task(void *parameter) 
{
	Log.infoln("Starting MIDI wrapper task...");
	
	static HardwareSerial MidiSerial(1);

	MidiSerial.begin(31250, SERIAL_8N1, GPIO_MIDI_RX, GPIO_MIDI_TX);
	MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial,  MIDI);
	MIDI.begin(MIDI_CHANNEL_OMNI);

	while (true) 
	{
		if (MIDI.read())
		{
			Log.infoln("Channel: %d, Type: %d, data1: %d, data2: %d", MIDI.getChannel(), MIDI.getType(), MIDI.getData1(), MIDI.getData2());
		}

		// vTaskDelay(1);
		yield();
	}

}

void setup()
{
	Serial.begin(115200);
	
	Log.begin(LOG_LEVEL_INFO, &Serial);
	

	pinMode(GPIO_LED_LYRAT, OUTPUT);
	digitalWrite(GPIO_LED_LYRAT, HIGH);

	
	xTaskCreate(midi_task, "MIDI Wrapper", 8*1024, NULL, tskIDLE_PRIORITY, NULL);
}

void loop()
{
	delay(1000);
	digitalWrite(GPIO_LED_LYRAT, digitalRead(GPIO_LED_LYRAT) ^ 1);
	// Log.infoln("Main loop alive %d", millis());
}
