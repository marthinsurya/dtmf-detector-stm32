#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define Q_FRAC_BITS 15
#define Q_ONE_I (1 << Q_FRAC_BITS)
#define Q_ONE ((float)Q_ONE_I)

int16_t float_to_q15(float x) {
    float scaled = x * Q_ONE;
    if (scaled > Q_ONE - 1.0f) {
        scaled = Q_ONE - 1.0f;
    }
    if (scaled < -Q_ONE) {
        scaled = -Q_ONE;
    }
    return (int16_t)roundf(scaled);
}

int16_t q15_mul(int16_t a, int16_t b){
    int32_t scaled = a*b >> Q_FRAC_BITS;
    if (scaled > Q_ONE_I - 1) {
        scaled = Q_ONE_I - 1;
    }
    if (scaled < -Q_ONE_I) {
        scaled = -Q_ONE_I;
    }
    return (int16_t)scaled;
}

int main(void) {
    float x[2] = {-1.0, 0.5};

    for (int i=0; i<2; i++){
        int16_t q = float_to_q15(x[i]);
        int16_t z = q15_mul(q, q);
        float y = z/Q_ONE;
        printf("val = %f\n", y);
    }

    return 0;
}