#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array_a[1000000];
int array_b[1000000];
int length = 0;
int count = 0;

void readingfile(int *array_pointer) {
	FILE *fp;
	int data;

	fp = fopen("./test_100.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		array_pointer[length] = data;
        length++;
	}

	fclose(fp);
}

void savefile(int *array_pointer) {
	FILE *fp;
	int data = 0;

	fp = fopen("./output_merge_100.txt", "a");
	int i = 0;

	for (i = 0; i < length; i++) {
		printf("%d\n", array_pointer[i]);
		fprintf(fp, "%d\n", array_pointer[i]);
        
	}

	fclose(fp);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge(int start, int mid, int end) {
    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end) {
        count++;
        if (array_a[i] <= array_a[j]) {
            array_b[k++] = array_a[i++];
        } else {
            array_b[k++] = array_a[j++];
        }
    }

    while (i <= mid) {
        array_b[k++] = array_a[i++];
    }

    while (j <= end) {
        array_b[k++] = array_a[j++];
    }

    for (int i = start; i <= end; i++) {
        array_a[i] = array_b[i - start];
    }
}

void mergeSort(int start, int end) {
    count++;
    if(start < end) {
        int mid = (start + end) / 2;
        mergeSort(start, mid);
        mergeSort(mid + 1, end);
        merge(start, mid, end);
    }
}

int main(void) {
	float gap;
	time_t start_time = 0, end_time = 0;

	readingfile(array_a);
	start_time = clock();
	mergeSort(0, length - 1);
	end_time = clock();
	savefile(array_a);
	gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
    printf("\n수행 횟수 : %d 회\n", count);
	printf("\n측정 시간 : %f 초\n", gap);

	return 0;
}