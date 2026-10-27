#include <stdio.h>
#include <math.h>

#define PI_F 3.14159265f

float goertzel_energy(const float *x, int n, float f) {
    float fs = 8000.0f;
    float coeff = 2*cosf(2*PI_F*f/fs);  
    float s0 = 0.0f;
    float s1 = 0.0f;
    float s2 = 0.0f;
    for (int i = 0; i < n; i++) {
        s0 = x[i] + coeff*s1 - s2;
        s2 = s1;
        s1 = s0;
    }
    return s1*s1+s2*s2-coeff*s1*s2;; 
}

float f_low[4]  = {697.0f, 770.0f, 852.0f, 941.0f};
float f_high[4] = {1209.0f, 1336.0f, 1477.0f, 1633.0f};
const char keys[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

char detect(const float *x, int n){
    int best_low = 0;
    int best_high = 0;
    float e_low[4];
    float e_high[4];

    for (int i = 0; i < 4; i++) {
        e_low[i] = goertzel_energy(x, n, f_low[i]);
        e_high[i] = goertzel_energy(x, n, f_high[i]);
    }

    for (int i = 1; i < 4; i++) {
        if (e_low[i]>e_low[best_low]){
            best_low = i;
        }
        if (e_high[i]>e_high[best_high]){
            best_high = i;
        }
    }
    return keys[best_low][best_high];
}

int main(void){
    FILE *f = fopen("c/signals.txt", "r");
    if (f == NULL) {
        printf("can't open file\n");
        return 1;
    }
    char key;
    int snr;
    int line = 0;

    while (fscanf(f, " %c %d", &key, &snr) == 2) {
        float x[800];
        for (int i = 0; i < 800; i++) {
            int n = fscanf(f, "%f", &x[i]); 
            if (n != 1) {
                printf("read failed at %d\n", i);
                return 1;
            }
        }
        line++;
        // printf("line %d: key %c, snr %d, E697 = %f\n", line, key, snr, goertzel_energy(x, 800, 697.0f));
        char got = detect(x, 800);
        printf("line %d: snr %d, expected %c, detected %c\n", line, snr, key, got);
    }
    
    fclose(f);
    return 0;
}