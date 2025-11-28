#include "MidiWrapper.h"
#include <MIDI.h>


HardwareSerial midiSerial = HardwareSerial(1);
MIDI_CREATE_INSTANCE(HardwareSerial, midiSerial, MIDI);

MidiWrapper::MidiWrapper() : gpioRx(-1), gpioTx(-1), taskHandle(nullptr) 
{

}

MidiWrapper& MidiWrapper::getInstance() 
{
    static MidiWrapper instance;
    return instance;
}

// Initialize with pins
void MidiWrapper::begin(int8_t gpioRx, int8_t gpioTx) 
{
    if (!taskHandle)
	{
		this->gpioRx = gpioRx;
		this->gpioTx = gpioTx;
        xTaskCreate(taskEntry, "MIDI_Task", 8*1024, nullptr, tskIDLE_PRIORITY, &taskHandle);
    }
}

void MidiWrapper::ChangeMidiChannel(uint8_t channel)
{
	MIDI.setInputChannel(channel);
}

void MidiWrapper::AddCCMapping(uint16_t midi_cc, String name="")
{
    ccMappings.push_back(new MidiCCVal(midi_cc, name)); 
}

void MidiWrapper::AddCCMapping(MidiCCVal *mapping)
{
    if(mapping != nullptr)
	{
        ccMappings.push_back(mapping);
	}
}


uint16_t MidiWrapper::GetCCValue(uint16_t midi_cc)
{
    // ccMappings.push_front(MidiCCVal(midi_cc, name));
	return 0;
}

uint16_t MidiWrapper::GetCCValue(String name)
{
	// ccMappings.push_front(MidiCCVal(midi_cc, name));
	return 0;
}

// FreeRTOS task
void MidiWrapper::taskEntry(void* parameter)
{
	MidiWrapper& instance = MidiWrapper::getInstance();
	midiSerial.begin(31250, SERIAL_8N1, instance.gpioRx, instance.gpioTx);
	MIDI.begin(MIDI_CHANNEL_OMNI);

    Log.infoln("Starting MIDI task...");

    while (true)
	{
        if (MIDI.read())
		{
			if(MIDI.getType() == midi::ControlChange)
			{
				int cc = MIDI.getData1();
				int val = MIDI.getData2();

				for(auto mapping : instance.ccMappings)  // mapping is a pointer
				{
					if(mapping->GetMidiCc() == cc)
					{
						if(mapping->Value != val)
						{
							mapping->Value = val;
							Log.infoln("Received %s, Value: %d", mapping->GetName().c_str(), mapping->Value);
						}
					}
				}
			}
        }
        yield();
    }
}