typedef int Item;

#define key(a) (a)

#define less(a, b) (key(a) < key(b))

#define exch(a, b) { Item t = a; a = b; b = t; }

#define cmpexch(a, b) { if(less(b, a)) exch(a, b); }

void insertionSort(Item *vector, int n){
  int i;

  for(i = 1; i < n; i++){
    Item temp = vector[i];
    int j = i - 1;

    while(j >= 0 && vector[j] > temp){
      vector[j + 1] = vector[j];
      j = j - 1;
    }

    vector[j + 1] = temp;
  }
}
