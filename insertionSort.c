#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct DNode {
	int data;
	struct DNode *next;
	struct DNode *prev;
} DNode;

typedef struct DList {
	DNode *head;
	DNode *tail;
	int length;
} DList;

DNode *create(int data) {
	DNode *pos = (DNode *)malloc(sizeof(DNode));
	pos->data = data;
	pos->prev = pos->next = NULL;

	return pos;
}

void initList(DList *list) {
	list->head = create(0);
	list->tail = create(0);
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->length = 0;
}

void append(DList *list, int data) {
	DNode *pos = create(data);

	pos->prev = list->tail->prev;
	pos->next = list->tail;
	list->tail->prev->next = pos;
	list->tail->prev = pos;
	list->length++;
}

void readingfile(DList *list) {
	FILE *fp;
	int data;

	fp = fopen("./test_100.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		append(list, data);
	}

	fclose(fp);
}

void savefile(DList *list) {
	FILE *fp;
	int data = 0;

	fp = fopen("./output.txt", "a");
	DNode *seek = list->head->next;
	int i = 0;

	while (seek != list->tail) {
		printf("%d\n", seek->data);
		fprintf(fp, "%d\n", seek->data);
		seek = seek->next;
	}

	fclose(fp);
}

void insertionSort(DList *list) {
	DNode *seek = list->head->next->next;

	while (seek != list->tail) {
		int temp = seek->data;
		DNode *seek2 = seek->prev;
		while (seek2 != list->head && seek2->data > temp) {
			seek2->next->data = seek2->data;
			seek2 = seek2->prev;
		}
		seek2->next->data = temp;
		seek = seek->next;
	}
}

int main(void) {
	float gap;
	time_t start_time = 0, end_time = 0;
	DList list;

	initList(&list);
	readingfile(&list);
	start_time = clock();
	insertionSort(&list);
	end_time = clock();
	savefile(&list);
	gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
	printf("\n측정 시간 : %f 초\n", gap);

	return 0;
}