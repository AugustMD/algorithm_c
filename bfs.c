// Breadth First Search
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define INFINITY -1
#define NIL 0

typedef struct Vertex {
    int color;
    int distance;
    int pre;
} Vertex;

Vertex *vertex;

typedef struct Queue {
    int n;
    struct Queue *next;
} Queue;

Queue *front = NULL, *rear = NULL;

int time=0, num_vertex, **adj;
FILE *input_fp, *output_fp;    

void enqueue(int);
int dequeue();
void bfs(int);

int main() {
    int i, j, start;
    input_fp = fopen("./graph.txt", "r");
    fscanf(input_fp, "%d\n", &num_vertex);
    vertex = (Vertex*)malloc(num_vertex * sizeof(Vertex));
    adj=(int**)malloc(num_vertex * sizeof(int*));
    for(i = 0; i < num_vertex; i++) 
        adj[i] = (int*)malloc(num_vertex * sizeof(int));

    for(i = 0; i < num_vertex; i++) {
        for(j = 0; j < num_vertex; j++) {
            fscanf(input_fp, "%d", &adj[i][j]);
        }
    }
    fclose(input_fp);

    printf("Enter the starting vertex : ");
    scanf("%d",&start);
    output_fp = fopen("./output_bfs.txt", "w");
    bfs(start);
    fclose(output_fp);

    return 0;
}

void enqueue(int num) {
    Queue *element;
    element = (Queue*)malloc(sizeof(Queue));
    element->n = num;
    element->next = NULL;
    if(front == NULL) {
        front = element;
        rear = element;
    } else {
        rear->next = element;
        rear = rear->next;
    }
}

int dequeue() {
    int x;
    Queue *temp;
    if(front == NULL)
        x = (int)NULL;
    else if((rear == front) && (front != NULL)) {
        x = front->n;
        free(front);
        front = NULL;
        rear = NULL;
    } else {
        x = front->n;
        temp = front;
        front = front->next;
        free(temp);
    }
    return x;
}

void bfs(int start) {
    int i,u;
    for(i = 0; i < num_vertex; i++) {
        if(i == (start-1)) continue;
        vertex[i].color = WHITE;
        vertex[i].distance = INFINITY;
        vertex[i].pre = NIL;
    }
    vertex[start-1].color = GRAY;
    vertex[start-1].distance = 0;
    vertex[start-1].pre = NIL;
    enqueue(start);
    while((u = dequeue()) != 0) {
        for(i = 0; i < num_vertex; i++) {
            if(adj[u-1][i] && (vertex[i].color==WHITE)) {
                vertex[i].color = GRAY;
                vertex[i].distance = vertex[u-1].distance + 1;
                vertex[i].pre = u;
                enqueue(i+1);
            }
        }
        vertex[u-1].color=BLACK;
        fprintf(output_fp, "v%d(%d) \n", u, vertex[u-1].distance);
    }
}

