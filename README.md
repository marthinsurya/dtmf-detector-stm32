# DTMF tone detector: Python → C → STM32

Detects which keypad key was pressed from its DTMF tone pair in noise. The same detection method is built three times, each under tighter constraints, to measure what each constraint costs and how much of it design choices win back.

## Steps and goals
1. **Python reference** (no hardware limits): tone generator, noise, detector, accuracy vs SNR. This is the best result the later steps are compared against.
2. **C on PC** (gcc): float first, then Q15 fixed-point. Goal: error vs Python, and fixing fixed-point problems (overflow, coefficient rounding, block length).
3. **STM32F407**: keypad -> DAC tone -> jumper wire -> ADC -> detector, float and Q15. Goal: accuracy and cycles per block (DWT counter) against the real-time budget, with real ADC/DAC effects included.

## Status
- [x] Step 1a: Signal generation & direct correlation detector in Python (`tone.py` - generator, noise, direct energy detector `tone_energy`, accuracy vs SNR)
- [x] Step 1b: Goertzel method detector in Python (`goertzel.py`), same accuracy table as the direct detector on identical test data; this is the version ported to C
- [ ] Step 2: C on PC (float `read_signals.c`, Q15 `goertzel_q15.c`): both detectors done and compared with Python on the same 1400 signals (results below); release v0.3 pending
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

Accuracy drops as noise increases: 100% at -10 dB and above, 88% at -15 dB, 39.5% at -20 dB, 21% at -25 dB, and 11.5% at -30 dB, about twice chance (6.25%).

| SNR (dB) | Python (hits of 200) |
|---|---|
| 0 | 200 |
| -5 | 200 |
| -10 | 200 |
| -15 | 176 |
| -20 | 79 |
| -25 | 42 |
| -30 | 23 |

The Goertzel detector (step 1b) gives the same table on the same noisy signals. Its energies match the direct method (step 1a) to rounding error (relative difference ~1e-12), so this table is the baseline reference for steps 2 and 3.

## How to reproduce
Run from the repo root:
```bash
python python/export_signals.py
python python/read_signals.py
gcc -Wall -Wextra -o c/read_signals c/read_signals.c -lm
gcc -Wall -Wextra -o c/goertzel_q15 c/goertzel_q15.c -lm
./c/read_signals
./c/goertzel_q15
```
`export_signals.py` writes the test signals to `c/signals.txt`. `read_signals.py` and the two C programs print hits per SNR in the same format, so the outputs can be compared directly; `read_signals.py` also saves `accuracy_vs_snr.png`.

### Step 2 - Fixed-Point implementation
Test data: 7 SNRs x 200 trials = 1400 signals, written to `c/signals.txt` (not in git; generate it with `python python/export_signals.py`, see How to reproduce).

The table shows hits out of 200 trials per SNR for the Goertzel detector in noise:

| SNR (dB) | Python & C float | C Q15 |
|---|---|---|
| 0 | 200 | 200 |
| -5 | 200 | 200 |
| -10 | 200 | 199 |
| -15 | 176 | 161 |
| -20 | 79 | 60 |
| -25 | 42 | 30 |
| -30 | 23 | 20 |

All three use the same 1400 signals, and Python and C float give identical detection. Q15 loses accuracy at low SNR, starting at -10 dB and largest at -20 dB (9.5 percentage points). Over all 1400 signals Q15 averages 3.6 percentage points lower accuracy than float (50 more misses). The likely cause is the input scaling of 0.25, which reduces the signal's resolution (fewer bits).
