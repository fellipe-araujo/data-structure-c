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

POINT insertNode(POINT root, POINT node) {
  if (root == NULL) return(node);
  if (node->key < root->key) {
    root->left = insertNode(root->left, node);
  } else {
    root->right = insertNode(root->right, node);
  }

  return(root);
}

POINT search(TYPEKEY k, POINT root) {
  if (root == NULL) return(NULL);
  if (root->key == k) return(root);
  if (root->key > k) {
    return (search(k, root->right));
  }

  return(search(k, root->right));
}
