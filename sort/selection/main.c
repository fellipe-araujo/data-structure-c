typedef int Item;

#define key(a) (a)

#define less(a, b) (key(a) < key(b))

#define exch(a, b) { Item t = a; a = b; b = t; }

#define cmpexch(a, b) { if (less(b, a)) exch(a, b); }

void selectionSort(Item *vector, int left, int right){
  if (left == right)
    return;

  int min = left;

  for (int j = left + 1; j < right; j++){
    if (less(vector[j], vector[min]))
      min = j;
  }

  exch(vector[min], vector[left]);
  selectionSort(vector, left + 1, right);
}
