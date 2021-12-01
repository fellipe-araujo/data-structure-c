#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50
#define INT_MAX 9999

typedef struct {
  int v;
  int w;
  int c;
} Edge;

Edge EDGE(int v, int w, int c);

typedef struct Node *Link;

struct Node{
  int value;
  int cost;
  Link next;
};

Link LINK(int value, int cost, Link next);

typedef struct {
  Link head;
  Link tail;
  int size;
} *Queue;

// Adjacency List
typedef struct graph * Graph;

struct graph{
  int total_vertices;
  int total_edges;
  Link *adj_list;
  int **transitive_closure; // Uncomment for Floyd Warshall
};

int ** MATRIXInit(int row, int col, int start_value);
Graph GRAPHInit(int qnt_vertices);
void GRAPHInsertEdge(Graph graph, Edge edge);
void GRAPHRemoveEdge(Graph graph, Edge edge);
int RemoveEdge(Graph graph, int v, int w);
int GRAPHEdges(Edge edges[], Graph graph);
Graph GRAPHCopy(Graph graph);

// Directed Graph
Graph GRAPHReverse(Graph graph);
void GRAPHPrint(Graph graph);
void GRAPHDestroy(Graph graph);
void DFSR(Graph graph, Edge edge);
void BFS(Graph graph, Edge edge);
// Directed Graph

// Floyd Warshall - transitive closure
void GRAPHTc(Graph graph);
int GRAPHReach(Graph graph, int s, int t); // s: source; t: to

// Bellmon Ford 
int GRAPHcptBF(Graph graph, int s, int *parent, int *distances);

// Dijkstra ingênuo
void GRAPHcptD1(Graph graph, int s, int *parent, int *distances);

int pre[MAX_VERTICES], count;

Edge EDGE(int v, int w, int c) {
  Edge edge;
  edge.v = v;
  edge.w = w;
  edge.c = c;
  return edge;
}

Link LINK(int value, int cost, Link next) {
  Link x = malloc(sizeof(*x));
  x->value = value;
  x->cost = cost;
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
    Link no = LINK(value, 0, NULL);
    q->head = no;
    q->tail = no;
  }
  else {
    Link no = LINK(value, 0, NULL);
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

int **MATRIXInit(int row, int col, int start_value) {
  int **matrix = malloc(row * sizeof(int*));

  for(int i = 0; i < row; i++)
    matrix[i] = malloc(col * sizeof(int));

  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++)
      matrix[i][j] = start_value;
  }

  return matrix;
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

void GRAPHInsertEdge(Graph graph, Edge edge) {
  int v = edge.v, w = edge.w, c = edge.c;
  graph->adj_list[v] = LINK(w, c, graph->adj_list[v]);
  graph->total_edges++;
}

void GRAPHRemoveEdge(Graph graph, Edge edge) {
  int v = edge.v, w = edge.w, removed_edge = 0;
  removed_edge = RemoveEdge(graph, v, w);

  if(removed_edge)
    graph->total_edges--;
}

int RemoveEdge(Graph graph, int v, int w) {
  Link prev, next;
  prev = graph->adj_list[v];

  for(next = graph->adj_list[v]; next!=NULL; next=next->next) {                
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

int GRAPHEdges(Edge edges[], Graph graph) {
  int v, qnt_edges = 0;
  Link t;

  for(v = 0; v < graph->total_vertices; v++) {
    for(t = graph->adj_list[v]; t != NULL; t = t->next)
      if(v < t->value) edges[qnt_edges++] = EDGE(v, t->value, t->cost);
  }

  return qnt_edges;
}

Graph GRAPHCopy(Graph graph) {
  Graph copy = GRAPHInit(graph->total_vertices);
  Link t;
  copy->total_edges = graph->total_edges;

  for(int v = 0; v < graph->total_vertices; v++) {
    for(t = graph->adj_list[v]; t != NULL; t = t->next) {
      if(v < t->value) {
        copy->adj_list[v] = LINK(t->value, t->cost, copy->adj_list[v]);
      }
    }
  }

  return copy;
}

// Directed Graph
Graph GRAPHReverse(Graph graph) {
  Graph reverse = GRAPHInit(graph->total_vertices);
  Link t;
  reverse->total_edges = graph->total_edges;

  for(int v = 0; v < graph->total_vertices; v++) {
    for(t = graph->adj_list[v]; t != NULL; t = t->next)
      GRAPHInsertEdge(reverse, EDGE(t->value, v, t->cost));
  }

  return reverse;
}

void DFSR(Graph graph, Edge edge) {
  int w = edge.w;
  Link t;
  pre[w] = count++;

  for(t = graph->adj_list[w]; t != NULL; t = t->next) {
    if(pre[t->value] == -1)
      DFSR(graph, EDGE(w, t->value, t->cost));
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

// Directed Graph Flyd Warshall
void GRAPHTc(Graph graph) {
  graph->transitive_closure = MATRIXInit(graph->total_vertices, graph->total_vertices, 0);

  for(int v = 0; v < graph->total_vertices; v++) {
    for(Link t = graph->adj_list[v]; t != NULL; t = t->next)
      graph->transitive_closure[v][t->value] = 1;
  }

  for(int s = 0; s < graph->total_vertices; s++)
    graph->transitive_closure[s][s] = 1;
  
  for(int i = 0; i < graph->total_vertices; i++) {
    for(int s = 0; s < graph->total_vertices; s++) {
      if(graph->transitive_closure[i][s] == 1) {
        for(int t = 0; t < graph->total_vertices; t++) {
          if(graph->transitive_closure[i][t] == 1)
            graph->transitive_closure[s][t] = 1;
        }
      }
    }
  }
}

int GRAPHReach(Graph graph, int s, int t) {
  return graph->transitive_closure[s][t];
}

int GRAPHcptBF(Graph graph, int source, int *parent, int *distances) {
  int on_queue[MAX_VERTICES], cycles = 0;

  for(int v=0; v < graph->total_vertices; v++) {
    parent[v] = -1;
    distances[v] = INT_MAX;
    on_queue[v] = 0;
  }

  parent[source] = source;
  distances[source] = 0;
  Queue q = QUEUEInit();
  QUEUEPush(q, source);
  on_queue[source] = 1;
  QUEUEPush(q, graph->total_vertices);

  while(1) {
    int v = QUEUEPop(q);
    if(v < graph->total_vertices) {
      for(Link t = graph->adj_list[v]; t!=NULL; t=t->next) {
        if(distances[v] + t->cost < distances[t->value]){
          distances[t->value] = distances[v] + t->cost;
          parent[t->value] = v;

          if(on_queue[t->value] == 0) {
            QUEUEPush(q, t->value);
            on_queue[t->value] = 1;
          }
        }
      }
    }
    else {
      if(QUEUEEmpty(q)) return 1;
      if(++cycles >= graph->total_vertices) return 0;

      QUEUEPush(q, graph->total_vertices);

      for(int v = 0; v < graph->total_vertices; v++)
        on_queue[v] = 0;
    }
  }
}

void GRAPHcptD1(Graph graph, int s, int *parent, int *distances) {
  int mature[MAX_VERTICES];

  for(int v = 0; v < graph->total_vertices; v++) {
    parent[v] = -1;
    distances[v] = INT_MAX;
    mature[v] = 0;
  }

  parent[s] = s;
  distances[s] = 0;
    
  while(1) {
    int min = INT_MAX, y;

    for(int z = 0; z < graph->total_vertices; z++) {
      if(mature[z]) continue;
      if(distances[z] < min) {
        min = distances[z];
        y = z;
      }
    }
    if(min == INT_MAX) break;

    for(Link t = graph->adj_list[y]; t != NULL; t = t->next) {
      if(mature[t->value] == 1) continue;
      if(distances[y] + t->cost < distances[t->value]) {
        distances[t->value] = distances[y] + t->cost;
        parent[t->value] = y;
      }
    }
    mature[y] = 1;
  }
}
