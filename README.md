# LyraTSynth
![Work in Progress](https://img.shields.io/badge/status-in--progress-orange)

My dream was to build an analog synthesizer — a project full of electrical work. For now, the goal has shifted to designing a digital one :)

This project aims to build a flexible framework for different types of synthesizers running on a low-cost microcontroller.
In this repository, most of the focus will be on software, while the hardware will be kept as a small and simple module.

## Hardware

Key components of the [ESP32-LyraT](https://docs.espressif.com/projects/esp-adf/en/latest/design-guide/dev-boards/board-esp32-lyrat-v4.3.html#selecting-of-the-audio-output):

* **Microcontroller:** ESP32-WROVER-E with 8 MB of additional PSRAM
* **DAC module:** [ES8388](http://www.everest-semi.com/pdf/ES8388%20DS.pdf) supporting up to 96 kHz / 24-bit sampling
* **Control interface:** several onboard buttons
* **MIDI input:** provided by an additional custom board

The simple schematic of the MIDI input is based on the [MIDI hardware specification](https://midi.org/5-pin-din-electrical-specs) (Figure 2 – MIDI IN and THRU circuit).
It uses an optocoupler connected to a UART pin of the microcontroller.


<p align="center">
	<img src="images/lyrat_and_midi.jpg" width="75%" />
</p>

## Project timeline

- [X] **1 weeks** – Prepare the hardware for testing (solder the MIDI input)
- [ ] **3 weeks** – Create a parser for MIDI parameter control
- [ ] **3 weeks** – Implement the waveform generation library. This will be a class that generates successive audio buffers, which can be modulated in real time using the MIDI parser module.
- [ ] **3 weeks** – Create the audio processing library and implement a filter controlled via the MIDI parser.
- [ ] **3 weeks** – Extend the library by adding a reverb or delay effect with MIDI control.
- [ ] **1 week** – Test the device to identify any issues during continuous operation.
- [ ] **1 week** – Prepare the presentation.

## Hello World

Yes – I still have a “Hello, World!” example :)

