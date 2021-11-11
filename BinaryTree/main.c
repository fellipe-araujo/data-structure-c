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

void printTree(POINT root) {
  if (root != NULL) {
    printf("%i", root->key);
    printf("(");

    printTree(root->left);
    printTree(root->right);

    printf(")");
  }
}

POINT searchNodeAux(POINT root, TYPEKEY k, POINT *father) {
  POINT current = root;
  *father = NULL;

  while (current) {
    if (current->key == k) return(current);

    *father = current;

    if (k < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  return(NULL);
}

POINT removeNode(POINT root, TYPEKEY k) {
  POINT father, node, p, q;
  node = searchNodeAux(root, k, &father);

  if (node == NULL) return(root);
  if (!node->left || !node->right) {
    if (!node->left) {
      q = node->right;
    } else {
      q = node->left;
    }
  } else {
    p = node;
    q = node->left;

    while (q->right) {
      p = q;
      q = q->right;
    }

    if (p != node) {
      p->right = q->left;
      q->left = node->left;
    }

    q->right = node->right;
  }

  if (!father) {
    free(node);
    return(q);
  }

  if (k < father->key) {
    father->left = q;
  } else {
    father->right = q;
  }

  free(node);
  return(root);
}
