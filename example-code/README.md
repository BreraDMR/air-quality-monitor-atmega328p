# Example code

The original coursework (`docs/report.md`) describes the sensor wiring and
a measurement algorithm in prose only (section 1.5.7) — there is no
Arduino sketch, source file, or compiled firmware anywhere in the original
submission, only a `.pdf` report, a schematic, and a presentation.
Everything in this folder was **written for this GitHub version, after the
original coursework was submitted** — it is not a transcription of
anything that was handed in for a grade.

## What's here

- [`air_quality_monitor/air_quality_monitor.ino`](air_quality_monitor/air_quality_monitor.ino) —
  an Arduino sketch implementing the algorithm described in
  `docs/report.md` 1.5.7: read DHT11 (temperature/humidity) and MQ-2 (gas,
  via ADC), calibrate the MQ-2 baseline (R0) in clean air on first boot and
  cache it in EEPROM, display readings on the 16×2 I2C LCD, and drive an
  LED/buzzer alarm past set thresholds. Pin mapping matches
  `diagrams/schematic.png`.
- [`mq2_calc.py`](mq2_calc.py) — a Python mirror of the sketch's MQ-2
  voltage→resistance math (`Vout → Rs → Rs/R0`), since the `.ino` itself
  can't be unit-tested without a board attached.
- [`tests/`](tests/) — unit tests for `mq2_calc.py`.

## Running it

No third-party Python dependencies — standard library only.

```sh
cd example-code
python3 -m unittest discover -s tests -v   # 7/7 pass
python3 mq2_calc.py                        # prints example Rs/R0 values
```

The `.ino` file needs the Arduino IDE (or `arduino-cli`) plus the
**DHT sensor library** (Adafruit) and **LiquidCrystal_I2C** libraries, and
an actual Nano + DHT11 + MQ-2 + LCD wired up per the schematic to run. It
has **not** been compiled, flashed, or tested against real or simulated
hardware — there's no lab or device behind this project, original or
otherwise. Treat it as a worked example of how the report's described
algorithm maps to Arduino C++, not as code that has been run.
