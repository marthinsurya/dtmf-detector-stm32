#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FS 8000.0f
#define PI_F 3.14159265f
#define NUM_TONES 4

int16_t float_to_q15(float x) {
    float scaled = x * 32768.0f;
    if (scaled > 32767.0f) {
        scaled = 32767.0f;
    }
    if (scaled < -32768.0f) {
        scaled = -32768.0f;
    }
    return (int16_t)roundf(scaled);
}

static const float f_low[NUM_TONES]  = {697.0f, 770.0f, 852.0f, 941.0f};
static const float f_high[NUM_TONES] = {1209.0f, 1336.0f, 1477.0f, 1633.0f};

int main(void) {    
    for (int i = 0; i < NUM_TONES; i++) {
        int16_t coeff_half_low = float_to_q15(cosf(2*PI_F*f_low[i]/FS));
        int16_t coeff_half_high = float_to_q15(cosf(2*PI_F*f_high[i]/FS));
        printf("i = %d, coeff_half_low = %d, coeff_half_high = %d\n", i, coeff_half_low, coeff_half_high);
    }
    return 0;
}