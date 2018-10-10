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

	fp = fopen("./output_quick_100.txt", "a");
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

int partition(int *array_pointer, int low, int high) {
    int pivotValue = array_pointer[high];
    int storeIndex = low;
    int i;

    for(i = low; i < high; i++) {
		count++;
        if(array_pointer[i] < pivotValue) {
            swap(array_pointer + i, array_pointer + storeIndex);
            storeIndex += 1;
        }
    }

    swap(array_pointer + storeIndex, array_pointer + high);

    return storeIndex;
}

void quickSort(int *array_pointer, int low, int high) {
	count++;
    if(low < high) {
        int pivot = partition(array_pointer, low, high);
        quickSort(array_pointer, low, pivot - 1);
        quickSort(array_pointer, pivot + 1, high);
    }
}

int main(void) {
	float gap;
	time_t start_time = 0, end_time = 0;

	readingfile(array);
	start_time = clock();
	quickSort(array, 0, length - 1);
	end_time = clock();
	savefile(array);
	gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
	printf("\n수행 횟수 : %d 회\n", count);
	printf("\n측정 시간 : %f 초\n", gap);

	return 0;
}