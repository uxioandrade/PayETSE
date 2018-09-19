#include <stdlib.h>
#include "abin.h"
typedef abin tipoelemPila; //Repetimos la definición de tipoelemPila

struct tipo_celda {
    tipoelemPila elemento;
    struct tipo_celda * sig;
};

typedef struct tipo_celda * pila;

void crearPila(pila *P) {
    *P = NULL;
}

void destruirPila(pila *P) {
    pila aux;
    aux = *P;
    while (aux != NULL) {
        aux = aux->sig;
        free(*P);
        *P = aux;
    }
}

unsigned esVaciaPila(pila P) {
    return P == NULL;
}

tipoelemPila tope(pila P) {
    if (!esVaciaPila(P)) /*si pila no vacía*/
        return P->elemento;
    else return 0;
}

void push(pila *P, tipoelemPila E) {
    pila aux;
    aux = (pila) malloc(sizeof (struct tipo_celda));
    aux->elemento = E;
    aux->sig = *P;
    *P = aux;
}

void pop(pila *P) {
    pila aux;
    if (!esVaciaPila(*P)) /*si pila no vacía*/ {
        aux = *P;
        *P = (*P)->sig;
        free(aux);
    }
}
