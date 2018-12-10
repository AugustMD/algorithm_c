#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1000

FILE *inputFp, *outputFp;
char *x, *y;
int x_length, y_length, count = 0;
float gap;
time_t start_time = 0, end_time = 0;

typedef struct LCS {
    int length[MAX_SIZE][MAX_SIZE];
    int solution[MAX_SIZE][MAX_SIZE];
} LCS;

void lcsLength(LCS *);
void printLCS(LCS *, int, int);

int main() {
    x = (char *)malloc(sizeof(char));
    y = (char *)malloc(sizeof(char));
    LCS *lcs = (LCS*)malloc(sizeof(LCS));

    inputFp = fopen("./LCS_Data.txt", "r");
    fscanf(inputFp, "%d\n%s\n%d\n%s", &x_length, x, &y_length, y);
    fclose(inputFp);

    outputFp = fopen("./Output.txt", "w");
    start_time = clock();
    lcsLength(lcs);
    end_time = clock();
    printLCS(lcs, x_length, y_length);
    fprintf(outputFp, "\n");
    fclose(outputFp);

    printf("반복 횟수 : %d\n", count);
    gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
    printf("측정 시간 : %f 초\n", gap);

    return 0;
}


void lcsLength(LCS *lcs) {
    int i, j;

    for(i = 0; i <= x_length; i++) {
        lcs->length[i][0] = 0;
        count++;
    }

    for(j = 0; i <= y_length; j++) {
        lcs->length[0][j] = 0;
        count++;
    }

    for(i = 1; i <= x_length; i++) {
        for(j = 1; j <= y_length; j++) {
            if(x[i-1] == y[j-1]) {
                lcs->length[i][j] = lcs->length[i-1][j-1] + 1;
                lcs->solution[i][j] = 0; // left up
            } else if(lcs->length[i-1][j] >= lcs->length[i][j-1]) {
                lcs->length[i][j] = lcs->length[i-1][j];
                lcs->solution[i][j] = 1; // up
            } else {
                lcs->length[i][j] = lcs->length[i][j-1];
                lcs->solution[i][j] = 2; // left
            }
            count++;
        }
        count++;
    }
}

void printLCS(LCS *lcs, int i, int j) {
    if(i == 0 || j == 0)
        return;

    if(lcs->solution[i][j] == 0) {
        printLCS(lcs, i-1, j-1);
        fprintf(outputFp, "%c", x[i-1]);
    } else if(lcs->solution[i][j] == 1)
        printLCS(lcs, i-1, j);
    else
        printLCS(lcs, i, j-1);
}