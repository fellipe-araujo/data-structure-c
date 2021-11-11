#include <stdio.h>

typedef struct Node *Link;

struct Node {
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

Link LINK(int value, int cost, Link next){
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
  } else {
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

void QUEUEClear(Queue q) {
  if(!q->head) return;
  else {
    Link p = q->head;

    for(int i = 0; i < QUEUESize(q); i++) {
      Link temp = p;
      p = temp->next;
      free(temp);
    }

    q->head = q->tail = NULL;
    q->size = 0;
  }
}

int QUEUESize(Queue q){
  return q->size;
}
