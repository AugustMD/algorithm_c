#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SPACE 10 

FILE *fp;
int keys[1000000];
int length = 0;
int count = 0;
float gap = 0;
time_t start_time = 0, end_time = 0;

typedef enum ColorType {
    RED, BLACK
} ColorType;

typedef struct Node {
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int key;
    ColorType color;
} Node;

typedef struct Tree {
    Node* root;
    int size;
} Tree;

void readingfile(int *);
void savefile(int *);
void initParmeter();

Tree *createTree();
Node *createNode(int);
Tree *makeTree(int *, int);
void treeInsert(Tree *, Node *); 
void fixTree(Node *, Node *);
void recoloring(Node *, Node *, Node *, Node *);
void swapColor(Node *, Node *);
void rotateLeft(Node *, Node *);
void rotateRight(Node *, Node *);
void inorder(FILE *,Node *);
void displayTree(FILE *, Tree *);
void displayStat(FILE *, int, int, int);
void printTree(Node *, int);

int main() {
	readingfile(keys);
    savefile(keys);
    
    return 0;
}

void readingfile(int *keys) {
	int data;

	fp = fopen("./Data1.txt", "r");
	while (fscanf(fp, "%d", &data) != EOF) {
		keys[length] = data;
        length++;
	}

	fclose(fp);
}

void savefile(int *keys) {
	int data = 0;

    fp = fopen("./output_RBT_Data1.txt", "w");


    initParmeter();
    start_time = clock();
	Tree *normalTree = makeTree(keys, length);
    end_time = clock();
    fprintf(fp, "====================================\n");
    fprintf(fp, "========== Red Black Tree ==========\n");
    fprintf(fp, "====================================\n\n");
    fprintf(fp, "Make Tree >\n");
    displayTree(fp, normalTree);
    displayStat(fp, count, end_time, start_time);
    fprintf(fp, "\n");

    fclose(fp);
}

void initParmeter() {
    count = 0;
    gap = 0;
    start_time = 0, end_time = 0;
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
    newNode->color = RED;
    newNode->key = key;
 
    return newNode;
}

Tree *makeTree(int *keys, int length) {
    int i = 0;
    Tree *tree = createTree();
    tree->size = length;
    for(i = 0; i < length; i++) {
        Node *nodeX = createNode(keys[i]);
        treeInsert(tree, nodeX);
        fprintf(fp, "=============== insert: %d ===============\n", nodeX->key);
        printTree(tree->root,0);
        fprintf(fp, "\n\n-> fixTree : ");
        fixTree(tree->root, nodeX);
        fprintf(fp, "\n\n");
        printTree(tree->root,0);
        fprintf(fp, "\n==========================================\n\n\n\n\n");
    }
    fprintf(fp, "\n\n");
    return tree;
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

void recoloring(Node *nodeX, Node *nodeX_parent, Node *nodeX_grandParent, Node *nodeX_uncle) {
    nodeX_grandParent->color = RED; 
    nodeX_parent->color = BLACK; 
    nodeX_uncle->color = BLACK; 
}

void swapColor(Node *x, Node *y) {
    ColorType tempColor;

    tempColor = x->color;
    x->color = y->color;
    y->color = tempColor;
}

void fixTree(Node *root, Node *nodeX) {
    while((nodeX != root) && (nodeX->color == RED) && (nodeX->parent->color == RED)) { 
        Node *nodeX_parent = nodeX->parent;
        Node *nodeX_grandParent = nodeX->parent->parent; 

        if(nodeX_parent == nodeX_grandParent->left) { 
            fprintf(fp, "[CASE A-");
            Node *nodeX_uncle = nodeX_grandParent->right;

            if((nodeX_uncle != NULL) && (nodeX_uncle->color == RED)) {
                count++;
                fprintf(fp, "1] ");
                recoloring(nodeX, nodeX_parent, nodeX_grandParent, nodeX_uncle);
                nodeX = nodeX_grandParent;
            } else { 
                if(nodeX == nodeX_parent->right) { 
                    count++;
                    fprintf(fp, "2-1]");
                    rotateLeft(root, nodeX_parent); 
                    nodeX = nodeX_parent; 
                    nodeX_parent = nodeX->parent; 
                } else fprintf(fp, "2-2] ");
                count++;
                rotateRight(root, nodeX_grandParent); 
                swapColor(nodeX_parent, nodeX_grandParent);
                nodeX = nodeX_parent; 
            } 
        } else {
            fprintf(fp, "[CASE B-");
            Node *nodeX_uncle = nodeX_grandParent->left;
    
            if((nodeX_uncle != NULL) && (nodeX_uncle->color == RED)) { 
                count++;
                fprintf(fp, "1] ");
                recoloring(nodeX, nodeX_parent, nodeX_grandParent, nodeX_uncle);
                nodeX = nodeX_grandParent;
            } else { 
                if(nodeX == nodeX_parent->left) { 
                    count++;
                    fprintf(fp, "2-1]");
                    rotateRight(root, nodeX_parent); 
                    nodeX = nodeX_parent; 
                    nodeX_parent = nodeX->parent; 
                } else fprintf(fp, "2-2] ");
                count++;
                rotateLeft(root, nodeX_grandParent); 
                swapColor(nodeX_parent, nodeX_grandParent);
                nodeX = nodeX_parent; 
            } 
        }
    } 
    root->color = BLACK; 
}

void rotateLeft(Node *root, Node *nodeX) {
    Node *nodeX_right = nodeX->right; 
  
    nodeX->right = nodeX_right->left; 
    nodeX_right->parent = nodeX->parent; 
  
    if(nodeX->parent == NULL) 
        root = nodeX_right; 
  
    else if(nodeX == nodeX->parent->left) 
        nodeX->parent->left = nodeX_right; 
  
    else
        nodeX->parent->right = nodeX_right; 
  
    nodeX_right->left = nodeX; 
    nodeX->parent = nodeX_right; 
}
  
void rotateRight(Node *root, Node *nodeX) {
    Node *nodeX_left = nodeX->left; 
  
    nodeX->left = nodeX_left->right; 
    nodeX_left->parent = nodeX->parent; 
  
    if(nodeX->parent == NULL) 
        root = nodeX_left; 
  
    else if(nodeX == nodeX->parent->left) 
        nodeX->parent->left = nodeX_left; 
  
    else
        nodeX->parent->right = nodeX_left; 
  
    nodeX_left->right = nodeX; 
    nodeX->parent = nodeX_left; 
}

void inorder(FILE *fp, Node *node) {
    if(node == NULL)
        return;
    inorder(fp, node->left);
    fprintf(fp, "%d ", node->key);
    inorder(fp, node->right);
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

void printTree(Node *root, int space) { 
    if(root == NULL) return; 

    space += SPACE; 
    printTree(root->right, space); 
    fprintf(fp, "\n"); 
    
    for(int i = SPACE; i < space; i++) 
        fprintf(fp, " "); 
    fprintf(fp, "%d(%s)\n", root->key, (root->color == RED)?"R":"B"); 
    printTree(root->left, space); 
} 