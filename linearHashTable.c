#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_HASH 97
#define MAX_HASH_SECOND 59
#define DELETED -1
#define HASH_KEY(key) key%MAX_HASH

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
void makeLinearHashTable(int *);
void linearInsert(Node *);
void linearSearchAll(int *);
bool linearSearch(Node *);
void linearDeleteAll(int *);
bool linearDelete(Node *);
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

    fp = fopen("./output_linear.txt", "w");

    printf("========== Linear Hash Table ==========\n");
    makeLinearHashTable(inputs_a);
    printStat();
    linearDeleteAll(inputs_b);
    linearSearchAll(inputs_c);

    fclose(fp);
}

Node *createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
 
    return newNode;
}

void makeLinearHashTable(int *inputs) {
    int i;
    for(i = 0; i < length_a; i++)
        linearInsert(createNode(inputs[i]));
}

void linearInsert(Node *x) {
    int key = HASH_KEY(x->value);
    while(hashTable[key] != NULL) {
        key = HASH_KEY((key + 1));
        count++;
    }
    hashTable[key] = x;
}

void linearSearchAll(int *inputs) {
    int i;
    for(i = 0; i < length_c; i++)
        linearSearch(createNode(inputs[i]));
}

bool linearSearch(Node *x) {
    int key = HASH_KEY(x->value);
    while(hashTable[key] != NULL) {
        if(hashTable[key]->value == x->value) {
            fprintf(fp, "%d %d\n", hashTable[key]->value, key);
            return true;
        }
        else
            key = HASH_KEY(key + 1);
    }
    return false;
}

void linearDeleteAll(int *inputs) {
    int i;
    for(i = 0; i < length_b; i++)
        linearDelete(createNode(inputs[i]));
}

bool linearDelete(Node *x) {
    int key = HASH_KEY(x->value);
    while(hashTable[key] != NULL) {
        if(hashTable[key]->value == x->value) {
            hashTable[key]->value = DELETED;
            return true;
        }
        else
            key = HASH_KEY((key + 1));
    }
    return false;
}

void printStat() {
    printf("crash count : %d\n", count);
    count = 0;
}