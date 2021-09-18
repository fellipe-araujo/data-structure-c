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

POINT createNewNode(TYPEKEY k) {
  POINT newNode = (POINT)malloc(sizeof(NODE));

  newNode->key = k;
  newNode->left = NULL;
  newNode->right = NULL;

  return(newNode);
}
