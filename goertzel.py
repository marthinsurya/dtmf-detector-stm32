import tone
import math

FS = tone.FS

def energy(signal, f):
    s1 = 0
    s2 = 0
    coeff = 2*math.cos(2*math.pi*f/FS)

    for s in signal:
        s0 = s + coeff*s1 - s2
        s2 = s1
        s1 = s0

    return s1**2 + s2**2 - coeff*s1*s2

if __name__ == "__main__":
    from tone import make_signal, tone_energy
    s = make_signal("5", 0.1)
    print(tone_energy(s, 770), energy(s, 770))