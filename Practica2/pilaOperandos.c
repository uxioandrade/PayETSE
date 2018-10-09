//
//  pilaOperandos.c
//  EntregaSesion2
//
//  Created by Uxío García Andrade on 26/9/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#include "abin.h"
#include <stdlib.h>

//ImplementaciÛn TAD pila

//CONTENIDO DE CADA ELEMENTO DE LA PILA
typedef abin tipoelemOperandos;
///////////////////////////////////////////////////////

//DefiniciÛn del tipo de datos pila
struct tipo_celda {
    tipoelemOperandos elemento;
    struct tipo_celda * sig;
};

typedef struct tipo_celda * pilaOperandos;
/////////////////////////////////////////////////////////

void crearPilaOperandos(pilaOperandos *P) {
    *P = NULL;
}

void destruirPilaOperandos(pilaOperandos *P) {
    pilaOperandos aux;
    aux = *P;
    while (aux != NULL) {
        aux = aux->sig;
        free(*P);
        *P = aux;
    }
}

unsigned esVaciaPilaOperandos(pilaOperandos P) {
    return P == NULL;
}

tipoelemOperandos topeOperandos(pilaOperandos P) {
    if (!esVaciaPilaOperandos(P)) /*si pila no vacia*/
        return P->elemento;
    else
        return 0;
}

void pushOperandos(pilaOperandos *P, tipoelemOperandos E) {
    pilaOperandos aux;
    aux = (pilaOperandos) malloc(sizeof (struct tipo_celda));
    aux->elemento = E;
    aux->sig = *P;
    *P = aux;
}

void popOperandos(pilaOperandos *P) {
    pilaOperandos aux;
    if (!esVaciaPilaOperandos(*P)) /*si pila no vacia*/ {
        aux = *P;
        *P = (*P)->sig;
        free(aux);
    }
}
