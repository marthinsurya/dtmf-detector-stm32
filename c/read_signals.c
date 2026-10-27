#include <stdio.h>

int main(void){
    FILE *f = fopen("c/signals.txt", "r");
    if (f == NULL) {
        printf("can't open file\n");
        return 1;
    }
    char key;
    int snr;
    fscanf(f, "%c %d", &key, &snr);
    printf("key %c, snr %d\n", key, snr);

    float x[800];
    for (int i = 0; i < 800; i++) {
        int n = fscanf(f, "%f", &x[i]); 
        if (n != 1) {
        printf("read failed at %d\n", i);
        return 1;
        }
    }
    printf("x[0] = %f, x[799] = %f\n", x[0], x[799]);

    fclose(f);
    return 0;
}