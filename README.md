# DTMF tone detector: Python → C → STM32

Detects which keypad key was pressed from its DTMF tone pair in noise. The same detection method is built three times, each under tighter constraints, to measure what each constraint costs and how much of it design choices win back.

## Steps and goals
1. **Python reference** (no hardware limits): tone generator, noise, detector, accuracy vs SNR. This is the best result the later steps are compared against.
2. **C on PC** (gcc): float first, then Q15 fixed-point. Goal: error vs Python, and fixing fixed-point problems (overflow, coefficient rounding, block length).
3. **STM32F407**: keypad -> DAC tone -> jumper wire -> ADC -> detector, float and Q15. Goal: accuracy and cycles per block (DWT counter) against the real-time budget, with real ADC/DAC effects included.

## Status
- [x] Step 1a: Signal generation & direct correlation detector in Python (`tone.py` - generator, noise, direct energy detector `tone_energy`, accuracy vs SNR)
- [x] Step 1b: Goertzel method detector in Python (`goertzel.py`), same accuracy table as the direct detector on identical test data; this is the version ported to C
- [ ] Step 2: C on PC (float, Q15)
- [ ] Step 3: STM32F407

## Method
Each DTMF key signal is represented by the sum of two sine waves: one tone each from **Low** and **High** group.
- Low group (697, 770, 852, 941 Hz)
- High group (1209, 1336, 1477, 1633 Hz)
These 8 frequencies give 16 unique pairs of DTMF keys that represent the 16 keys (i.e. 0-9, A-D, #, *).

Noisy signal references were simulated in Python with random seed for reproducibility.

Test Setup:
- SNR range: -30 to 0 dB in 5 dB steps (below 0 dB the noise is louder than the tone)
- Sampling rate = 8 kHz
- Sampling window = 100ms
- Test samples = 200 random keys per SNR point (with random seed defined random.seed(0))
- Noise: Gaussian (random), scaled so signal power / noise power matches the target SNR

The detector measures the signal energy at each of the 8 frequencies and picks the strongest in each group to determine which key was pressed. Energy is computed with the Goertzel algorithm, the standard choice for DTMF: it needs only multiply and add and two state variables per frequency, which reduces the computational demands of the direct approach and makes it better suited to a hardware-efficient implementation (fixed-point integer code on a microcontroller).

## Results
### Step 1 - Python Reference 

Step 1 is the baseline: the signal is processed in floating-point Python with no hardware restrictions, but with noise added. It shows how well the method detects keys at best, so steps 2 and 3 can be compared against it.

![Accuracy vs SNR](accuracy_vs_snr.png)

Accuracy drops as noise increases: 100% at -10 dB and above, 90% at -15 dB, 41.5% at -20 dB, and near chance (6.25%) at -30 dB.

| SNR (dB) | accuracy |
|---|---|
| -30 | 0.07 |
| -25 | 0.155 |
| -20 | 0.415 |
| -15 | 0.9 |
| -10 | 1.0 |
| -5 | 1.0 |
| 0 | 1.0 |

The Goertzel detector (step 1b) gives the same table on the same noisy signals. Its energies match the direct method (step 1a) to rounding error (relative difference ~1e-12), so this table is the baseline reference for steps 2 and 3.

## How to reproduce
```bash
python plot_accuracy.py
```
Prints the table values and saves `accuracy_vs_snr.png`.

### Step 2 - Fixed-Point implementation
Test data was generated for 7 SNR, 200 trials per SNR - total 1400 signals (written to c/signals.txt). 
To generate: run "python python/export_signals.py"