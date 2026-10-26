import matplotlib.pyplot as plt
import tone
import random
import goertzel

snrs = [-30, -25, -20, -15, -10, -5, 0]

random.seed(0)
accs = [tone.accuracy(snr, 200) for snr in snrs]

random.seed(0)
goert_accs = [tone.accuracy(snr, 200, goertzel.energy) for snr in snrs]

print("identical:", accs == goert_accs)
print(snrs, accs)
print(snrs, goert_accs)
plt.plot(snrs, goert_accs, marker="o")
plt.xlabel("SNR (dB)")
plt.ylabel("detection accuracy")
plt.title("DTMF Goertzel detector, 0.1 s tone, fs = 8 kHz")
plt.grid(True)
plt.savefig("accuracy_vs_snr.png", dpi=150)
# plt.show()




