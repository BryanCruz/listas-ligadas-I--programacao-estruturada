#include <stdio.h>
#include <stdlib.h>

typedef struct s_no * no;

struct s_no {
  int item;
  no  prox;
};

// 1. Cria um novo nó da lista.
no novo(int item) {
  no x = (no) malloc(sizeof(struct s_no));

  if (x == NULL) {
    fprintf(stderr, "Memória insuficiente.\n");
    exit(1);
  }

  x->item = item;
  x->prox = NULL;

  return x;
}

// 2. Deleta um nó.
void deleta(no x) {
  free(x);
}

// 3. Insere um nó no início da lista (como PUSH).
//    (Supõem que x e inicio são ambos diferentes de NULL.)
//    (Mas *inicio pode ser NULL.)
void insere_inicio(no *inicio, no x) {
  x->prox = *inicio;
  *inicio = x;
}

// 4. Remove o primeiro nó da lista.
//    (Se o valor de retorno fosse o item do nó removido,
//    essa função seria como POP.)
void remove_inicio(no *inicio) {
  no x = *inicio;
  if (*inicio != NULL) {
    *inicio = x->prox;
    deleta(x);
  }
}

// 5. Imprime todos os elementos de uma lista
//    (supondo que sejam inteiros).
void imprime(no inicio) {
  no x;
  for (no x = inicio; x != NULL; x = x->prox)
    printf("%d ", x->item);
  printf("\n");
}

// 6. Busca o primeiro nó contendo item.
//    Retorna NULL se não encontrar o nó.
no busca(no inicio, int item) {
  for (; inicio != NULL && inicio->item != item;
       inicio = inicio->prox);
  return inicio;
}

// 7. Busca o primeiro nó contendo item, recursivamente.
//    Retorna NULL se não encontrar o nó.
no buscaR(no inicio, int item) {
  if (inicio == NULL)
    return NULL;
  if (inicio->item == item)
    return inicio;
  return buscaR(inicio->prox, item);
}

// 8 (EXERCÍCIO) Devolve o último nó de uma lista.
no final(no inicio){
  if(inicio == NULL){
    return NULL;
  }

  while(inicio->prox != NULL){
    inicio = inicio->prox;
  }
  return inicio;
}

// 9. (EXERCÍCIO) Insere nó no final.
//    (Supõem que x e inicio são ambos diferentes de NULL.)
//    (Mas *inicio pode ser NULL.)
void insere_final(no *inicio, no x){
  if(*inicio == NULL){
    *inicio = x;
  }else{
    no y = final(*inicio);
    y->prox = x;
  }
}

// 10. (EXERCÍCIO) Insere nó no final, recursivamente.
//    (Supõem que x e inicio são ambos diferentes de NULL.)
//    (Mas *inicio pode ser NULL.)
void insere_finalR(no *inicio, no x){
  if(*inicio == NULL){
    *inicio = x;
  }else{
    insere_finalR(&((*inicio)->prox), x);
  }
}

// 11. Remove primeiro nó que contém item.
//    (Supõem que inicio é diferente de NULL.
//    (*inicio pode ser NULL.)
//    (EXERCÍCIO: entender o que a função faz.)
void remove_um(no *inicio, int item) {
  no x = *inicio, *aux = inicio;
  while(x != NULL && x->item != item){
    aux = &(x->prox);
    x = x->prox;
  }

  if(x != NULL){
    *aux = x->prox;
    deleta(x);
  }
}

// 11. Remove primeiro nó que contém item.
//     (Provavelmente a 1ª idéia que vem à mente.)
void remove_um_v1(no *inicio, int item) {
  if (*inicio == NULL)
    return;

  no x = *inicio, y;

  if (x->item == item) {
    *inicio = x->prox;
    deleta(x);
    return;
  }

  while (x->prox != NULL && x->prox->item != item)
    x = x->prox;

  if (x->prox == NULL)
    return;

  y = x->prox;
  x->prox = y->prox;
  deleta(y);
}

// 12. (EXERCÍCIO) Remove todos os nós contendo item.
void remove_todos(no *inicio, int item){
  //x é copia, *aux é referencia, aux é cópia da referencia
  no x = *inicio, *aux = inicio;

  while(x != NULL){
    if(x->item == item){
      *aux = x->prox;
      deleta(x);

      x = *aux;
    }else{
      aux = &(x->prox);
      x = x->prox;
    }
  }
}

// 13. (EXERCÍCIO) Remove todos os nós contendo item, recursivo.
//     Este fica mais simples que o anterior.
void remove_todosR(no *inicio, int item){
  if(*inicio != NULL){
    no x = *inicio;
    remove_todosR(&(x->prox), item);

    if(x->item == item){
       *inicio = x->prox;
       deleta(x);
    }
  }
}

// 14. (EXERCÍCIO) Cria uma cópia da lista dada
//     (copiar em outras posições de memória, é claro).
no copia(no inicio){
  no inicioCopia = NULL;

  if(inicio != NULL){
    inicioCopia = novo(inicio->item);
    inicio = inicio->prox;

    while(inicio != NULL){
      insere_final(&inicioCopia, novo(inicio->item));
      inicio = inicio->prox;
    }
  }
  return inicioCopia;
}

// 15. Inverte a lista.
void inverte(no *inicio) {
  no inv = NULL, x = *inicio;

  while (*inicio != NULL) {
    x = *inicio;
    *inicio = (*inicio)->prox;
    x->prox = inv;
    inv = x;
  }

  *inicio = x;
}

// 16. Função recursiva para inverter uma lista.
//     (EXERCÍCIO: entender o que a função faz.)
void inverteR(no *head, no *tail) {
  if (*head == *tail) return;
  inverteR(&((*head)->prox), tail);
  (*tail)->prox = *head;
  *tail = *head;
  *head = (*head)->prox;
  (*tail)->prox = NULL;
}

// 17. (EXERCÍCIO) Função recursiva para inverter uma lista
//     Agora só com o ponteiro para (o ponteiro para) o
//     primeiro nó sendo passado como parâmetro.
void inverteR2(no *head);

/****************************************************/
/****************************************************/
/****************************************************/

void imprimir_teste(char * nome){
  printf("Testa %s\n", nome);
}

void testa_inverteR() {
  no head = NULL, tail;

  for (int i = 0; i < 10; i ++) {
    insere_inicio(&head, novo(i));
    if (i == 0)
      tail = head;
  }

  imprime(head);
  inverteR(&head, &tail);
  imprime(head);
}

void testa_final(){
  no inicio = NULL;

  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }

  imprime(inicio);
  printf("%d\n", final(inicio)->item);

}

void testa_insere_final(){
  no inicio = NULL;

  printf("teste 1:\ninsere -1 em NULL:\n");
  no x1 = novo(-1);
  insere_final(&inicio, x1);
  imprime(inicio);

  printf("teste 2:\n");
  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }
  imprime(inicio);
  printf("insere -2\n");
  no x2 = novo(-2);
  insere_final(&inicio, x2);
  imprime(inicio);
}

void testa_insere_finalR(){
  no inicio = NULL;

  printf("teste 1:\ninsere -1 em NULL:\n");
  no x1 = novo(-1);
  insere_finalR(&inicio, x1);
  imprime(inicio);

  printf("teste 2:\n");
  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }
  imprime(inicio);
  printf("insere -2\n");
  no x2 = novo(-2);
  insere_finalR(&inicio, x2);
  imprime(inicio);
}

void testa_remove_um(){
  no inicio = NULL;
  printf("remove null\n");
  remove_um(&inicio, 3);

  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }
  imprime(inicio);

  printf("remove 2 no meio\n");
  remove_um(&inicio, 2);
  imprime(inicio);

  printf("remove 9 no inicio\n");
  remove_um(&inicio, 9);
  imprime(inicio);

  printf("remove 0 no final\n");
  remove_um(&inicio, 0);
  imprime(inicio);

  printf("nao remove 10\n");
  remove_um(&inicio, 10);
  imprime(inicio);
}

void testa_remove_um_v1(){
  no inicio = NULL;
  printf("remove null\n");
  remove_um_v1(&inicio, 3);

  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }
  imprime(inicio);

  printf("remove 2 no meio\n");
  remove_um_v1(&inicio, 2);
  imprime(inicio);

  printf("remove 9 no inicio\n");
  remove_um_v1(&inicio, 9);
  imprime(inicio);

  printf("remove 0 no final\n");
  remove_um_v1(&inicio, 0);
  imprime(inicio);

  printf("nao remove 10\n");
  remove_um_v1(&inicio, 10);
  imprime(inicio);
}

void testa_remove_todos(){
  no inicio = NULL;
  printf("remove null\n");
  remove_todos(&inicio, 3);

  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }
  insere_inicio(&inicio, novo(9));
  for (int i = 0; i < 5; i++) {
    insere_inicio(&inicio, novo(i));
  }
  imprime(inicio);

  printf("remove 2\n");
  remove_todos(&inicio, 2);
  imprime(inicio);

  printf("remove 9\n");
  remove_todos(&inicio, 9);
  imprime(inicio);

  printf("remove 0\n");
  remove_todos(&inicio, 0);
  imprime(inicio);

  printf("nao remove 10\n");
  remove_todos(&inicio, 10);
  imprime(inicio);
}

void testa_remove_todosR(){
  no inicio = NULL;
  printf("remove null\n");
  remove_todosR(&inicio, 3);

  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }
  insere_inicio(&inicio, novo(9));
  for (int i = 0; i < 5; i++) {
    insere_inicio(&inicio, novo(i));
  }
  imprime(inicio);

  printf("remove 2\n");
  remove_todosR(&inicio, 2);
  imprime(inicio);

  printf("remove 9\n");
  remove_todosR(&inicio, 9);
  imprime(inicio);

  printf("remove 0\n");
  remove_todosR(&inicio, 0);
  imprime(inicio);

  printf("nao remove 10\n");
  remove_todosR(&inicio, 10);
  imprime(inicio);
}

void testa_copia(){
  no inicio = NULL;

  printf("lista original NULL:\n");
  imprime(inicio);

  printf("copia NULL:\n");
  no cop1 = copia(inicio);
  imprime(cop1);

  printf("lista original:\n");
  for (int i = 0; i < 10; i++) {
    insere_inicio(&inicio, novo(i));
  }
  imprime(inicio);

  printf("copia:\n");
  no cop2 = copia(inicio);
  imprime(cop2);
}

int main() {
  imprimir_teste("inverteR");
  testa_inverteR();
  printf("\n");

  imprimir_teste("final");
  testa_final();
  printf("\n");

  imprimir_teste("insere_final");
  testa_insere_final();
  printf("\n");

  imprimir_teste("insere_finalR");
  testa_insere_finalR();
  printf("\n");

  imprimir_teste("remove_um");
  testa_remove_um();
  printf("\n");

  imprimir_teste("remove_um_v1");
  testa_remove_um_v1();
  printf("\n");

  imprimir_teste("remove_todos");
  testa_remove_todos();
  printf("\n");

  imprimir_teste("remove_todosR");
  testa_remove_todosR();
  printf("\n");

  imprimir_teste("copia");
  testa_copia();
  printf("\n");

  return 0;
}
