#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct location{
    int vertice;
    char name[50];
}location;

typedef struct Bin{
    int hasBin;
    int FullLevel;
}bin;

// Dijkstra's 
void dijkstra(int n, int adj[][n], int start, int dist[], int parent[]);

// Greedy (to reach all nearest node)
void greedyCollectionRoute(int n, int adj[][n], int start, bin binArr[], 
                          location loc[], int route[], int *routeLen, 
                          int *totalDist, int truckCapacity);

#endif
