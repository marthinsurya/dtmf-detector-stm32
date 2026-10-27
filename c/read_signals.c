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
        printf("line %d: key %c, snr %d, E697 = %f\n", line, key, snr, goertzel_energy(x, 800, 697.0f));
    }
    
    fclose(f);
    return 0;
}