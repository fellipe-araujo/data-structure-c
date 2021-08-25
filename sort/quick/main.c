typedef int Item;

#define key(a) (a)

#define less(a, b) (key(a) < key(b))

#define lesseq(a, b) (key(a) <= key(b))

#define exch(a, b) { Item t = a; a = b; b = t; }

#define cmpexch(a, b) { if(less(b, a)) exch(a, b); }

static int partition(Item *vector, int left, int right) {
  int i = left;
  Item pivot = vector[right];

  for (int j = left; j < right; j++) {
    if (lesseq(vector[j], pivot)) {
      exch(vector[j], vector[i]);
      i++;
    }
  }

  exch(vector[i], vector[right]);

  return i;
}

/* =============== QuickSort Mediana de 3  =============== */

void quickSortM3(Item *vector, int left, int right) {
  int j;
  int average = (left + right) / 2;

  if (right <= left) return;

  cmpexch(vector[average], vector[right]);
  cmpexch(vector[left], vector[average]);
  cmpexch(vector[right], vector[average]);

  j = partition(vector, left, right);
  quickSortM3(vector, left, j - 1);
  quickSortM3(vector, j + 1, right);
}

/* ========== QuickSort Mediana de 3 com InsertionSort ========== */

void insertionSort(Item *vector, int left, int right) {
  for(int i = right; i > left; i--) {
    cmpexch(vector[i - i], vector[i]);
  }

  for (int i = left + 2; i <= right; i++) {
    int j = i;
    Item tmp = vector[j];

    while (less(tmp, vector[j - 1])) {
      vector[j] = vector[j - 1];
      j--;
    }

    vector[j] = tmp;
  }
}

void quickSortM3Insertion(Item *vector, int left, int right) {
  int j;
  int average = (left + right) / 2;

  if (right - left <= 32) return;

  exch(vector[average], vector[right - 1]);
  cmpexch(vector[left], vector[right - 1]);
  cmpexch(vector[left], vector[right]);
  cmpexch(vector[right - 1], vector[right]);

  j = partition(vector, left + 1, right - 1);
  quickSort(vector, left, j - 1);
  quickSort(vector, j + 1, right);
}

void sort(Item *vector, int left, int right) {
  quickSortM3Insertion(vector, left, right);
  insertionSort(vector, left, right);
}
