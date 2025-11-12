#include <Arduino.h>
#include <ArduinoLog.h>
#include <MIDI.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>


MIDI_CREATE_DEFAULT_INSTANCE();

void midi_task()
{
	
	MIDI.begin(MIDI_CHANNEL_OMNI);
	MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, DefaultSerialSettings);
	
	while (true) 
	{
		if (MIDI.read())
		{
			switch(MIDI.getType())
			{
				case midi::ControlChange:
				{
					byte control = MIDI.getData1();
					byte value = MIDI.getData2();
					Log.infoln("Control: %d, Value: %d", control, value);

					break;
				}
				default:
					break;
			}
		}
		// vTaskDelay(2000 / portTICK_PERIOD_MS);
	}

}



void setup()
{
	Serial.begin(115200);
	Log.begin(LOG_LEVEL_INFO, &Serial);

	Log.infoln("Hello world! Starting MIDI wrapper task...");
	xTaskCreate(midi_task, "MIDI Wrapper", 8192, NULL, 1, NULL);
}

void loop()
{
	delay(1000);
	Log.infoln("Main loop alive");
}
