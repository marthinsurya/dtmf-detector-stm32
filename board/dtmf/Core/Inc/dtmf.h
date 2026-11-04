#ifndef DTMF_H
#define DTMF_H


#include <math.h>

#define FS 8000.0f
#define PI_F 3.14159265f
#define NUM_TONES 4

static const float f_low[NUM_TONES]  = {697.0f, 770.0f, 852.0f, 941.0f};
static const float f_high[NUM_TONES] = {1209.0f, 1336.0f, 1477.0f, 1633.0f};

static const char keys[NUM_TONES][NUM_TONES] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

float goertzel_energy(const float *x, int n, float f) {
    float coeff = 2*cosf(2*PI_F*f/FS);
    float s0 = 0.0f;
    float s1 = 0.0f;
    float s2 = 0.0f;
    for (int i = 0; i < n; i++) {
        s0 = x[i] + coeff*s1 - s2;
        s2 = s1;
        s1 = s0;
    }
    return s1*s1 + s2*s2 - coeff*s1*s2;
}

char detect(const float *x, int n) {
    int best_low = 0;
    int best_high = 0;
    float e_low[NUM_TONES];
    float e_high[NUM_TONES];

    for (int i = 0; i < NUM_TONES; i++) {
        e_low[i] = goertzel_energy(x, n, f_low[i]);
        e_high[i] = goertzel_energy(x, n, f_high[i]);
    }

    for (int i = 1; i < NUM_TONES; i++) {
        if (e_low[i] > e_low[best_low]) {
            best_low = i;
        }
        if (e_high[i] > e_high[best_high]) {
            best_high = i;
        }
    }
    return keys[best_low][best_high];
}

#endif
