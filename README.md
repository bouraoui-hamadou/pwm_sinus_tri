# Sinus-Dreieck Pulsweiten-Modulation (PWM) Project for XMC4500

[XMC4500](https://www.infineon.com/cms/en/product/microcontroller/32-bit-industrial-microcontroller-based-on-arm-cortex-m/32-bit-xmc4000-industrial-microcontroller-arm-cortex-m4/xmc4500/)

## Overview

This repository contains a group project for implementing Sinus-Dreieck Pulsweiten-Modulation (PWM) on the XMC4500 microcontroller. The project enables precise generation of sinusoidal and triangular waveforms, making it suitable for motor control and power applications.

## Introduction to Pulse Width Modulation (PWM)

Pulse Width Modulation (PWM) is a widely used technique for controlling the amount of power delivered to a load, such as a motor or a light, by varying the width of the pulses of a periodic signal. In PWM, the duty cycle, which is the ratio of pulse duration to the total period, determines the average power delivered to the load. By changing the duty cycle, we can effectively control the output voltage or current, allowing us to regulate the speed of motors or control the brightness of LEDs, for example.

## Project Description

The group project focuses on implementing PWM to generate sinusoidal and triangular waveforms. Sinusoidal waveforms are used in motor control applications, where smooth variations in voltage and current are required for efficient and precise motor operation. Triangular waveforms, on the other hand, are used in various modulation techniques and frequency synthesis applications.

The project utilizes the XMC4500 microcontroller and the DAVE IDE (Integrated Development Environment) for code development. By combining PWM with advanced algorithms, the application achieves accurate and efficient waveform generation.

## Getting Started

To build and run the project, follow these steps:

1. **Download DAVE IDE**: Use the following link to download DAVE IDE, which comes with its own integrated flashing method for XMC microcontrollers: [DAVE IDE Download](https://softwaretools.infineon.com/tools/com.ifx.tb.tool.daveide).

2. **Clone the Repository**: Clone this repository to your local machine using Git or download it as a ZIP file and extract it.

3. **Set Up DAVE IDE**: Open DAVE IDE and import the project files from the repository. Make sure to configure the project settings as required.

4. **Build the Project**: Build the project within DAVE IDE to generate the binary files.

5. **Connect Debugger**: Connect your debugger (e.g., Segger J-Link) to the appropriate debug interface on your XMC4500 development board.

6. **Flash the Microcontroller**: Start the debugging session in DAVE IDE and program the XMC4500 microcontroller with your firmware using the integrated flashing method.

7. **Run the Application**: Power up the XMC4500 and run the application to observe the generated sinusoidal and triangular waveforms.


## Contributions

Contributions to the project are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
