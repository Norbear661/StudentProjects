//Norbert Manatad
//nmanatad
//Graph.c
//cmps101

#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

#define NIL (-1)
#define infinity (-2)
//#define dequeue(List Q) deleteFront(Q)

typedef struct GraphObj{
    List* neighbors;
    //colors: (white == w)//(black == b)//(gray == g);
    char* colors;
    int* parents;
    int* distance;

    int order;
    int size;
    int source;
}GraphObj;

//typedef struct GraphObj* Graph;

Graph newGraph(int n){
    int length = n + 1;
    Graph newGraph = malloc(sizeof(GraphObj));
    newGraph->neighbors = calloc(length, sizeof(List));
    newGraph->colors = calloc(length, sizeof(char));
    newGraph->parents = calloc(length, sizeof(int));
    newGraph->distance = calloc(length, sizeof(int));

    newGraph->order = n;
    newGraph->size = 0;
    newGraph->source = NIL;

    for(int i = 1; i <= n; i++){
        newGraph->neighbors[i] = newList();
        newGraph->colors[i] = 'w';
        newGraph->parents[i] = NIL;
        newGraph->distance[i] = infinity;
    }
    return newGraph;
}

void freeGraph(Graph* pG){
    Graph temp = *pG;
    for(int i = 1; i <= temp->order; i++){
        freeList(&temp->neighbors[i]);
    }
    free(temp->neighbors);
    free(temp->colors);
    free(temp->parents);
    free(temp->distance);
    *pG = NULL;
}
int getOrder(Graph G){
    if(G == NULL){
        printf("error: called getOrder on invalid graph\n");
        exit(1);
    }
    return G->order;
}

int getSize(Graph G){
    if(G == NULL){
        printf("error: called getSize on invalid graph\n");
        exit(1);
    }
    return G->size;
}

int getSource(Graph G){
    if(G == NULL){
        printf("error: called getSource on invalid graph\n");
        exit(1);
    }    
    return G->source;
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("error: called getParent on invalid graph\n");
        exit(1);
    }
    if(u < 1 || u > G->order){
        printf("error: called getParent on an invalid vertex\n");
        exit(1);
    }
    return G->parents[u];
}

int getDist(Graph G, int u){
    if(G == NULL){
        printf("error: called getDist on invalid graph\n");
        exit(1);
    }
    if(u < 1 || u > G->order){
        printf("error: called getDist on an invalid vertex\n");
        exit(1);
    }
    if(u == G->source){//tbh it should be zero, i dont know why it would be infinity
        return infinity;
    }
    return G->distance[u];
}

void getPath(List L, Graph G, int u){
    int gp = getParent(G, u);
    if(G == NULL){
        printf("error: called on getPath on an invalid Graph\n");
        exit(1);
    }
    if(getSource(G) == NIL){
        printf("errror: called getPath with an invalid source\n");
        exit(1);
    }
    if(u < 1 || u > G->order){
        printf("error: called getPath on an invalid input\n");
        exit(1);
    }
    if(u == G->source){//rip having a path to yourself
        append(L, u);
    } else {
        while(G->parents[u] != NIL){
            append(L, gp);
            gp = getParent(G, G->parents[u]);
        }
    }
}

void makeNull(Graph G){
    for(int i = 1; i <= G->order; i++){
        clear(G->neighbors[i]);
    }
    G->size = 0;
}

void sortAlgorithm(List L, Graph G, int x){
    if(L == NULL){
        printf("error: sortAlgorithm being called on invalid List\n");
        exit(1);
    }
    if(getIndex(L) == - 1){
        append(L, x);
        G->size++;
    }
    for(moveFront(L); getIndex(L) >= 0; moveNext(L)){
        int compared = get(L);
        if(x < compared){
            //printf("here2\n");
            insertBefore(L,x);
            G->size++;
            break;
        }
    } 
}

void addEdge(Graph G, int u, int v){
    if(G == NULL){
        printf("error: calling addEdge on invalid graph\n");
        exit(1);
    }
    if(u < 1 || u > G->order || v < 1 || v > G->order){
        printf("error: invalid arguments in addEdge\n");
        exit(1);
    }
    //  printf("here");
    sortAlgorithm(G->neighbors[u], G, v);
    sortAlgorithm(G->neighbors[v], G, u);
}

void addArc(Graph G, int u, int v){
    if(G == NULL){
        printf("error: calling addArc on invalid graph\n");
        exit(1);
    }
    if(u < 1 || u > G->order || v < 1 || v > G->order){
        printf("error: invalid arguments in addArc\n");
        exit(1);
    }
    sortAlgorithm(G->neighbors[u], G, v);
}

void BFS(Graph G, int s){//the algorithm for this was from the last page on the midterm 2 that we were allowed to take home
    if(G == NULL){
        printf("error: calling BFS on an invalid graph\n");
        exit(1);
    }
    if(s < 1 || s > G->order){
        printf("error: calling BFS with invalid input\n");
        exit(1);
    }
    for(int i = 1; i <= G->order; i++){
        G->colors[i] = 'w';
        G->distance[i] = infinity;
        G->parents[i] = NIL;
    }
    G->colors[s] = 'g';
    G->distance[s] = 0;
    G->parents[s] = NIL;
    List Q = newList();
    if(Q == NULL){
        printf("error: invalid list call in BFS\n");
        exit(1);
    }
    append(Q, s);//same as Enqueue
    while(length(Q) > 0){
        int x = front(Q);
        //printf("hello there");
        //printf("%d", length(Q));
        deleteFront(Q);
        List Y = G->neighbors[x];
        for(moveFront(Y); getIndex(Y) >= 0; moveNext(Y)){
            if(G->colors[get(Y)] == 'w'){
                G->colors[get(Y)] = 'g';
                G->distance[get(Y)] = G->distance[x] + 1;
                G->parents[get(Y)] = x;
                append(Q,get(Y));
            }
        }
        G->colors[x] = 'b'; 
    }
    freeList(&Q);
}

void printGraph(FILE* out, Graph G){
    if(G == NULL){
        printf("error: called printGraph on an invalid Graph\n");
        exit(1);
    }
    for(int i = 1; i <= G->order; i++){
        fprintf(out, "%d: ", i);
        //printf("hello\n");
        printList(out, G->neighbors[i]);   
    }
}

