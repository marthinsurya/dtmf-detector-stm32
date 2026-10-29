import tone
import random

FS = 8000
duration_s = 0.1
KEYS = "123A456B789C*0#D"
snr_list = (0, -5, -10, -15, -20, -25, -30)

random.seed(0) #random gaussian noise with targeted SNR
trials_no = 200
with open("c/signals.txt", "w") as f:
    for snr in snr_list:
        for _ in range(trials_no):
            key = random.choice(KEYS)
            signal = tone.make_signal(key, duration_s)
            noisy_s = tone.add_noise_snr(signal, snr)
            samples = " ".join(f"{x:.6f}" for x in noisy_s)
            f.write(f"{key} {snr} {samples}\n")

