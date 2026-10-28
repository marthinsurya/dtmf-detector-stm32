#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define FS 8000.0f
#define PI_F 3.14159265f
#define N 800
#define KEYS_PER_SNR 16
#define NUM_TONES 4
#define NUM_SNRS 4
#define INPUT_SCALE 0.25f

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


void q15_goertzel_state(const float *x, int n, float f, int32_t *s1, int32_t *s2){
    int16_t coeff_half = float_to_q15(cosf(2*PI_F*f/FS));
    *s1 = 0;
    *s2 = 0;

    for (int i = 0; i < n; i++) {
        int16_t s = float_to_q15(x[i] * INPUT_SCALE);
        int32_t s0 = s + (int32_t)(((int64_t)coeff_half * *s1) >> 14) - *s2;
        *s2 = *s1;
        *s1 = s0; 
    }
}


static const float f_low[NUM_TONES]  = {697.0f, 770.0f, 852.0f, 941.0f};
// static const float f_high[NUM_TONES] = {1209.0f, 1336.0f, 1477.0f, 1633.0f};

// static const char keys[NUM_TONES][NUM_TONES] = {
//     {'1','2','3','A'},
//     {'4','5','6','B'},
//     {'7','8','9','C'},
//     {'*','0','#','D'}
// };

int main(void) {
    FILE *fp = fopen("c/signals.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "can't open file\n");
        return 1;
    }
    char key;
    int snr;
    // int line = 0;
    // int correct[NUM_SNRS] = {0, 0, 0, 0};
    // int snrs[NUM_SNRS];
    int count = 0;      
    while (fscanf(fp, " %c %d", &key, &snr) == 2) {
        float x[N];
        //Read 1 signal
        for (int i = 0; i < N; i++) {
            int ok = fscanf(fp, "%f", &x[i]);
            if (ok != 1) {
                fprintf(stderr, "read failed at %d\n", i);
                fclose(fp);
                return 1;
            }             
        }
        //Process signal
        for (int i = 0; i < NUM_TONES; i++) {
            int32_t s1, s2;
            q15_goertzel_state(x, N, f_low[i], &s1, &s2);
            printf("s1 = %d, s2 = %d\n", s1, s2);
        }
        count++;             
    }
    printf("count %d\n", count);
    return 0;
}