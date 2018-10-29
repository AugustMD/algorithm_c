#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int keys[1000000];
int length = 0;
int count = 0;
float gap = 0;
time_t start_time = 0, end_time = 0;

typedef struct Node {
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int key;
} Node;

typedef struct Tree {
    Node* root;
    int size;
} Tree;

void readingfile(int *);
void savefile(int *);

void swap(int *, int *);
int partition(int *, int, int);
void quickSort(int *, int, int);

Tree *createTree();
Node *createNode(int);
void treeInsert(Tree *, Node *);
Node *treeMedianInsert(int *, int, int, Node *);
Node *treeRecursiveSearch(Node *, int);
Node *treeIterativeSearch(Node *, int);
Node* treeMinimum(Node *);
Node* treeMaximum(Node *);
Node *treeSuccessor(Node *);
Node *treePredecessor(Node *);
void transplant(Tree *, Node *, Node *);
void treeDelete(Tree *, Node *);
Tree *makeTree(int *, int);
Tree *makeMedianTree(int *, int);
void inorder(FILE *,Node *);
void initParmeter();
void displayTree(FILE *, Tree *);
void displayStat(FILE *, int, int, int);

int main() {
	readingfile(keys);
    savefile(keys);
    
    return 0;
}

void readingfile(int *keys) {
	FILE *fp;
	int data;

	fp = fopen("./Data2.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		keys[length] = data;
        length++;
	}

	fclose(fp);
}

void savefile(int *keys) {
    FILE *fp;
	int data = 0;

    fp = fopen("./output_Data2.txt", "w");

    fprintf(fp, "=======================================\n");
    fprintf(fp, "====== Normal Binary Search Tree ======\n");
    fprintf(fp, "=======================================\n\n");

    fprintf(fp, "Make Tree >\n");
    start_time = clock();
	Tree *normalTree = makeTree(keys, length);
    end_time = clock();
    displayTree(fp, normalTree);
    displayStat(fp, count, end_time, start_time);
    initParmeter();
    fprintf(fp, "\n");

    Node *root = normalTree->root;

    fprintf(fp, "Recursive Search >\n");
    fprintf(fp, "check [node:root] is [key:1] : %s\n", treeRecursiveSearch(root, 1) != NULL?"true":"false");
    fprintf(fp, "check [node:root] is [key:%d] : %s\n", root->key, treeRecursiveSearch(root, root->key) != NULL?"true":"false");
    fprintf(fp, "\n");

    fprintf(fp, "Iterative Search >\n");
    fprintf(fp, "check [node:root] is [key:1] : %s\n", treeIterativeSearch(root, 1) != NULL?"true":"false");
    fprintf(fp, "check [node:root] is [key:%d] : %s\n", root->key, treeIterativeSearch(root, root->key) != NULL?"true":"false");
    fprintf(fp, "\n");

    fprintf(fp, "Successor >\n");
    fprintf(fp, "Successor Root Node : %d\n", treeSuccessor(root)->key);
    fprintf(fp, "\n");

    fprintf(fp, "Predecessor >\n");
    fprintf(fp, "Predecessor Root Node : %d\n", treePredecessor(root)->key);
    fprintf(fp, "\n");

    fprintf(fp, "Delete >\n");
    fprintf(fp, "Delete Root Node : %d\n", root->key);
    treeDelete(normalTree, root);
    displayTree(fp, normalTree);
    fprintf(fp, "Delete Root Right Node : %d\n", (root->right)->key);
    treeDelete(normalTree, root->right);
    displayTree(fp, normalTree);
    fprintf(fp, "\n\n");

    fprintf(fp, "=======================================\n");
    fprintf(fp, "====== Median Binary Search Tree ======\n");
    fprintf(fp, "=======================================\n\n");

    fprintf(fp, "Make Tree >\n");
    start_time = clock();
	Tree *medianTree = makeMedianTree(keys, length);
    end_time = clock();
    displayTree(fp, medianTree);
    displayStat(fp, count, end_time, start_time);
    initParmeter();
    fprintf(fp, "\n");

    Node *rootMedian = medianTree->root;

    fprintf(fp, "Recursive Search >\n");
    fprintf(fp, "check [node:root] is [key:1] : %s\n", treeRecursiveSearch(rootMedian, 1) != NULL?"true":"false");
    fprintf(fp, "check [node:root] is [key:%d] : %s\n", rootMedian->key, treeRecursiveSearch(rootMedian, rootMedian->key) != NULL?"true":"false");
    fprintf(fp, "\n");

    fprintf(fp, "Iterative Search >\n");
    fprintf(fp, "check [node:root] is [key:1] : %s\n", treeIterativeSearch(rootMedian, 1) != NULL?"true":"false");
    fprintf(fp, "check [node:root] is [key:%d] : %s\n", rootMedian->key, treeIterativeSearch(rootMedian, rootMedian->key) != NULL?"true":"false");
    fprintf(fp, "\n");

    fprintf(fp, "Successor >\n");
    fprintf(fp, "Successor Root Node : %d\n", treeSuccessor(rootMedian)->key);
    fprintf(fp, "\n");

    fprintf(fp, "Predecessor >\n");
    fprintf(fp, "Predecessor Root Node : %d\n", treePredecessor(rootMedian)->key);
    fprintf(fp, "\n");

    fprintf(fp, "Delete >\n");
    fprintf(fp, "Delete Root Node : %d\n", rootMedian->key);
    treeDelete(medianTree, rootMedian);
    displayTree(fp, medianTree);
    fprintf(fp, "Delete Root Right Node : %d\n", (rootMedian->right)->key);
    treeDelete(medianTree, rootMedian->right);
    displayTree(fp, medianTree);
    fprintf(fp, "\n");
	
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

Tree *createTree() {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));
    newTree->root = NULL;
    newTree->size = 0;

    return newTree;
}

Node *createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->key = key;
 
    return newNode;
}

void treeInsert(Tree *tree, Node *insertNode) {
    Node *currentNode = insertNode->parent;
    Node *parentNode = tree->root;

    while(parentNode != NULL) {
        currentNode = parentNode;
        if(insertNode->key < parentNode->key) {
            parentNode = parentNode->left;
            count++;
        } else {
            parentNode = parentNode->right;
            count++;
        }
    }
    if(currentNode == NULL)
        tree->root = insertNode;
    else if(insertNode->key < currentNode->key) {
        currentNode->left = insertNode;
        insertNode->parent = currentNode;
    }
    else {
        currentNode->right = insertNode;
        insertNode->parent = currentNode;
    }
}

Node *treeMedianInsert(int *keys, int start, int end, Node *parent) { 
    count++;
    if(start > end)
        return NULL;

    int mid = (start + end)/2; 
    Node *newNode = createNode(keys[mid]);

    newNode->parent = parent;
    newNode->left =  treeMedianInsert(keys, start, mid-1, newNode); 
    newNode->right = treeMedianInsert(keys, mid+1, end, newNode); 
  
    return newNode; 
} 

Node *treeRecursiveSearch(Node *node, int key) {
    if(node == NULL || key == node->key)
        return node;
    else if (key < node->key) {
        return treeRecursiveSearch(node->left, key);
    }
    else {
        return treeRecursiveSearch(node->right, key);
    }
}

Node *treeIterativeSearch(Node *node, int key) {
    while(node != NULL && key != node->key) {
        if(key < node->key) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return node;
}

Node* treeMinimum(Node *node) {
  Node *currentNode = node;
  while(currentNode->left != NULL)
    currentNode = currentNode->left;
  
  return (currentNode);
}

Node* treeMaximum(Node *node) {
  Node *currentNode = node;
  while(currentNode->right != NULL)
    currentNode = currentNode->right;
  
  return (currentNode);
}

Node *treeSuccessor(Node *node) {
    Node *currentNode = NULL;
    if(node->right != NULL)
        return treeMinimum(node->right);
    currentNode = node->parent;
    while(currentNode != NULL && node == currentNode->right) {
        node = currentNode;
        currentNode = currentNode->parent;
    }

    return currentNode;
}

Node *treePredecessor(Node *node) {
    Node *currentNode = NULL;
    if(node->left != NULL)
        return treeMaximum(node->left);
    currentNode = node->parent;
    while(currentNode != NULL && node == currentNode->left) {
        node = currentNode;
        currentNode = currentNode->parent;
    }

    return currentNode;
}

void transplant(Tree *tree, Node *u, Node *v) {
    if(u->parent == NULL)
        tree->root = v;
    else if(u == (u->parent)->left)
        (u->parent)->left = v;
    else
        (u->parent)->right = v;
    if(v != NULL)
        v->parent = u->parent;
}

void treeDelete(Tree *tree, Node *deleteNode) {
    if(deleteNode->left == NULL)
        transplant(tree, deleteNode, deleteNode->right);
    else if(deleteNode->right == NULL)
        transplant(tree, deleteNode, deleteNode->left);
    else {
        Node *minNode = treeMinimum(deleteNode->right);
        if(minNode->parent != deleteNode) {
            transplant(tree, minNode, minNode->right);
            minNode->right = deleteNode->right;
            (minNode->right)->parent = minNode;
        }
        transplant(tree, deleteNode, minNode);
        minNode->left = deleteNode->left;
        (minNode->left)->parent = minNode;
    }
}

Tree *makeTree(int *keys, int length) {
    int i = 0;
    Tree *tree = createTree();
    tree->size = length;
    for(i = 0; i < length; i++) {
        Node *insertNode = createNode(keys[i]);
        treeInsert(tree, insertNode);
    }
    printf("\n\n");
    return tree;
}

Tree *makeMedianTree(int *keys, int length) {
    int i = 0;
    Tree *tree = createTree();
    tree->size = length;

    quickSort(keys, 0, length - 1);

    Node *root = treeMedianInsert(keys, 0, length-1, NULL);
    tree->root = root;
    printf("\n\n");
    return tree;
}

void inorder(FILE *fp, Node *node) {
    if(node == NULL)
        return;
    inorder(fp, node->left);
    fprintf(fp, "%d ", node->key);
    inorder(fp, node->right);
}

void initParmeter() {
    count = 0;
    gap = 0;
    start_time = 0, end_time = 0;
}

void displayTree(FILE *fp, Tree *tree) {
    fprintf(fp, "Inorder  : [ ");
    inorder(fp, tree->root);
    fprintf(fp, "]\n");
}

void displayStat(FILE *fp, int count, int end_time, int start_time) {
    gap = (float)(end_time - start_time) / (CLOCKS_PER_SEC);
    fprintf(fp, "counting : %d\n", count);
	fprintf(fp, "time     : %f\n", gap);
}