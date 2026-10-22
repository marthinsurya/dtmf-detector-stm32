import matplotlib.pyplot as plt
import tone
import random

snrs = [-30, -25, -20, -15, -10, -5, 0]
random.seed(0)

accs = []
for snr in snrs:
    acc = tone.accuracy(snr, 200)
    accs.append(acc)

print(snrs, accs)
plt.plot(snrs, accs, marker="o")
plt.xlabel("SNR (dB)")
plt.ylabel("detection accuracy")
plt.title("DTMF Goertzel detector, 0.1 s tone, fs = 8 kHz")
plt.grid(True)
plt.savefig("accuracy_vs_snr.png", dpi=150)
# plt.show()


