#include <stdio.h>

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
        printf("line %d: key %c, snr %d, x[0]=%f\n", line, key, snr, x[0]);
    }
    
    fclose(f);
    return 0;
}