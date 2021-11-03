#define key(a) (a.key)
#define less(a, b) (a < b)
#define exch(a, b) \
  {                \
    Item t = a;    \
    a = b;         \
    b = t;         \
  }

typedef struct {
  int key;
  int column;
  int row;
  int points;
}Item;

typedef struct {
  Item *pq;
  int N;
}PQ_ST;

void fix_up(Item *vector, int k) {
  while (k > 1 && vector[k/2].points < vector[k].points) {
    exch(vector[k], vector[k/2]);
    k = k/2;
  }
}

void fix_down(Item *vector, int k, int n) {
  int j;

  while (2 * k <= n) {
    j = 2 * k;

    if (j < n && less(vector[j].points, vector[j + 1].points)) {
      j++;
    }

    if (!less(vector[k].points, vector[j].points))
      break;

    exch(vector[k], vector[j]);
    k = j;
  }
}

void PQ_init(PQ_ST *PQ) {
  PQ->pq = malloc(sizeof(Item) * 1000);
  PQ->N = 0;
}

void PQ_insert(Item position, PQ_ST *PQ) {
  PQ->N++;
  PQ->pq[PQ->N] = position;
  fix_up(PQ->pq, PQ->N);

  if (!(PQ[PQ->N + 2].pq->key)) {
    PQ->pq = realloc(PQ->pq, sizeof(Item) * (PQ->N + 2) * 2);
  }
}

Item PQ_remove_max_priority(PQ_ST *PQ) {
  exch(PQ->pq[1], PQ->pq[PQ->N]);
  fix_down(PQ->pq, 1, --PQ->N);
  return PQ->pq[PQ->N + 1];
}
