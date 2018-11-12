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
void makeQuadraticHashTable(int *);
void quadraticInsert(Node *);
void quadraticSearchAll(int *);
bool quadraticSearch(Node *);
void quadraticDeleteAll(int *);
bool quadraticDelete(Node *);
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

    fp = fopen("./output_quadratic.txt", "w");

    printf("========== Quadratic Hash Table ==========\n");
    makeQuadraticHashTable(inputs_a);
    printStat();
    quadraticDeleteAll(inputs_b);
    quadraticSearchAll(inputs_c);

    fclose(fp);
}

Node *createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
 
    return newNode;
}

void makeQuadraticHashTable(int *inputs) {
    int i;
    for(i = 0; i < length_a; i++)
        quadraticInsert(createNode(inputs[i]));
}

void quadraticInsert(Node *x) {
    int key = HASH_KEY(x->value);
    int i = 0;
    while(hashTable[key] != NULL) {
        i++;
        key = HASH_KEY((HASH_KEY(x->value) + (i*i)));
        count++;
    }
    hashTable[key] = x;
}

void quadraticSearchAll(int *inputs) {
    int i;
    for(i = 0; i < length_c; i++)
        quadraticSearch(createNode(inputs[i]));
}

bool quadraticSearch(Node *x) {
    int key = HASH_KEY(x->value);
    int i = 0;
    while(hashTable[key] != NULL) {
        i++;
        if(hashTable[key]->value == x->value) {
            fprintf(fp, "%d %d\n", hashTable[key]->value, key);
            return true;
        }
        else
            key = HASH_KEY((HASH_KEY(x->value) + (i*i)));
    }
    return false;
}

void quadraticDeleteAll(int *inputs) {
    int i;
    for(i = 0; i < length_b; i++)
        quadraticDelete(createNode(inputs[i]));
}

bool quadraticDelete(Node *x) {
    int key = HASH_KEY(x->value);
    int i = 0;
    while(hashTable[key] != NULL) {
        i++;
        if(hashTable[key]->value == x->value) {
            hashTable[key]->value = DELETED;
            return true;
        }
        else
            key = HASH_KEY((HASH_KEY(x->value) + (i*i)));
    }
    return false;
}

void printStat() {
    printf("crash count : %d\n", count);
    count = 0;
}