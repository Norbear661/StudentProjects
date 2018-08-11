//Norbert Manatad
//nmanatad
//FindPath.c
//cmps101

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
/*1. Read and store the graph and print out its adjacency list representation.

2. Enter a loop that processes the second part of the input. Each iteration of 
the loop should read in one pair of vertices (source, destination), run BFS on 
the source vertex, print the distance to the destination vertex, then find and 
print the resulting shortest path, if it exists, or print a message if no path 
from source to destination exists (as in the above example).*/

int main(int argc, char* argv[]){
    FILE *in;
    FILE *out;
    char c[10];
    int size; 
    int v;
    int e; 
    int source;
    int destination;
    Graph G;

    if(argc != 3){
        printf("Usage: %s <input file> <output file> \n", argv[0]);
        exit (1);
    }
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if(fgets(c, 10, in) != NULL){
        size = atoi(c);
        G = newGraph(size);        
    }
    int x, y;
    while(fgetc(in) != EOF){
        fscanf(in, "%d", &v);
        fscanf(in, "%d", &e);
        if(v == 0 && e == 0){
            break;
        }
        addEdge(G, v, e);
    }
    printGraph(out, G);
    fprintf(out, "\n");
    List newList = newList();

     while(fgetc(in) != EOF){
        fscanf(in, "%d", &source);
        fscanf(in, "%d", &destination);
        if(source == 0 && destination == 0){
            break;
        }
        BFS(G, source);
        getPath(newList, G, destination);
        if(length(L) == 0){
            fprintf(out, "\nThe distance from %d to %d is infinity", source, destination);
            fprintf(out, "\nNo %d-%d path exists\n", source, destination);
        } else {
            fprintf(out, "\nThe distance from %d to %d is %d", source, destination, (G, destination));
            fprintf(out, "A shortest %d-%d path is: ", source, destination);
            printList(out, newList);
        }
        clear(newList);
    }
freeGraph(&G);
freeList(&newList);
fclose(in);
fclose(out);
}



