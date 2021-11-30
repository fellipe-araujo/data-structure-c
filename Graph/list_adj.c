#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50

typedef struct {
  int v;
  int w;
} Edge;

Edge EDGE(int v, int w);

typedef struct Node *Link;

struct Node {
  int value;
  Link next;
};

Link LINK(int value, Link next);

typedef struct {
  Link head;
  Link tail;
  int size;
} *Queue;

typedef struct graph * Graph;

struct graph {
  int total_vertices;
  int total_edges;
  Link *adj_list;
};

int pre[MAX_VERTICES], count;

Edge EDGE(int v, int w) {
  Edge edge;
  edge.v = v;
  edge.w = w;
  return edge;
}

Link LINK(int value, Link next) {
  Link x = malloc(sizeof(*x));
  x->value = value;
  x->next = next;
  return x;
}

Queue QUEUEInit() {
  Queue q = malloc(sizeof(Queue));
  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

void QUEUEPush(Queue q, int value) {
  if(!q->tail) {
    Link no = LINK(value, NULL);
    q->head = no;
    q->tail = no;
  }
  else {
    Link no = LINK(value, NULL);
    q->tail->next = no;
    q->tail = no;
  }

  q->size++;
}

int QUEUEPop(Queue q) {
  int aux;

  if(q->head) {
    Link temp = q->head;
    q->head = temp->next;
    aux = temp->value;
    free(temp);
    q->size--;
  }

  if(!q->size)
    q->head = q->tail = NULL;
  
  return aux;
}

int QUEUEEmpty(Queue q) {
  return !q->head;
}

int QUEUESize(Queue q) {
  return q->size;
}

Graph GRAPHInit(int qnt_vertices) {
  Graph graph = malloc(sizeof(*graph));
  graph->total_vertices = qnt_vertices;
  graph->total_edges = 0;
  graph->adj_list = malloc(qnt_vertices * sizeof(Link));

  for(int i = 0; i < qnt_vertices; i++)
    graph->adj_list[i] = NULL;

  return graph;
}

void GRAPHInsertEdge(Graph graph, Edge edge){
  int v = edge.v, w = edge.w;
  graph->adj_list[v] = LINK(w, graph->adj_list[v]);
  graph->adj_list[w] = LINK(v, graph->adj_list[w]);
  graph->total_edges++;
}

int RemoveEdge(Graph graph, int v, int w) {
  Link prev, next;
  prev = graph->adj_list[v];

  for(next = graph->adj_list[v]; next != NULL; next = next->next) {                
    if(next->value == w) {            
      if(prev->value == next->value)                
        graph->adj_list[v] = next->next;                
      else                
        prev->next = next->next;                
      return 1;
    }

    prev = next;
  }

  return 0;
}

void GRAPHRemoveEdge(Graph graph, Edge edge) {
  int v = edge.v, w = edge.w, removed_edge = 0;
  removed_edge = RemoveEdge(graph, v, w);
  removed_edge = RemoveEdge(graph, w, v);

  if(removed_edge)
    graph->total_edges--;
}

int GRAPHEdges(Edge edges[], Graph graph) {
  int v, qnt_edges = 0;
  Link t;

  for(v = 0; v < graph->total_vertices; v++) {
    for(t = graph->adj_list[v]; t != NULL; t = t->next)
      if(v < t->value) edges[qnt_edges++] = EDGE(v, t->value);
  }
  return qnt_edges;
}

void DFSR(Graph graph, Edge edge) {
  int w = edge.w;
  Link t;
  pre[w] = count++;

  for(t = graph->adj_list[w]; t != NULL; t = t->next) {
    if(pre[t->value] == -1)
      DFSR(graph, EDGE(w, t->value));
  }
}

void BFS(Graph graph, Edge edge) {
  int w = edge.w;
  Queue q = QUEUEInit();
  QUEUEPush(q, w);
  pre[w] = count++;

  while(!QUEUEEmpty(q)) {
    w = QUEUEPop(q);
    Link t = graph->adj_list[w];

    for(t = graph->adj_list[w]; t != NULL; t = t->next) {
      if(pre[t->value] == -1) {
        QUEUEPush(q, t->value);
        pre[t->value] = count++;
      }
    }
  }
}
