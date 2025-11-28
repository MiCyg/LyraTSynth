#include <MidiWrapper.h>
#include <MIDI.h>

static HardwareSerial MidiSerial = HardwareSerial(1);
MIDI_CREATE_INSTANCE(HardwareSerial, MidiSerial,  MIDI);

static int8_t gpio_rx = GPIO_NUM_23;
static int8_t gpio_tx = GPIO_NUM_18;


void midiTask(void *parameter) 
{
	Log.infoln("Starting MIDI wrapper task...");
	MidiSerial.begin(31250, SERIAL_8N1, gpio_rx, gpio_tx);
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

void MidiWrapperInit(int8_t rx_pin, int8_t tx_pin)
{
	gpio_rx = rx_pin;
	gpio_tx = tx_pin;
	xTaskCreate(midiTask, "MIDI wrapper", 8*1024, NULL, tskIDLE_PRIORITY, NULL);
}

