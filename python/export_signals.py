import tone
import random

FS = 8000
duration_s = 0.1

random.seed(0) #random gaussian noise with targeted SNR
snr_list = (20, 0, -10, -20)
with open("c/signals.txt", "w") as f:
    for snr in snr_list:
        for row in tone.KEYS:
            for key in row:
                signal = tone.make_signal(key, duration_s)
                noisy_s = tone.add_noise_snr(signal, snr)
                samples = " ".join(f"{x:.6f}" for x in noisy_s)
                f.write(f"{key} {snr} {samples}\n")

