"""Reference implementation of the MQ-2 voltage-to-resistance math used in
air_quality_monitor/air_quality_monitor.ino (see docs/report.md, 1.5.5).

The Arduino sketch can't be unit-tested directly without a board attached,
so this module mirrors its two pure-math functions in Python, which can be.
It is not loaded by the firmware at runtime -- it exists purely so the
conversion formulas have an automated check.
"""

RL_OHMS = 5000.0
ADC_VREF = 5.0


def vout_to_rs(vout_volts: float, rl_ohms: float = RL_OHMS, vref: float = ADC_VREF) -> float:
    """Convert the MQ-2 module's output voltage to sensor resistance Rs.

    Vout = (RL / (RL + Rs)) * Vcc  =>  Rs = RL * (Vcc / Vout - 1)
    """
    if vout_volts <= 0.0:
        vout_volts = 0.001
    return rl_ohms * (vref / vout_volts - 1.0)


def gas_ratio(rs_ohms: float, r0_ohms: float) -> float:
    """Rs/R0 -- falls below 1 as gas concentration rises above the clean-air
    baseline R0 established during calibration."""
    return rs_ohms / r0_ohms


def calibrate_r0(vout_samples: list[float], rl_ohms: float = RL_OHMS, vref: float = ADC_VREF) -> float:
    """Average Rs over a set of clean-air Vout samples to get baseline R0."""
    rs_values = [vout_to_rs(v, rl_ohms, vref) for v in vout_samples]
    return sum(rs_values) / len(rs_values)


if __name__ == "__main__":
    clean_air_samples = [2.5, 2.48, 2.52, 2.49, 2.51]
    r0 = calibrate_r0(clean_air_samples)
    print(f"Calibrated R0: {r0:.1f} ohm")

    for label, vout in [("clean air", 2.5), ("some gas", 1.8), ("heavy gas", 0.9)]:
        rs = vout_to_rs(vout)
        ratio = gas_ratio(rs, r0)
        print(f"{label:>10}: Vout={vout:.2f}V  Rs={rs:8.1f}  Rs/R0={ratio:.2f}")
