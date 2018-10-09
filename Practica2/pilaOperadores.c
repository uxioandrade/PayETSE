//
//  pilaOperadores.c
//  EntregaSesion2
//
//  Created by Uxío García Andrade on 26/9/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#include <stdlib.h>

//ImplementaciÛn TAD pila

//CONTENIDO DE CADA ELEMENTO DE LA PILA
typedef char tipoelemOperadores;
///////////////////////////////////////////////////////

//DefiniciÛn del tipo de datos pila
struct tipo_celda {
    tipoelemOperadores elemento;
    struct tipo_celda * sig;
};

typedef struct tipo_celda * pilaOperadores;
/////////////////////////////////////////////////////////

void crearPilaOperadores(pilaOperadores *P) {
    *P = NULL;
}

void destruirPilaOperadores(pilaOperadores *P) {
    pilaOperadores aux;
    aux = *P;
    while (aux != NULL) {
        aux = aux->sig;
        free(*P);
        *P = aux;
    }
}

unsigned esVaciaPilaOperadores(pilaOperadores P) {
    return P == NULL;
}

tipoelemOperadores topeOperadores(pilaOperadores P) {
    if (!esVaciaPilaOperadores(P)) /*si pila no vacia*/
        return P->elemento;
    else
        return 0;
}

void pushOperadores(pilaOperadores *P, tipoelemOperadores E) {
    pilaOperadores aux;
    aux = (pilaOperadores) malloc(sizeof (struct tipo_celda));
    aux->elemento = E;
    aux->sig = *P;
    *P = aux;
}

void popOperadores(pilaOperadores *P) {
    pilaOperadores aux;
    if (!esVaciaPilaOperadores(*P)) /*si pila no vacia*/ {
        aux = *P;
        *P = (*P)->sig;
        free(aux);
    }
}
