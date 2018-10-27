#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array_a[1000000];
int array_b[1000000];
int array_c[1000000];
int length = 0;
int count = 0;

void readingfile(int *array_pointer) {
	FILE *fp;
	int data;

	fp = fopen("./test_100.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
        length++;
		array_pointer[length] = data;
	}

	fclose(fp);
}

void savefile(int *array_pointer) {
	FILE *fp;
	int data = 0;

	fp = fopen("./output_counting_100.txt", "a");
	int i = 0;

	for (i = 1; i <= length; i++) {
		printf("%d\n", array_pointer[i]);
		fprintf(fp, "%d\n", array_pointer[i]);
	}

	fclose(fp);
}

void countingSort(int *array_pointer, int max, int n) {
    int i, j;
    for(i = 0; i <= max; i++)
        array_c[i] = 0;

    for(j = 1; j <= n; j++)
        array_c[array_pointer[j]] = array_c[array_pointer[j]] + 1;

    for(i = 1; i <= max; i++)
        array_c[i] = array_c[i] + array_c[i - 1];

    for(j = n; j >= 1; j--) {
        array_b[array_c[array_pointer[j]]] = array_pointer[j];
        array_c[array_pointer[j]] = array_c[array_pointer[j]] - 1;
        count++;
    }
}


int main() {
    int max = 0, i = 0;
	float gap;
	time_t start_time = 0, end_time = 0;

	readingfile(array_a);
	start_time = clock();

    for (i = 0; i < length; i++)
        if (array_a[i] > max) max = array_a[i];
    
	countingSort(array_a, max, length);
	end_time = clock();
	savefile(array_b);
	gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
    printf("\n수행 횟수 : %d 회\n", count);
	printf("\n측정 시간 : %f 초\n", gap);

    return 0;
}