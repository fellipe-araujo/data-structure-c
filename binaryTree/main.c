#include <stdio.h>
#include <stdlib.h>

typedef int bool;
typedef int TYPEKEY;

typedef struct aux {
  TYPEKEY key;
  struct aux *left, *right;
} NODE;

typedef NODE* POINT;

POINT init() {
  return(NULL);
}
