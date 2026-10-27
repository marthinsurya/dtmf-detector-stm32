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
    fclose(f);
    return 0;
}