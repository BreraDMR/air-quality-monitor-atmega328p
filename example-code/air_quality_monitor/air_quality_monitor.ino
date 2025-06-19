/*
 * Indoor air quality monitor — DHT11 + MQ-2 + 16x2 I2C LCD on an
 * Arduino Nano (ATmega328P).
 *
 * Written for the GitHub portfolio version of this coursework — the
 * original submission has no firmware, only a prose description of this
 * algorithm (see docs/report.md, section 1.5.7) and the schematic this
 * sketch follows (diagrams/schematic.png). Not part of the graded work.
 *
 * Wiring (matches diagrams/schematic.png):
 *   DHT11 data  -> D2  (4.7-10k pull-up to 5V)
 *   MQ-2 Vout   -> A0
 *   LCD SDA/SCL -> A4/A5 (I2C, PCF8574 backpack, address 0x27)
 *   Buzzer      -> D3
 *   Alarm LED   -> D4
 *
 * Libraries (Arduino Library Manager):
 *   - DHT sensor library (Adafruit)
 *   - LiquidCrystal_I2C (Frank de Brabander / marcoschwartz fork)
 */

#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define MQ2_PIN A0
#define BUZZER_PIN 3
#define ALARM_LED_PIN 4

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// MQ-2 load resistor on the sensor module, per docs/report.md 1.5.5.
#define RL_OHMS 5000.0f
#define ADC_VREF 5.0f
#define ADC_MAX 1023.0f

// EEPROM layout: calibrated R0 (float, 4 bytes) at address 0.
#define EEPROM_R0_ADDR 0
#define R0_UNSET_SENTINEL -1.0f

// Alarm thresholds (per docs/report.md 1.5.7 "threshold check").
#define TEMP_ALARM_C 35.0f
#define HUMIDITY_ALARM_PCT 85.0f
#define GAS_RATIO_ALARM 1.5f  // Rs/R0 below this means rising gas concentration

// Calibration: how long to average MQ-2 readings in clean air on first boot.
#define CALIBRATION_SAMPLES 50
#define CALIBRATION_SAMPLE_DELAY_MS 200

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

float r0 = R0_UNSET_SENTINEL;

float readR0FromEeprom() {
  float value;
  EEPROM.get(EEPROM_R0_ADDR, value);
  return value;
}

void writeR0ToEeprom(float value) {
  EEPROM.put(EEPROM_R0_ADDR, value);
}

// Vout (V) -> sensor resistance Rs (ohm), per docs/report.md 1.5.5.
float mq2VoutToRs(float voutVolts) {
  if (voutVolts <= 0.0f) {
    voutVolts = 0.001f;  // avoid divide-by-zero on a disconnected sensor
  }
  return RL_OHMS * (ADC_VREF / voutVolts - 1.0f);
}

float mq2ReadVout() {
  int raw = analogRead(MQ2_PIN);
  return (raw / ADC_MAX) * ADC_VREF;
}

// Calibrate R0 in (assumed) clean air. Run once on first boot; the result
// is cached in EEPROM so later boots skip this.
float calibrateR0() {
  float rsSum = 0.0f;
  for (int i = 0; i < CALIBRATION_SAMPLES; i++) {
    rsSum += mq2VoutToRs(mq2ReadVout());
    delay(CALIBRATION_SAMPLE_DELAY_MS);
  }
  return rsSum / CALIBRATION_SAMPLES;
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ALARM_LED_PIN, OUTPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Air monitor");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  r0 = readR0FromEeprom();
  if (r0 <= 0.0f || isnan(r0)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Calibrating MQ-2");
    lcd.setCursor(0, 1);
    lcd.print("Keep air clean");
    r0 = calibrateR0();
    writeR0ToEeprom(r0);
  }

  lcd.clear();
}

void setAlarm(bool active) {
  digitalWrite(ALARM_LED_PIN, active ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, active ? HIGH : LOW);
}

void loop() {
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();

  float vout = mq2ReadVout();
  float rs = mq2VoutToRs(vout);
  float gasRatio = rs / r0;  // falls below 1 as gas concentration rises

  bool dhtOk = !isnan(humidity) && !isnan(tempC);

  lcd.setCursor(0, 0);
  if (dhtOk) {
    lcd.print("T:");
    lcd.print(tempC, 1);
    lcd.print("C H:");
    lcd.print(humidity, 0);
    lcd.print("% ");
  } else {
    lcd.print("DHT11 read err  ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Gas ratio:");
  lcd.print(gasRatio, 2);
  lcd.print("  ");

  bool alarm = (dhtOk && (tempC >= TEMP_ALARM_C || humidity >= HUMIDITY_ALARM_PCT))
               || (gasRatio <= GAS_RATIO_ALARM);
  setAlarm(alarm);

  delay(1000);  // DHT11 needs >=1s between reads (docs/report.md 1.5.4)
}
