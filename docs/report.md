# Microprocessor-Based Indoor Air Quality Analyzer on ATmega328P

Coursework project ("курсова робота"), 4th year, specialty 123 Computer
Engineering, Y. O. Paton Vocational College of Welding and Electronics.

- **Student:** Damir
- **Advisor:** [redacted]
- **Group:** [redacted]

## Introduction

Indoor air quality directly affects people's health and well-being.
Elevated humidity, temperature, or the presence of harmful gases can lead
to allergic reactions, respiratory illness, and reduced productivity.
Continuous monitoring of these parameters is therefore important for
maintaining a comfortable indoor environment.

One effective way to implement such monitoring is a microprocessor system
built on Arduino. It can integrate various sensors and display measurement
results, providing convenient real-time access to the information.

This coursework develops a microprocessor-based air analysis system built
around the ATmega328P microcontroller [1]. The system includes:

- a DHT11 temperature/humidity sensor, measuring temperature in the range
  0–50 °C with ±2 °C accuracy and humidity 20–90% with ±5% accuracy [2];
- an analog MQ-2 gas sensor for detecting various gases such as methane,
  propane, smoke, and others, allowing an estimate of air pollution level;
- a 16×2 LCD display with an I2C interface, providing convenient output of
  measurement results while reducing the number of connections and
  simplifying the device's wiring [3].

The goal of the coursework is to design and implement a microprocessor
system for monitoring temperature, humidity, and harmful gas concentration
in indoor air, with the results shown on a display.

To achieve this goal, the following tasks were addressed:

- analyze existing indoor air quality monitoring methods and select
  suitable sensors for temperature, humidity, and gas measurement;
- design the sensor-to-microcontroller wiring and organize communication
  with the display over the I2C interface.

The object of study is the process of designing microprocessor systems for
indoor air quality monitoring. The subject of study is the methods of
integrating temperature, humidity, and gas sensors with the ATmega328P
microcontroller to build an air quality monitoring system.

## 1. General part

### 1.1 Problem statement

The task of this coursework is to design a microprocessor-based indoor air
analysis system built around the ATmega328P microcontroller.

Maintaining proper indoor climate conditions is one of the key factors
supporting human health and productivity [4]. Insufficient ventilation,
elevated humidity, excess harmful gases, or elevated temperature can
worsen well-being, reduce concentration, increase fatigue, and reduce the
efficiency of study or work. Prolonged exposure to poor indoor air quality
increases the risk of respiratory and allergic illness, which makes
indoor climate control especially relevant [5].

The main tasks of the work are:

- measure air temperature and humidity using a DHT11 sensor, allowing
  control of comfortable conditions for people in the room;
- monitor harmful gas concentration in the room using an analog MQ-2 gas
  sensor, enabling detection of potentially dangerous situations for
  health;
- display measurement results on a 16×2 LCD over the I2C interface,
  providing clarity, accessibility, and a quick assessment of air
  condition;
- design the electrical circuit connecting the sensors and display to the
  microcontroller, with attention to minimizing the number of connections
  and ensuring stable operation of the system.

The tasks are formulated to ensure the creation of an effective, reliable,
and easy-to-use air quality monitoring system that supports a healthy and
comfortable environment for study and work.

### 1.2 Purpose and application of the microprocessor system

The developed indoor air analysis system based on the ATmega328P is
intended for the real-time monitoring of indoor climate parameters and
detection of potentially hazardous changes in air composition. Its main
task is to provide the user with up-to-date information on temperature,
humidity, and gas pollution level in real time, allowing a timely response
to hazardous situations.

The system serves as an accessible and convenient monitoring tool
applicable in various settings. In educational institutions, it helps
create comfortable study conditions and reduce health risks in
poorly-ventilated rooms. In workplaces, it contributes to higher
productivity by maintaining a normal indoor climate, since elevated
temperature or high humidity are known to significantly reduce
concentration and work capacity.

Such systems are also valuable for home use. In residential spaces, they
help detect excess gas or smoke concentration in time, which may be
related to faulty gas equipment or household appliances, helping prevent
hazardous situations and creating a safer environment for residents [6].

In addition, Arduino-based microprocessor systems have educational value.
They are widely used in training specialists in electronics, programming,
and automation. Developing such devices helps reinforce theoretical
knowledge in practice and gain experience working with microcontrollers,
sensors, and interfaces, which is an important part of future professional
work.

The purpose of the system is to create a universal device for air
analysis applicable in education, at work, at home, and in research. Its
use not only improves comfort indoors but also makes the environment
safer for people.

### 1.3 Technical characteristics of the microprocessor system

The air parameter analysis system is developed on the Arduino Nano board,
fitted with an ATmega328P chip. This controller runs at 16 MHz, has 32 KB
of flash memory for program storage, 2 KB of SRAM for real-time data
processing, and 1 KB of non-volatile EEPROM for retaining information
after power-off. The Arduino Nano has 14 digital I/O pins (6 of which can
operate as PWM channels) and 8 analog inputs for connecting sensors.
The board can be powered from a USB port (5 V), which is also used for
programming the device, or from an external DC source.

The system supports two power modes:

- a standalone mode based on a TP4056 charging module with a lithium
  polymer battery in a 1s5p configuration, providing extended standalone
  operating time;
- a stationary mode powered from USB, which directly powers the Arduino
  Nano through its built-in voltage regulator.

### 1.4 Survey of analogous devices

There is a considerable number of indoor air quality monitoring devices on
the market today, used both at home and in industry. Most of them
integrate into "smart home" systems, have mobile apps for convenient data
display, and feature a wide range of sensors.

One example is the Xiaomi Smart Air Quality Monitor, capable of measuring
temperature, humidity, and volatile organic compound levels. Its
advantages are compactness and the ability to transmit data to a
smartphone. Its drawback is the lack of standalone operation without
network access. [14]

The Awair Element device is aimed at household use and has an extended
sensor set: it measures CO₂ level, humidity, temperature, PM2.5 dust
concentration, and volatile organic compounds. Its main drawback is high
cost and dependence on cloud services. [15]

The IQAir AirVisual Pro is considered a more professional air monitoring
device. It tracks temperature, humidity, CO₂ concentration, and PM2.5
dust. The device can accumulate data and display it over Wi-Fi, but is
noted for being complex to maintain and expensive. [16]

Among well-known brands, the Netatmo Smart Indoor Air Quality Monitor also
stands out, tracking humidity, temperature, CO₂, and noise level. The main
advantage of this solution is integration into comprehensive "smart home"
systems, but the device has limited standalone operation. [17]

For industrial purposes, Honeywell's systems are used, providing
measurement of a wide range of indicators: PM2.5, PM10, CO₂, CO,
temperature, and humidity. Such devices are noted for high accuracy and
reliability, but have a high cost and complex installation.

Comparing the listed analogues with the developed ATmega328P-based
microprocessor system, it can be concluded that the proposed device will
be simpler and more affordable to implement. Its advantage lies in
combining basic temperature, humidity, and gas-pollution control functions
with standalone power capability. This makes it a promising option for
educational use, household application, and further refinement.

### 1.5 Operating principle at the structural-diagram level

The device is a compact microprocessor system for monitoring indoor air
parameters.

#### 1.5.1 Structural diagram

At the structural-diagram level the system consists of the following base
blocks:

- power supply block (USB, or TP4056 + Li-Pol 1s5p + boost converter if
  needed);
- Arduino Nano (ATmega328P) controller as the central processing unit;
- DHT11 temperature/humidity sensor as a digital source of climate data;
- MQ-2 gas sensor as an analog gas-pollution sensor;
- 16×2 LCD with I2C interface (I2C expander on a PCF8574 or equivalent);
- auxiliary elements: alarm indicators (LED, buzzer), buttons, connectors,
  filtering capacitors, battery protection.

#### 1.5.2 Power supply block — principles and requirements

The device can be powered in two ways: from USB (5 V through the mini-USB/
USB-B port on the Nano board) or standalone, through a lithium-polymer
battery in 1s5p configuration charged by a TP4056 module.

Note on standalone mode: the TP4056 provides charge control for a single
lithium-polymer cell. Powering the Arduino Nano at its 16 MHz operating
clock requires a stabilized 5 V supply. The circuit should provide power
decoupling and filtering: 0.1 µF capacitors near the microcontroller's
power pins, a 10–47 µF electrolytic capacitor on the 5 V rail, and a fuse
or polyfuse on the power input (the board itself already has some degree
of filtering, but not enough).

#### 1.5.3 Arduino Nano (ATmega328P) — role and interfaces

The Arduino Nano performs the function of data acquisition, primary
processing, display output, and alarm logic. Key hardware characteristics
used: 16 MHz, 32 KB flash, 2 KB SRAM, 1 KB EEPROM, 10-bit ADC (0…1023).

Key pins used for connections:

- A0 — analog input for the MQ-2 (module Vout / sensor node);
- D2 (or another free digital pin) — single-wire interface for the DHT11
  (an external 4.7–10 kΩ pull-up resistor to Vcc is required);
- A4 (SDA), A5 (SCL) — I2C bus for the LCD with PCF8574 expander.

#### 1.5.4 DHT11 — operating principle and connection

The DHT11 combines a capacitive humidity sensor and a thermistor/internal
element for temperature, and transmits data over a digital single-wire
protocol. Data arrives as a 40-bit sequence (16 bits temperature/humidity
+ check bits).

Operation sequence: the microcontroller sends a start pulse (low level,
≥18 ms), the sensor responds with a series of pulses and bits — reading is
accurate to roughly ±1 s (a polling interval of at least 1 s is
recommended).

For reliable operation a 4.7–10 kΩ pull-up resistor on the DATA line is
needed; software checksum validation of the readings is recommended.

#### 1.5.5 MQ-2 — operating principle, connection, and signal processing

The MQ-2 is a semiconductor sensor based on tin oxide (SnO₂); in the
presence of combustible gases its resistance Rs changes (decreasing as gas
concentration increases). The module typically outputs an analog voltage
Vout, formed as a voltage divider between Rs (the sensing element) and a
load resistor RL.

Typical measurement circuit: Vcc → [sensing element Rs] → Vout node →
[RL] → GND; Vout is fed into the ADC (A0). The module usually has a
trimming resistor for RL; when designing a custom board, RL is chosen in
the 2–20 kΩ range (typically 5–10 kΩ) depending on range and sensitivity.

Conversion formulas:

```
Vout = (RL / (RL + Rs)) · Vcc
Rs = RL · (Vcc / Vout − 1)
```

The relative value Rs/R0 is used to estimate gas concentration (R0 is the
sensor's resistance under reference conditions — clean air — after
calibration).

Key requirements: the element has a heater that needs a stable 5 V supply
and draws a significant current (on the order of tens to hundreds of mA).
The sensor needs a warm-up period — a few minutes to tens of minutes for
basic stabilization; the manufacturer often recommends a 24–48 hour
initial burn-in for full parameter stabilization.

Calibration: setting R0 in clean air (a known clean environment) at the
start of operation; the R0 value is stored in EEPROM for subsequent
calculations. Converting Rs/R0 → ppm is done using the manufacturer's
sensitivity curves (logarithmic approximation or a lookup table in
firmware).

#### 1.5.6 16×2 LCD over I2C — connection and display logic

The HD44780-class display is operated in 4-bit mode through an I2C
expander (typically a PCF8574). This allows the display to be connected
with just two wires (SDA, SCL), freeing up the controller's digital pins.

The typical I2C module address is 0x27 or 0x3F; software initialization
includes setting up 4-bit mode and backlight control.

The display shows the main parameters: temperature (°C), humidity (%), a
gas-level indicator (qualitative rating or percentage/multiple of
threshold), and an alarm indication.

#### 1.5.7 Program sequence (algorithm)

Initialization: hardware setup of peripherals (I2C, ADC, GPIO), display
initialization, reading calibration parameters (R0) from EEPROM,
readiness indication.

Warm-up/stabilization: on first power-up, allow time for the MQ-2 to
stabilize (recommended wait: at least a few minutes; for precise
measurements, up to 10–15 minutes or more depending on conditions).

Measurement cycle:

- read DHT11 (interval ≥1 s) → checksum validation → obtain T, RH;
- read MQ-2 via ADC (faster interval, e.g. 1–5 s, averaging n readings to
  reduce noise) → compute Vout, Rs, Rs/R0 → convert to a qualitative
  rating (L, M, H) or an approximate ppm value using the approximation;
- apply a filter (moving average, exponential smoothing) to reduce noise;
- threshold check: if T, RH, or gas concentration exceed set thresholds —
  trigger the alarm indicator (LED, buzzer) and show a message on the
  display;
- update the display (e.g. every second or after each measurement cycle);
- in standalone power mode, apply power-saving modes (temporarily turning
  off the display, lowering polling frequency, using ATmega328P sleep
  modes).

Data retention: optionally — storing calibration and statistical data in
EEPROM (e.g. R0, time of last calibration, maximum recorded values).

*[Figure: wiring diagram — see `diagrams/schematic.png`. Note: the original
document's Figure 1.3 caption calls this image a "code block diagram"; it
is in fact the same component wiring diagram as the schematic, just drawn
at a lower level of detail — see Editor's notes below.]*

#### 1.5.8 Electrical and construction details

For connecting the MQ-2, a module variant with an analog voltage output
must be used; the board should provide for adjusting RL (a 10 kΩ
potentiometer) for convenient calibration.

Access to the GND, Vcc, A0, D2, SDA, SCL contacts on connectors is needed
for convenient assembly and debugging.

The thermal influence of the MQ-2's heating element must also be
considered when placing it near the DHT11 — close proximity should be
avoided so the humidity sensor's temperature reading is not skewed.

#### 1.5.9 Error accounting and calibration

The DHT11 has limited accuracy (approximately ±2 °C, ±5% RH) and a slow
response — this is accounted for when interpreting data through
adaptation of the readings in firmware.

The MQ-2 gives relative values, sensitive to temperature and humidity; for
correct interpretation, calibration is performed (determining R0 in clean
air) and, if needed, temperature/humidity correction is applied based on
DHT11 data.

#### 1.5.10 Energy balance (practical notes)

Main energy consumers: the MQ-2 heater, the Nano (~20–50 mA in active
mode), LCD backlight (depending on mode).

In standalone operation, the capacity of the 1s5p battery pack (five cells
in parallel) given average consumption may allow roughly 10 hours of
operation, if the display backlight is not used continuously.

At the structural-diagram level, the system follows a traditional layout
for educational/household monitoring devices: power source → central
controller (Arduino Nano) → sensors (DHT11, MQ-2) → output interface (LCD
over I2C) → auxiliary indicators. The key implementation aspects are
correct power organization for standalone operation (TP4056 + Li-Pol +
boost), correct MQ-2 connection and calibration, ensuring measurement and
filtering timing intervals, saving settings in EEPROM, and overall
industrial/educational usability of the design.

## 2. Special part

### 2.1 Purpose of the microcontroller

The microcontroller in the developed system performs the function of the
central computing element, coordinating the operation of all connected
sensors, indicators, and auxiliary modules. Its main purpose is to read
sensor data, process it, compare it against threshold values, and
generate the corresponding signals for the indicators or the alarm
system.

This project uses the ATmega328P microcontroller, integrated on the
Arduino Nano board. Thanks to its compact size and broad library support,
it is an optimal choice for an air quality monitoring system. Its
capabilities allow reading analog values from the MQ-2 sensor through the
built-in analog-to-digital converter, as well as receiving digital signals
from the DHT11 temperature/humidity sensor. In addition, the controller
forms the commands for displaying measurement results on the LCD and
controls the alarm signals (LED and buzzer).

An important task of the microcontroller is ensuring energy-efficient
operation of the system, particularly during standalone operation from
the lithium-polymer battery. Software methods can implement reduced power
consumption modes, optimize sensor polling frequency, and disable
secondary functions in case of low battery charge.

The microcontroller in this device acts as the control center, providing
data collection, analysis, storage of calibration parameters, and a
convenient user interface. It is precisely because of this role that the
system becomes universal, flexible, and capable of future functional
expansion.

### 2.2 Technical characteristics of the microcontroller

The ATmega328P microcontroller, the core element of the Arduino Nano
board, belongs to the 8-bit AVR-architecture microcontroller family from
Microchip Technology. It is built on an enhanced RISC architecture, which
allows most instructions to execute in a single clock cycle, providing
high efficiency at a relatively low clock frequency. This makes it
suitable for building embedded systems with constrained power
consumption.

Main technical characteristics of the ATmega328P:

- architecture: 8-bit AVR RISC;
- number of general-purpose registers: 32, allowing efficient execution
  of arithmetic and logic operations;
- clock frequency: up to 20 MHz (the Arduino Nano uses a 16 MHz crystal);
- program memory (Flash): 32 KB (0.5 KB of which is used by the Arduino
  bootloader);
- RAM (SRAM): 2 KB, used to store sensor data and intermediate computation
  results;
- non-volatile EEPROM: 1 KB, which can be used to store calibration
  coefficients or system settings;
- number of I/O lines: 23 digital pins, 14 of which can operate as
  digital I/O, 6 of those supporting PWM signals;
- number of analog inputs: 6 channels with 10-bit resolution, allowing
  connection of analog-output sensors such as the MQ-2.

Hardware interfaces:

- UART (serial port for data exchange or programming);
- SPI (serial peripheral interface for fast communication with other
  chips);
- I2C/TWI (interface for connecting sensors and modules, e.g. the 16×2
  LCD);
- supply voltage: 1.8–5.5 V; the Arduino Nano uses a 5 V operating
  voltage;
- current consumption: from single-digit microamps in sleep mode to
  15–20 mA during active operation;
- operating temperature range: from −40 °C to +85 °C, allowing use in both
  domestic and industrial conditions.

A notable feature of the microcontroller is the presence of hardware
timers (two 8-bit and one 16-bit), allowing precise time measurement,
pulse generation, or control of periodic processes. The ATmega328P also
has a built-in watchdog timer, which ensures system reliability and
prevents the program from hanging.

The Arduino Nano, built around the ATmega328P, is additionally equipped
with a voltage regulator that allows power to be supplied through the VIN
pin (7–12 V range) or through the mini-USB port. A built-in USB-UART
converter (based on a CH340 or FT232RL chip, depending on the board
revision) allows programming the microcontroller and exchanging data with
a computer.

To improve energy efficiency, the microcontroller supports several
power-saving modes (Idle, Power-down, Standby), allowing the system to be
adapted for standalone operation from a lithium-polymer battery. This is
critically important for the developed device, since it must be able to
operate in mobile mode without a network connection.

Thus, the technical characteristics of the ATmega328P fully satisfy the
requirements of the coursework. It provides a sufficient level of
performance for processing data from the DHT11 and MQ-2 sensors, supports
the necessary interfaces for connecting peripheral devices, and is
distinguished by low power consumption, making it a versatile solution for
building indoor air quality monitoring systems.

### 2.3 Analysis of the microcontroller's structural diagram and pin functions

The ATmega328P's structural diagram reflects the internal organization of
its functional blocks and their interconnections. The central element is
the 8-bit AVR RISC core, which interacts with the system's data, address,
and control buses.

Main blocks of the structural diagram:

- central processing unit (CPU) — performs arithmetic and logic
  operations, controls overall system operation; contains 32
  general-purpose registers directly connected to the arithmetic-logic
  unit (ALU);
- program memory (Flash, 32 KB) — used to store the user's firmware;
  supports rewriting;
- RAM (SRAM, 2 KB) — temporarily stores data, variables, intermediate
  computation results;
- non-volatile memory (EEPROM, 1 KB) — allows storage of parameters and
  settings that must remain available after power-off;
- I/O system (I/O ports) — consists of three main ports (B, C, D), which
  can be configured as inputs or outputs;
- analog-to-digital converter (ADC) — 10-bit, with 6 channels for
  converting analog signals to a digital code;
- timers/counters — two 8-bit and one 16-bit, used for time measurement,
  PWM signal generation, and process control;
- communication interfaces — include UART (serial port), SPI, and I2C
  (TWI), which provide communication with peripheral devices;
- interrupt system — allows fast reaction to external and internal
  events;
- watchdog timer — automatically restarts the microcontroller if the
  program hangs;
- clock system — supports operation from an external crystal oscillator
  (16 MHz) or the internal RC oscillator.

Functional pin assignment of the ATmega328P (in the DIP-28 package, used
similarly on the Arduino Nano):

- VCC (pins 7, 20) — main microcontroller power (5 V);
- GND (pins 8, 22) — ground;
- AVCC (pin 20) — power for the analog section (ADC);
- AREF (pin 21) — reference voltage input for the ADC;
- PB0–PB5 (pins 14–19) — port B, used as digital I/O, supports SPI (MISO,
  MOSI, SCK, SS);
- PC0–PC5 (pins 23–28) — port C, 6 analog inputs ADC0–ADC5;
- PD0–PD7 (pins 2–9) — port D, used as digital I/O, including UART (RX —
  PD0, TX — PD1) and PWM;
- RESET (pin 1) — microcontroller reset signal;
- XTAL1, XTAL2 (pins 9, 10) — connection for an external crystal
  oscillator for clocking.

The ATmega328P's structure is built to provide a balance between
computing power and low power consumption. Thanks to its wide range of
interfaces and multi-function I/O ports, it is a flexible solution for
connecting sensors, actuators, and organizing data exchange.

### 2.4 Justification of the component base

When designing a microprocessor system, an important step is selecting
the component base, which determines the device's functional
capabilities, reliability, and energy efficiency. The choice of components
is based on system requirements, operating conditions, and economic
feasibility.

The main element is the ATmega328P microcontroller, used on the Arduino
Nano platform. Its selection is justified by the following factors:
sufficient performance (16 MHz clock), the required amount of memory
(32 KB Flash, 2 KB SRAM, 1 KB EEPROM), support for a wide range of
interfaces (UART, SPI, I2C), low power consumption, availability, and
ease of programming. The presence of hardware timers, a 10-bit ADC, and an
interrupt system allows efficient processing of sensor signals.

Sensors are used to collect information from the surrounding environment.
For example, temperature and humidity sensors based on capacitive or
resistive principles (DHT22, similar devices) provide accurate
environmental measurements. Gas sensors (MQ-series) operate based on
changes in the conductivity of the sensing layer when interacting with
specific gas molecules. Analog signals from such sensors are converted to
digital form using the microcontroller's integrated ADC.

The power system is designed with a choice of source. For standalone
operation, a lithium-polymer battery in 1s5p configuration is used,
providing increased capacity and stable device operation. A TP4056 module
is used for charging and parameter control, supporting overcharge and
deep-discharge protection. As an alternative, power can be supplied
through the mini-USB port, which is also used for programming the
microcontroller.

Additional elements used to ensure correct microcontroller operation
include: a 16 MHz crystal oscillator for accurate clocking, voltage
regulators for matching power sources, as well as resistors, capacitors,
and other auxiliary passive components for forming correct electrical
operating conditions.

Thus, the choice of component base is optimal from the standpoint of
functionality, availability, and ease of integration. Using the Arduino
Nano with the ATmega328P, combined with a set of sensors and a flexible
power system, allows building a universal and reliable microprocessor
system suitable for both educational and practical applications.

### 2.5 Operating principle at the level of the electrical schematic

The electrical schematic of the air quality analysis microprocessor
system is a set of nodes interacting with each other to perform the task
of measuring environmental parameters and displaying the results. Each
element of the circuit performs a separate function, but together they
form a complete system capable of operating both in stationary and
standalone mode.

The device's main node is the ATmega328P microcontroller, placed on the
Arduino Nano board. It receives signals from the sensors, processes them,
and controls the other system components. Digital and analog lines from
the sensors are connected to it.

The DHT11 temperature/humidity sensor connects to one of the
microcontroller's digital I/O pins. It operates on its own data-transfer
protocol, where a sequence of pulses of varying duration encodes the
temperature and humidity values. For correct operation, the data line is
fitted with a pull-up resistor that holds the logic level at rest and
prevents spurious pulses. The DHT11 is powered from the common 5 V bus.

The MQ-2 gas sensor connects to one of the microcontroller's analog
inputs. It consists of a heating element and a metal-oxide sensing layer,
whose conductivity changes depending on the concentration of combustible
gases in the air. This produces an analog signal fed to the
microcontroller's ADC. The built-in 10-bit ADC converts the voltage to a
digital value, which is then analyzed in software. For stable MQ-2
operation, the circuit includes a load resistor that properly shapes the
output signal.

A 16×2 liquid-crystal display, connected to the microcontroller through
the I2C interface, is used to indicate the results. Using it allows data
transfer over just two lines: SDA (data) and SCL (clock pulses). This
substantially reduces the number of wires in the circuit and simplifies
routing. The display is powered from the same 5 V bus as the other
components.

The power system is designed with standalone operation in mind. A
lithium-polymer battery in 1s5p configuration is used for this, providing
increased capacity and a longer device runtime. The battery is charged
through a TP4056 module, which performs charge-process control and
overload protection. In stationary mode, power is supplied directly
through the Arduino Nano's mini-USB port. This same port is used for
programming the microcontroller, making it versatile.

Auxiliary elements of the circuit include a 16 MHz crystal oscillator,
which provides a stable clock frequency for the microcontroller. Voltage
regulators, capacitors for interference filtering, resistors for forming
logic levels and protecting inputs, and elements to prevent system
overload are also used.

The device's operating principle at the schematic level can be described
as follows. The sensors convert physical parameters of the surrounding
environment into corresponding electrical signals. The DHT11 forms a
digital code that goes to the microcontroller, while the MQ-2 produces an
analog signal that passes through the ADC. The microcontroller receives
this data, analyzes it, and forms the information to display on the
screen. The display, in turn, outputs the numerical values of
temperature, humidity, and gas-pollution level in a user-friendly form.
The power system ensures uninterrupted operation regardless of whether
the USB port or the standalone source is used.

The schematic ensures coordinated operation of the sensor elements, the
microcontroller, the indicator module, and the power system, creating a
complete device for indoor air quality monitoring.

*[Figure: see `diagrams/schematic.png` — original schematic, title block
with personal names/group number removed; see Editor's notes.]*

### 2.6 User documentation

**Device name:** Microprocessor-based air analysis system

**Purpose:** The device is designed to measure the main parameters of
indoor air: temperature, humidity, and gas concentration. The system
allows the user to assess air quality, which directly affects health,
comfort, and productivity indoors.

**Technical characteristics:**

- Microcontroller: ATmega328P (Arduino Nano)
- Temperature/humidity sensor: DHT11 (digital signal)
- Analog gas sensor: MQ-2
- Display: 16×2 LCD with I2C interface
- Power: USB or battery
- Clock frequency: 16 MHz
- Input signals: digital (DHT11), analog (MQ-2)
- Output: data display on screen

**Operating principle and interpretation of results:** The device
collects information from the sensors and displays it on the screen. The
temperature sensor determines the thermal state of the air and shows it
in degrees Celsius. The humidity sensor measures the relative humidity of
the air as a percentage, allowing assessment of indoor climate comfort
and safety. The analog MQ-2 gas sensor reacts to the presence of various
gases (methane, propane, carbon monoxide, smoke), producing a variable
voltage that is shown in relative units, allowing assessment of the
presence of potentially dangerous concentrations.

**User interface:** The display shows three main parameters: temperature,
humidity, and gas level. Parameters update in real time, allowing the user
to track changes in room conditions and respond promptly to deteriorating
air quality. Gas values are given in relative units, where a higher number
signals rising concentration of harmful or combustible gases.

**Connection and use:** The device can run either from a USB port or from
a battery, providing mobility and use in different conditions. To operate
the device, it is enough to switch it on; it automatically starts
measuring and displaying results on the screen. The user receives clear
and understandable information about air condition, allowing timely
action to maintain a safe and comfortable environment.

When using the air analysis microprocessor system, certain rules must be
followed to ensure safe operation and prevent device damage.

*Power:*

- use only recommended power sources — 5 V USB or the corresponding
  battery;
- do not connect the device to voltage sources exceeding the permissible
  range, to avoid damaging the electronics;
- make sure connectors are properly seated, without skew or contact
  damage.

*Device placement:*

- place the device on a level, stable surface to prevent tipping or
  falling;
- avoid placing it near strong heat sources (radiators, stoves) or cold
  surfaces, which can distort temperature and humidity readings;
- ensure adequate ventilation for correct sensor operation, avoiding
  enclosed or dusty spaces.

*Operating limitations:*

- do not allow water, liquids, or other conductive substances to get on
  the sensors or board, as this can cause a short circuit or damage to
  components;
- do not use the device in environments with a high concentration of
  aggressive chemicals, dust, or gases that could damage the sensors;
- avoid mechanical shocks, vibration, or pressing on the board and
  display, which could cause them to fail.

*Maintenance and care during use:*

- power off before moving the device or removing it from its installation
  location;
- regularly check the external condition of the enclosure, and when using
  USB power, check the cable for damage;
- do not disassemble the device yourself without the necessary knowledge
  and tools, as this could disrupt the operation of the sensors and
  electronics.

*Sensor use:*

- the DHT11 and MQ-2 sensors are sensitive to temperature, humidity, and
  gases, so direct heat sources or smoke should not be allowed to affect
  the sensor during operation;
- for correct data display, a stable connection between sensors and board
  must be ensured, avoiding interrupted contacts.

*Summary:* Following these recommendations ensures safe and long-term
operation of the device, prevents damage to electronic components and
sensors, and ensures reliable readings of temperature, humidity, and gas
concentration indoors.

## Conclusion

As a result of completing this coursework, a microprocessor-based air
analysis system was developed on the ATmega328P, providing measurement of
temperature, humidity, and gas concentration indoors. The choice of
component base was justified, and the electrical schematic and structural
interaction diagram of the system's components were developed.

The system uses the digital DHT11 sensor for temperature and humidity
measurement and the analog MQ-2 sensor for estimating the concentration of
combustible and harmful gases. Measurement results are shown on a 16×2
liquid-crystal display over the I2C interface, providing convenient and
clear monitoring of air condition.

User documentation was developed along with recommendations for safe use,
allowing the device to be operated without risk of damage while obtaining
reliable data.

The work performed confirmed the relevance of developing microprocessor
systems for indoor air quality control, as well as their practical
significance for maintaining a healthy and comfortable environment
indoors. The completed work creates a basis for further development of
air monitoring systems, their modernization, and integration with other
automated control systems. The developed microprocessor system is not
just an air monitoring system but also a platform for building a smart
home.

During the coursework, I learned the operating principles of temperature,
humidity, and gas sensors, studied the process of integrating sensors with
a microcontroller, developed the electronic circuit, and learned how to
design user documentation for microprocessor devices.

## Sources

1. ATmega328P datasheet. URL: https://www.alldatasheet.com/view.jsp?Searchword=Atmega328p (accessed 10 October)
2. DHT11 temperature/humidity sensor reference. URL: https://navody.dratek.cz/navody-k-produktum/teplotni-senzor-dht11.html (accessed 10 October)
3. I2C 16×2 LCD module reference. URL: https://dratek.cz/arduino/1570-iic-i2c-display-lcd-1602-16x2-znaku-lcd-modul-modry (accessed 10 October)
4. Indoor microclimate parameters and requirements (regulatory reference). URL: https://navyflex.com.ua/mikroklimat-v-budynku-parametry-vymogy-i-kontrol (accessed 10 October)
5. Indoor gas/CO control reference. URL: https://pragmatic.com.ua/kontrol_uglekislogo_gaza_v_pomeshhenijakh (accessed 10 October)
6. (Source omitted — original entry was a private Google Drive link; see Editor's notes.)
7. AVR microcontroller regulator reference. URL: https://cz.rs-online.com/web/p/mikroregulatory/1310270 (accessed 10 October)
8. Arduino Nano V3.0 (ATmega328, CH340 clone) product page. URL: https://dratek.cz/arduino/1164-arduino-nano-v3-0-atmega328-16m-5v-ch340g-klon.html (accessed 10 October)
9. Li-ion/USB-C charging board product page. URL: https://dratek.cz/arduino/34679-nabijeci-deska-li-ion-baterii-usb-c.html (accessed 10 October)
10. LiPol battery product page. URL: https://www.laskakit.cz/geb-lipol-baterie-102035-650mah-3-7v-jst-sh-2-0 (accessed 10 October)
11. MQ-2 combustible gas sensor reference. URL: https://dratek.cz/arduino/1074-mq2-mq-2-senzor-horlavych-plynu-propanu-metanu-butanu-vodiku.html (accessed 10 October)
12. Xiaomi Smart Air Quality Monitor reference. URL: https://stovefancompany.com/smart-air-quality-meter/ (accessed 10 October)
13. Awair Element reference. URL: https://vrealmatic.com/smart-home/awair-element (accessed 10 October)
14. IQAir AirVisual Pro product page. URL: https://www.iqair.com/products/air-quality-monitors (accessed 10 October)
15. Netatmo Smart Indoor Air Quality Monitor reference. URL: https://meteorologicke-stanice.heureka.cz/netatmo-nhc-ec/#prehled/ (accessed 10 October)

## Editor's notes on this translation

1. **Anonymization.** Student name → "Damir"; advisor and committee-head
   surname → "[redacted]" (the original advisor and the head of the
   cyclic commission appear to be the same person, signing in three roles
   on the task sheet and title block); group number → "[redacted]". The
   college name is kept, as in the already-published diploma repo
   (`BreraDMR/EQF_L5`).
2. **Schematic title block.** `diagrams/schematic.png` is the original
   КОМПАС-style schematic (`Circuit.pdf` in the source archive), with the
   title block (containing the same student/advisor/group fields as
   above) cropped out. The circuit itself — Arduino Nano, LCD 16×2, MQ-2,
   pull-up resistor, power rails — is unchanged from the original.
3. **Mislabeled figure.** The original report's Figure 1.3, captioned
   "блок-схема коду" ("code block diagram"), is not a flowchart of the
   firmware logic — it's the same component wiring diagram as Figure 1.4
   (the full schematic), just drawn with fewer details (missing the
   load resistor and the AVCC/Vcc breakout). No actual code or flowchart
   appears anywhere in the original document; section 1.5.7's "program
   algorithm" is a prose description only. This is reflected directly in
   this translation by noting both figures as wiring diagrams.
4. **MQ-2 mislabeled as "MOISTURE SENSOR" on the schematic.** The
   schematic's component symbol for the MQ-2 gas sensor (`SEN1`) carries
   the label "MOISTURE SENSOR" — apparently the closest generic symbol
   available in the schematic editor's library, not an indication that a
   different sensor was actually used. The surrounding text and bill of
   materials consistently describe it as the MQ-2 gas sensor, which is
   what this translation follows.
5. **Source 6 omitted.** One reference in the original bibliography
   (`Перелік рекомендованих джерел`/`Перелік використаних джерел`, item on
   indoor gas hazards) pointed to a private Google Drive file URL,
   inappropriate to keep in a public repository; it has been omitted
   from this translation's source list (now ends at 15 instead of 17, the
   other gap being the renumbering itself).
6. **No firmware in the original.** As with the Cisco coursework
   (repo `BreraDMR/enterprise-network-cisco`), this coursework's
   explanatory note describes sensor logic and a measurement algorithm in
   prose only — there is no actual Arduino sketch, source file, or
   compiled firmware anywhere in the original submission (only a `.pdf`
   report, a schematic, and a presentation). The `example-code/` directory
   in this repo is new code written for the portfolio, explicitly marked
   as such — see [`example-code/README.md`](../example-code/README.md).
7. **Component photos not reproduced.** The original report illustrates
   each component (ATmega328P chip, Arduino Nano board, TP4056 charger,
   LiPol battery, DHT11, MQ-2, 16×2 LCD) with stock product photos taken
   from the vendor pages cited in the bibliography (sources 1, 8–13).
   These are not original artwork and are not reproduced here; the
   schematic diagram is kept instead since it is the project's own
   design work.
