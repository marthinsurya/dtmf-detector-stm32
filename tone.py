import math

FS = 8000
F_LOW = (697, 770, 852, 941)
F_HIGH = (1209, 1336, 1477, 1633)

def key_tone(fl, fh, n_samples):
    samples = []
    for n in range(n_samples):
        value = math.sin(2*math.pi*fl*n/FS) + math.sin(2*math.pi*fh*n/FS)
        samples.append(value)
    return samples

def key_freqs(row, col):
    return F_LOW[row], F_HIGH[col]


print(key_tone(770, 1336, 8))

fl, fh = key_freqs(1,1)
print(key_tone(fl, fh, 4))