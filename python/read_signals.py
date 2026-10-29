import tone
import goertzel
import matplotlib.pyplot as plt

correct = {}

with open("c/signals.txt") as f:   
    for line in f:                 
        parts = line.split()       
        key = parts[0]
        snr = int(parts[1])
        samples = [float(x) for x in parts[2:]]

        if key == tone.detect(samples, goertzel.energy):
            correct[snr] = correct.get(snr,0)+1

    for snr in correct:
        print(f"snr {snr}: {correct[snr]}/200 correct")

    snrs = sorted(correct)                 
    accs = [correct[s] / 200 for s in snrs] 
    plt.plot(snrs, accs, marker="o")
    plt.xlabel("SNR (dB)")
    plt.ylabel("detection accuracy")
    plt.title("DTMF Goertzel detector, 0.1 s tone, fs = 8 kHz")
    plt.grid(True)
    plt.savefig("accuracy_vs_snr.png", dpi=150)
