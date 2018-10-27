#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array[1000000];
int length = 0;
int count = 0;

void readingfile(int *array_pointer) {
	FILE *fp;
	int data;

	fp = fopen("./test_1000.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		array_pointer[length] = data;
        length++;
	}

	fclose(fp);
}

void savefile(int *array_pointer) {
	FILE *fp;
	int data = 0;

	fp = fopen("./output_max_heap_1000.txt", "a");
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

void maxHeapify(int *array_pointer, int k, int n) {
	int largest = k;
	int left = 2*k + 1;
	int right = 2*k + 2;
	count++;

	if (left < n && array_pointer[left] > array_pointer[largest])
		largest = left;

	if (right < n && array_pointer[right] > array_pointer[largest])
		largest = right;

	if (largest != k) {
		swap(array_pointer + k, array_pointer + largest);
		maxHeapify(array_pointer, largest, n);
	}
}

void buildMaxdHeap(int *array_pointer, int n) {
	int i = 0;
	for(i = n/2 - 1; i >= 0; i--) {
		maxHeapify(array_pointer, i, n);
		count++;
	}
}

void maxHeapSort(int *array_pointer, int n) {
	int i = 0;

	buildMaxdHeap(array_pointer, n);

	for(i = n - 1; i >= 0; i--) {
		swap(array_pointer + 0, array_pointer + i);
		maxHeapify(array_pointer, 0, i);
		count++;
	}
}

int main() {
	float gap;
	time_t start_time = 0, end_time = 0;

	readingfile(array);
	start_time = clock();
	maxHeapSort(array, length);
	end_time = clock();
	savefile(array);
	gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
    printf("\n수행 횟수 : %d 회\n", count);
	printf("\n측정 시간 : %f 초\n", gap);

    return 0;
}