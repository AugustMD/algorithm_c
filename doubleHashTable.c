#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_HASH 97
#define MAX_HASH_SECOND 59
#define DELETED -1
#define HASH_KEY(key) key%MAX_HASH
#define HASH_KEY_SECOND(key) (key%MAX_HASH_SECOND)+1

typedef enum { false, true } bool;

FILE *fp;
int inputs_a[1000000], inputs_b[1000000], inputs_c[1000000];
int length_a = 0, length_b = 0, length_c = 0, count = 0;

typedef struct Node {
    int value;
} Node;
 
Node *hashTable[MAX_HASH];

void readingfile();
void savefile();
Node *createNode(int);
void makeDoubleHashTable(int *);
void doubleInsert(Node *);
void doubleSearchAll(int *);
bool doubleSearch(Node *);
void doubleDeleteAll(int *);
bool doubleDelete(Node *);
void printStat();

int main() {
	readingfile();
    savefile();
    
    return 0;
}

void readingfile() {
	int data;

	fp = fopen("./Data1.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		inputs_a[length_a] = data;
        length_a++;
	}

    fp = fopen("./Data2.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		inputs_b[length_b] = data;
        length_b++;
	}

    fp = fopen("./Data3.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		inputs_c[length_c] = data;
        length_c++;
	}

	fclose(fp);
}

void savefile() {
	int data = 0;

    fp = fopen("./output_double.txt", "w");
    printf("========== Double Hash Table ==========\n");
    makeDoubleHashTable(inputs_a);
    printStat();
    doubleDeleteAll(inputs_b);
    doubleSearchAll(inputs_c);

    fclose(fp);
}

Node *createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
 
    return newNode;
}

void makeDoubleHashTable(int *inputs) {
    int i;
    for(i = 0; i < length_a; i++)
        doubleInsert(createNode(inputs[i]));
}

void doubleInsert(Node *x) {
    int key = HASH_KEY(x->value);
    int i = 0;
    while(hashTable[key] != NULL) {
        i++;
        key = HASH_KEY((HASH_KEY(x->value) + i*HASH_KEY_SECOND(x->value)));
        count++;
    }
    hashTable[key] = x;
}

void doubleSearchAll(int *inputs) {
    int i;
    for(i = 0; i < length_c; i++)
        doubleSearch(createNode(inputs[i]));
}

bool doubleSearch(Node *x) {
    int key = HASH_KEY(x->value);
    int i = 0;
    while(hashTable[key] != NULL) {
        i++;
        if(hashTable[key]->value == x->value) {
            fprintf(fp, "%d %d\n", hashTable[key]->value, key);
            return true;
        }
        else
            key = HASH_KEY((HASH_KEY(x->value) + i*HASH_KEY_SECOND(x->value)));
    }
    return false;
}

void doubleDeleteAll(int *inputs) {
    int i;
    for(i = 0; i < length_b; i++)
        doubleDelete(createNode(inputs[i]));
}

bool doubleDelete(Node *x) {
    int key = HASH_KEY(x->value);
    int i = 0;
    while(hashTable[key] != NULL) {
        i++;
        if(hashTable[key]->value == x->value) {
            hashTable[key]->value = DELETED;
            return true;
        } else
            key = HASH_KEY((HASH_KEY(x->value) + i*HASH_KEY_SECOND(x->value)));
    }
    return false;
}

void printStat() {
    printf("crash count : %d\n", count);
    count = 0;
}