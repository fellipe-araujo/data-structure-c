#include <stdio.h>
#include <stdlib.h>

#define key(a) (a)

#define lesseq(a, b) (key(a) <= key(b))

typedef struct Item {
  int code;
  char title[15];
}Item;

int binarySearch(Item *vector, int qtd_itens, int target) {
   int left = -1;
   int right = qtd_itens;

   while (left < right - 1) {
      int middle = (left + right) / 2;

      if (vector[middle].code < target) {
         left = middle;
      } else {
         right = middle;
      }
   }

   return right;
}