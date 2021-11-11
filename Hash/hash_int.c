#define hash(v, m) (618033 * (unsigned)v % m)
#define hashtwo(v, m) (618033 * (unsigned)v % 97 + 1)

typedef struct {
  int key;
  int column;
  int row;
  int points;
}Item;

Item NULLITEM = {0, 0, 0, 0};

void ht_init(Item *ht, long int *M, long int *N) {
  *N = 0;
  *M = 16161;
  ht = (Item*)malloc(sizeof(Item) * *M);

  for (long int i = 0; i < *M; i++) {
    ht[i] = NULLITEM;
  }
}

void expand(Item *ht, int *M, int *N) {
  Item *t = ht;
  *M = *M * 2;
  ht = (Item*)malloc(sizeof(Item) * *M);

  for (int i = 0; i < *M / 2; i++) {
    if (t[i].key != NULLITEM.key && t[i].column != NULLITEM.column && t[i].row != NULLITEM.row) {
      ht_insert(t[i], ht, M, N);
    }
  }

  free(t);
}

void ht_insert(Item position, Item *ht, int *M, int *N) {
  int v = key(position);
  int i = hash(v, *M);
  int k = hashtwo(v, *M);
  
  while (ht[i].key != NULLITEM.key && ht[i].column != NULLITEM.column && ht[i].row != NULLITEM.row)
    i = (i + k) % *M;
  
  ht[i] = position;
  *N = *N + 1;

  if (*N >= *M / 2) {
    expand(ht, M, N);
  }
}

Item ht_search(Item position, Item *ht, long int *M) {
  int i = hash(position.key, *M);
  int k = hashtwo(position.key, *M);
  
  while (key(ht[i]) != key(NULLITEM)) {
    if (position.key == ht[i].key && position.column == ht[i].column && position.row == ht[i].row) {
      return ht[i];
    } else {
      i = (i + k) % *M;
    }
  }

  return NULLITEM;
}
