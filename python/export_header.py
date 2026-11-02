import tone

FS = 8000
duration_s = 0.1
snr_list = (0, -5, -10, -15, -20, -25, -30)

sig = tone.make_signal('5', duration_s)         
sig = tone.add_noise_snr(sig, 10)

with open("../board/blink/Core/Inc/test_signal.h", "w") as f:
    f.write("const float test_signal[800] = {\n")
    for v in sig:
        f.write(f"{v:.6f}f,\n")
    f.write("};\n")