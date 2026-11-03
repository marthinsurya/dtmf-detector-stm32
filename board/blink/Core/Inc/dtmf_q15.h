#ifndef DTMF_Q15_H
#define DTMF_Q15_H

#include <stdint.h>
#include "dtmf.h"

static const int16_t coeff_low_q15[4]  = {27980, 26956, 25701, 24219};
static const int16_t coeff_high_q15[4] = {19073, 16325, 13085, 9315};

int64_t goertzel_energy_q15(const int16_t *x, int n, int16_t coeff_half) {
    int32_t s1 = 0;
    int32_t s2 = 0;
    for (int i = 0; i < n; i++) {
        int32_t term = (int32_t)(((int64_t)coeff_half * s1) >> 14);
        int32_t s0 = x[i] + term - s2;
        s2 = s1;
        s1 = s0;
    }
    int64_t term = ((int64_t)coeff_half * s1) >> 14;
    return (int64_t)s1 * s1 + (int64_t)s2 * s2 - term * s2;
}

char detect_q15(const int16_t *x, int n) {
    int best_low = 0;
    int best_high = 0;
    int64_t e_low[NUM_TONES];
    int64_t e_high[NUM_TONES];

    for (int i = 0; i < NUM_TONES; i++) {
        e_low[i]  = goertzel_energy_q15(x, n, coeff_low_q15[i]);
        e_high[i] = goertzel_energy_q15(x, n, coeff_high_q15[i]);
    }

    for (int i = 1; i < NUM_TONES; i++) {
           if (e_low[i] > e_low[best_low]) {
              best_low = i;
           }
           if (e_high[i] > e_high[best_high]) {
			  best_high  = i;
		  }
       }

    return keys[best_low][best_high];
}

#endif
