#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

FILE *inputFp, *outputFp;

typedef struct Node {
    struct Node *next;
    struct Node *parent;

    char *id;
    int num;

    int rank;
} Node;

Node *readingfile();

Node *createNode(char *, int);
void connectNode(Node *, Node *);

void executeUnionSet(Node *);
void executeUnionALL(Node *);

void makeSet(Node *);
void unionSet(Node *, Node *);
Node *findSet(Node *);

void printOutput(Node *);

int main() {
    Node *head = (Node*)malloc(sizeof(Node));
    head = readingfile();
    executeUnionSet(head);
    outputFp = fopen("./output1.txt", "w");
    printOutput(head);
    executeUnionALL(head);
    outputFp = fopen("./output2.txt", "w");
    printOutput(head);
    fclose(outputFp);
    return 0;
}

Node *readingfile() {
    char *id = (char *)malloc(sizeof(char));
	int num;    
    Node *inputNode = NULL, *oldNode = NULL, *head = NULL;

	inputFp = fopen("./Data_updated.txt", "r");
	while(fscanf(inputFp, "%s\t%d", id, &num) != EOF) {
        inputNode = createNode(id, num);
        makeSet(inputNode);

        if(head == NULL) head = inputNode;
        if(oldNode != NULL) connectNode(oldNode, inputNode);
        oldNode = inputNode;

        id = (char *)malloc(sizeof(char));
	}

	fclose(inputFp);

    return head;
}

void connectNode(Node *nodeX, Node *nodeY) {
    nodeX->next = nodeY;
}

void executeUnionSet(Node *head) {
    Node *point = head;
    Node *nextPoint;

    while(point != NULL) {
        nextPoint = point->next;
        while(nextPoint != NULL) {
            if(point->num == nextPoint->num) {
                unionSet(point, nextPoint);
            }
            nextPoint = nextPoint->next;
        }
        point = point->next;
    }
}

void executeUnionALL(Node *head) {
    Node *point = head;
    Node *nextPoint = point->next;

    while(nextPoint != NULL) {
        unionSet(point, nextPoint);
        point = point->next;
        nextPoint = point->next;
    }
}


Node *createNode(char *id, int num) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->parent = NULL;
    newNode->id = id;
    newNode->num = num;
 
    return newNode;
}

void makeSet(Node *nodeX) {
    nodeX->parent = nodeX;
    nodeX->rank = 1;
}

void unionSet(Node *nodeX, Node *nodeY) {
    Node *rootX = findSet(nodeX);
    Node *rootY = findSet(nodeY);
    if(rootX == rootY) return;

    if(rootX->rank > rootY->rank) {
        rootY->parent = rootX;
    } else {
        rootX->parent = rootY;
        if(rootX->rank == rootY->rank) {
            rootY->rank = rootY->rank+1;
        }
    }
}

Node *findSet(Node *nodeX) {
    if(nodeX->parent == nodeX)
        return nodeX;
    else
        return findSet(nodeX->parent);
}

void printOutput(Node *point) {
    while(point != NULL) {
        fprintf(outputFp,"%s\t%s\n", point->id, point->parent->id);
        point = point->next;
    }
}