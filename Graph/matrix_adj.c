#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int v, w;
} Edge;

Edge EDGE(int a, int b) {
  Edge edge = {a, b};

  return edge;
}

typedef struct graph {
  int vertex;
  int edge;
  int **adj;
} graph, *Graph;

static int **MATRIXinit(int row, int column, int value) { 
  int **matrix = malloc(row * sizeof (int *));

  for (int i = 0; i < row; ++i) 
    matrix[i] = malloc(column * sizeof (int));

  for (int i = 0; i < row; ++i)
    for (int j = 0; j < column; ++j)
        matrix[i][j] = value;

  return matrix;
}

Graph GRAPHinit(int vertex) {
  Graph G = malloc(sizeof(graph));

  G->vertex = vertex;
  G->edge = 0;
  G->adj = MATRIXinit(vertex, vertex, 0);

  return G;
}

void GRAPHinsertE(Graph G, Edge edge) {
  int v = edge.v;
  int w = edge.w;

  if (G->adj[v][w] == 0)
    G->edge++;
    G->adj[v][w] = 1;
    // G->adj[w][v] = 1;
}
