import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from mq2_calc import RL_OHMS, calibrate_r0, gas_ratio, vout_to_rs


class TestVoutToRs(unittest.TestCase):
    def test_half_supply_voltage_gives_rs_equal_to_rl(self):
        # Vout = Vcc/2 means Rs and RL form an equal voltage divider.
        rs = vout_to_rs(2.5, rl_ohms=RL_OHMS, vref=5.0)
        self.assertAlmostEqual(rs, RL_OHMS, places=3)

    def test_lower_vout_means_higher_rs(self):
        rs_high_vout = vout_to_rs(3.0)
        rs_low_vout = vout_to_rs(1.0)
        self.assertGreater(rs_low_vout, rs_high_vout)

    def test_zero_vout_does_not_divide_by_zero(self):
        # A disconnected/shorted sensor shouldn't crash the reading loop.
        rs = vout_to_rs(0.0)
        self.assertGreater(rs, 0.0)


class TestGasRatio(unittest.TestCase):
    def test_ratio_one_when_rs_equals_r0(self):
        self.assertAlmostEqual(gas_ratio(1000.0, 1000.0), 1.0)

    def test_ratio_below_one_when_gas_present(self):
        # Gas lowers Rs below the clean-air baseline R0.
        self.assertLess(gas_ratio(500.0, 1000.0), 1.0)


class TestCalibrateR0(unittest.TestCase):
    def test_calibration_averages_clean_air_samples(self):
        samples = [2.5, 2.5, 2.5]
        r0 = calibrate_r0(samples)
        expected = vout_to_rs(2.5)
        self.assertAlmostEqual(r0, expected, places=3)

    def test_calibration_handles_sensor_noise(self):
        samples = [2.48, 2.5, 2.52]
        r0 = calibrate_r0(samples)
        # Should land close to the noise-free reading at 2.5V.
        self.assertAlmostEqual(r0, vout_to_rs(2.5), delta=50.0)


if __name__ == "__main__":
    unittest.main()
