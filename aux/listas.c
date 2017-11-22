#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

// 1. (EXERCÍCIO) Cria um novo nó da lista.
//    Mudar a implementação da função novo
//    para alocar muitos nós de uma vez e usar a lista
//    livres para guardar os blocos que ainda não estão
//    sendo usados. Como visto em sala...
no novo(int item);

// 2. (EXERCÍCIO) Deleta um nó.
//    Adaptar a função deleta para trabalhar
//    com a lista de nós livres. Como visto em sala...
void deleta(no x);

// 3. Insere um nó no início da lista (como PUSH).
//    (Supõem que x e ini são ambos diferentes de NULL.)
//    (Mas *ini pode ser NULL.)
void insere_inicio(no *ini, no x) {
  x->prox = *ini;
  *ini = x;
}

// 4. Remove o primeiro nó da lista.
//    (Se o valor de retorno fosse o item do nó removido,
//    essa função seria como POP.)
void remove_inicio(no *ini) {
  no x = *ini;
  if (*ini != NULL) {
    *ini = x->prox;
    deleta(x);
  }
}

// 5. Imprime todos os elementos de uma lista
//    (supondo que sejam inteiros).
void imprime(no x) {
  for (; x != NULL; x = x->prox)
    printf("%d", x->item);
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

// 8. Devolve o último nó de uma lista.
no final(no x) {
  if (x == NULL)
    return NULL;

  while (x->prox != NULL)
    x = x->prox;

  return x;
};

// 9. Insere nó no final.
//    (Supõem que x e ini são ambos diferentes de NULL.)
//    (Mas *ini pode ser NULL.)
void insere_final(no *ini, no x) {
  if (*ini == NULL) {
    *ini = x;
    return;
  }

  no y = final(*ini);
  y->prox = x;
}

// 10. Insere nó no final, recursivamente.
//    (Supõem que x e ini são ambos diferentes de NULL.)
//    (Mas *ini pode ser NULL.)
void insere_finalR(no *ini, no x) {
  if (*ini == NULL)
    *ini = x;
  else
    insere_finalR(&((*ini)->prox), x);
}

// 11. Remove primeiro nó que contém item.
//    (Supõem que ini é diferente de NULL.
//    (*ini pode ser NULL.)
//    (EXERCÍCIO: entender o que a função faz.)
void remove_um(no *ini, int item) {
  if (*ini == NULL)
    return;

  no x, *prev = ini;
  for (x = (*ini); x != NULL && x->item != item;
       prev = &(x->prox), x = x->prox);

  if (x != NULL) {
    *prev = x->prox;
    deleta(x);
  }
}

// 12. (EXERCÍCIO) Remove todos os nós contendo item.
void remove_todos(no *ini, int item){
  //x é copia, *aux é referencia, aux é cópia da referencia
  no x = *ini, *aux = ini;

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
void remove_todosR(no *ini, int item){
  if(*ini != NULL){
    no x = *ini;
    remove_todosR(&(x->prox), item);

    if(x->item == item){
       *ini = x->prox;
       deleta(x);
    }
  }
}

// 14. Cria uma cópia da lista dada
//     (copiar em outras posições de memória, é claro).
no copia(no inicio) {
  if (inicio == NULL)
    return NULL;

  no x = novo(inicio->item);
  x->prox = copia(inicio->prox);
  return x;
}

// 15. Inverte a lista.
void inverte(no *ini) {
  no x = *ini;
  *ini = NULL;

  while (x != NULL) {
    no y = x->prox;
    x->prox = *ini;
    *ini = x;
    x = y;
  }
}

// 16. (EXERCÍCIO) Função recursiva para inverter uma lista
//     Agora só com o ponteiro para (o ponteiro para) o
//     primeiro nó sendo passado como parâmetro.
void inverteR2(no *ini);

/****************************************************/
/****************************************************/
/****************************************************/

/*
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
*/
