// Depth First Search
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define WHITE 1
#define GRAY 2
#define BLACK 3
#define NIL -1

typedef struct Vertex {
    int color;
    int d,f;
    int pre;
} Vertex;

Vertex *vertex;
int time=0, num_vertex, **adj;
FILE *input_fp, *output_fp;    

void dfs(int);
void dfsVisit(int);

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
    output_fp = fopen("./output_dfs.txt", "w");
    dfs(start-1);
    fclose(output_fp);
    return 0;
}

void dfs(int start) {
    int i;
    for(i = 0; i < num_vertex; i++) {
        vertex[i].color = WHITE;
        vertex[i].pre = NIL;
    }
    dfsVisit(start);
    time = 0;
    for(i = 0; i < num_vertex; i++) {
        if(vertex[i].color == WHITE)
            dfsVisit(i);
    }
}

void dfsVisit(int u) {
    int i;
    time = time + 1;

    vertex[u].d = time;
    vertex[u].color = GRAY;

    for(i = 0; i < num_vertex; i++) {
        if((adj[u][i]) && vertex[i].color == WHITE) {
            vertex[i].pre = u;
            dfsVisit(i);
        }
    }
    vertex[u].color=BLACK;
    time = time + 1;
    vertex[u].f=time;

    fprintf(output_fp, "v%d(%d|%d)\n", u+1, vertex[u].d, vertex[u].f);
}


