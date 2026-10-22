import math
import random

FS = 8000
F_LOW = (697, 770, 852, 941)
F_HIGH = (1209, 1336, 1477, 1633)
KEYS = ("123A", "456B", "789C", "*0#D")

def key_tone(fl, fh, n_samples):
    samples = []
    for n in range(n_samples):
        value = math.sin(2*math.pi*fl*n/FS) + math.sin(2*math.pi*fh*n/FS)
        samples.append(value)
    return samples

def key_freqs(row, col):
    return F_LOW[row], F_HIGH[col]

def freqs_for(key):
    for row, line in enumerate(KEYS):
        col = line.find(key)
        if col != -1:
            return key_freqs(row, col)
    raise ValueError("bad key")

def make_signal(key, duration_s):
    n_samples = int(FS*duration_s)
    fl, fh = freqs_for(key)
    return key_tone(fl, fh, n_samples)

def add_noise(signal, sigma):
    out = []
    for s in signal:
        noisy = s + random.gauss(0, sigma)
        out.append(noisy)
    return out


print(add_noise([0,0,0], 0.5))