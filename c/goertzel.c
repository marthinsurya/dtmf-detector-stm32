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
    return s1*s1+s2*s2-coeff*s1*s2; 
}


int main(void) {
    float x[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    printf("energy = %f\n", goertzel_energy(x, 4, 697.0f));
    return 0;
}