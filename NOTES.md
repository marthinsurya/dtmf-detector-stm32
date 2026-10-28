# GLOSSARY
DTMF -  Dual-Tone Multi-Frequency

# Step 2 Notes
Q15 Goertzel, first attempt: state reached ±2e6 (22 bits), overflowing int16; q15_mul(int16) silently truncated an int32 state.