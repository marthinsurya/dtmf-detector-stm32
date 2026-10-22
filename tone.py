import math

fs = 8000

def key_tone(f_low, f_high, n_samples):
    samples = []
    for n in range(n_samples):
        value = math.sin(2*math.pi*f_low*n/fs) + math.sin(2*math.pi*f_high*n/fs)
        samples.append(value)
    return samples

print(key_tone(770, 1336, 8))
