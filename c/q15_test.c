#include <stdio.h>
#include <stdint.h>
#include <math.h>

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

int main(void) {
    float x[3] = {-3, 1, 2.5};

    for (int i=0; i<3; i++){
        int16_t z = float_to_q15(x[i]);
        printf("val = %d\n", z);
    }

    return 0;
}