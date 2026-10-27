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
    return (int32_t)a*b;
}

int main(void) {
    int16_t x[1] = {-1, 0.5};

    for (int i=0; i<2; i++){
        int32_t z = q15_mul(x[i], x[i]);
        printf("val = %d\n", z);
    }

    return 0;
}