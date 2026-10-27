#include <stdio.h>
#include <stdint.h>

int16_t float_to_q15(float x) {
    float scaled = x * 32768.0f;
    if (scaled > 32767.0f) {
        scaled = 32767.0f;
    }
    if (scaled < -32768.0f) {
        scaled = -32768.0f;
    }
    return (int16_t)scaled;
}

int main(void) {
    float z[3] = {-3.0f, 1.0f, 2.5f};

    for (int i = 0; i < 3; i++){
        float x = z[i];
        int16_t q = float_to_q15(x);
        float back = q / 32768.0f;
        printf("x = %f, q = %d, back = %f\n", x, q, back);
    }
    return 0;
}