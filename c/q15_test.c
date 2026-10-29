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

int16_t q15_mul(int16_t a, int16_t b){
    int32_t scaled = a*b >> 15;
    if (scaled > 32767) {
        scaled = 32767;
    }
    if (scaled < -32768) {
        scaled = -32768;
    }
    return (int16_t)scaled;
}

int main(void) {
    float x[2] = {-1.0, 0.5};

    for (int i=0; i<2; i++){
        int16_t q = float_to_q15(x[i]);
        int16_t z = q15_mul(q, q);
        float y = z/32768.0f;
        printf("val = %f\n", y);
    }

    return 0;
}