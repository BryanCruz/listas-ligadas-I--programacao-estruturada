#ifndef LISTA
#define LISTA

typedef struct s_no *   no;

struct s_no {
  int item;
  no  prox;
};

  no novo            (int item);
void deleta          (no x);
void insere_inicio   (no *inicio,    no x);
void remove_inicio   (no *inicio);
void imprime         (no inicio);
  no busca           (no inicio,     int item);
  no buscaR          (no inicio,     int item);
  no final           (no inicio);
void insere_final    (no *inicio,    no x);
void insere_finalR   (no *inicio,    no x);
void remove_um       (no *inicio,    int item);
void remove_todos    (no *inicio,    int item);
void remove_todosR   (no *inicio,    int item);
  no copia           (no inicio);
void inverte         (no *inicio);
void inverteR        (no *head,      no *tail);
void inverteR2       (no *head);

no livres = NULL;

#endif
