typedef struct {
  char key[30]; // Chave de 1 item (concatenação de linha + coluna)
  long int column;
  long int row;
  long int points;
}Item;

Item NULLITEM = {'0', 0, 0, 0, 0};

void format_key(Item *position) {
  char number[30];
  char string[30];

  number[0] = '\0';
  string[0] = '\0';

  memset(position->key, '0', strlen(position->key));
  sprintf(number, "%ld", position->row);
  strcat(string, number);
  memset(number, '0', strlen(number));
  sprintf(number, "%ld", position->column);
  strcat(string, number);
  strcpy(position->key, string);
  position->key[strlen(position->key)] = '\0';
}

int hash_string(char *ch, int *M) {
  // 'a' e 'b' podem sem 2 números quaisquer
  unsigned int h;
  unsigned int a = 31415;
  int b = 27183;

  for (h = 0; *ch != '\0'; ch++) {
    a = a * b % (*M - 1);
    h = (a * h + *ch) % *M;
  }

  return h;
}

void ht_insert(Item *ht, int *M, int *N, Item item) {
  int i = hash_string(item.key, M);

  ht[i] = item;
  *N = *N + 1;
}

Item ht_search(Item *ht, int *M, Item position) {
  int i = hash_string(position.key, M);

  if (strcmp(ht[i].key, NULLITEM.key) != 0)
    return ht[i];

  return NULLITEM;
}