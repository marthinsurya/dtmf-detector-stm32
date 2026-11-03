import tone
import numpy as np

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

# q15 input
INPUT_SCALE = 0.25
sig_arr = np.array(sig)
q = np.clip(np.round(sig_arr * INPUT_SCALE * 32768), a_min=-32768, a_max=32767).astype(np.int16)

with open("../board/blink/Core/Inc/test_signal_q15.h", "w") as f:
    f.write("#include <stdint.h>\n")
    f.write("const int16_t test_signal_q15[800] = {\n")
    for v in q:
        f.write(f"{v},\n")
    f.write("};\n")