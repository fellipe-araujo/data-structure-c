typedef int Item;

#define key(a) (a)

#define less(a, b) (key(a) < key(b))

#define exch(a, b) { Item t = a; a = b; b = t; }

#define cmpexch(a, b) { if(less(b, a)) exch(a, b); }

void bubbleSort(Item *vector, int left, int right) {
  for (int i = left; i < right; i++) {
    int flag = 0;
    for (int j = left; j < right; j++) {
      if (less(vector[j + 1], vector[j])) {
        exch(vector[j], vector[j + 1]);
        flag = 1;
      }
    }

    if (flag = 0) {
      break;
    }
  }
}