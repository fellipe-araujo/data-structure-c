typedef struct Item {
  int code;
  char letter;
}Item;

#define key(a) (a)

#define less(a, b) (key(a) < key(b))

#define lesseq(a, b) (key(a) <= key(b))

#define exch(a, b) { Item t = a; a = b; b = t; }

#define cmpexch(a, b) { if(less(b, a)) exch(a, b); }

void merge(Item *vector, int left, int middle, int right) {
  // Item *v2 = malloc(sizeof(Item) * (right - left + 1));
  Item vector2[right - left + 1];

  int k = 0;
  int i = left;
  int j = middle + 1;

  while (i <= middle && j <= right) {
    if (lesseq(vector[i].code, vector[j].code)) {
      vector2[k++] = vector[i++];
    } else {
      vector2[k++] = vector[j++];
    }
  }

  while (i <= middle) {
    vector2[k++] = vector[i++];
  }

  while (j <= right) {
    vector2[k++] = vector[j++];
  }

  k = 0;
  for (i = left; i <= right; i++) {
    vector[i] = vector2[k++];
  }
}

void mergeSort(Item *vector, int left, int right) {
  int middle = (right + left) / 2;

  if(middle == left && middle == right) {
    return;
  }

  mergeSort(vector, left, middle);
  mergeSort(vector, middle + 1, right);
  merge(vector, left, middle, right);
}
