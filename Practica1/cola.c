#include <stdlib.h>
#include <stdio.h>
#include "abin.h"


/////////////////////REPETIMOS LA DEFINICIÓN DE LOS TIPOS DE DATOS
//cola es un puntero a struct cabeceraCola
typedef struct cabeceraCola * cola;

//contenido de cada nodo del árbol
//es un árbol de números enteros
typedef abin tipoelemCola;

//celda que contiene los elementos de la cola
struct celdaCola{
    tipoelemCola elemento;
    struct celdaCola * sig;
};
typedef struct celdaCola * puntero;
/////////////////////ESTRUCTURAS DE DATOS
//celda cabecera que contiene la información del frente y del final de la cola
struct cabeceraCola{
	puntero frente;
	puntero final;
};


///////////////////////FUNCIONES

//Crea la cola vacía, con la cabecera de la cola y punteros nulos a frente y final
void crearCola(cola *C)
{
    *C=(cola)malloc(sizeof(struct cabeceraCola));
    if (C == NULL)
      printf("Error: Memoria insuficiente\n");
    else{
        (*C)->frente=(puntero)malloc(sizeof(struct celdaCola));
        if ((*C)->frente == NULL)
             printf("Error: Memoria insuficiente\n");
        else{
            (*C)->final=(*C)->frente;
            (*C)->frente->sig=NULL;
        }
    }
}

//Destruye la cola, recorriendo sus elementos
void destruirCola(cola *C) {
    puntero p, r;
    p = (*C)->frente;
    while (p != NULL) {
        r = p;
        p = p->sig;
        free(r);
    }
    free(*C);
}

//Informa si la cola está vacía
unsigned esVaciaCola(cola C)
{
    return (C->frente==C->final);
}

//Devuelve el elemento el elemento en el frente de la cola
tipoelemCola primero(cola C)
{
    if (!esVaciaCola(C))
	return (C->frente)->sig->elemento;
    else{
        printf("Error: cola vacía\n");
        return 0;
    }
}

//Inserta un elemento al final de la cola
void insertarCola(cola *C, tipoelemCola E)
{
    ((*C)->final)->sig=(puntero)malloc(sizeof(struct celdaCola));
    if ((*C)->final->sig == NULL)
        printf("Error: Memoria insuficiente\n");
    else{
        (*C)->final=((*C)->final)->sig;
        ((*C)->final)->elemento=E;
        ((*C)->final)->sig=NULL;
    }
}

//Suprime el primer elemento de la cola
void suprimirCola(cola *C)
{
    puntero p;
    if (esVaciaCola(*C))
        printf("Error: Cola vacia\n");
    else{
        p=(*C)->frente;
	(*C)->frente=(*C)->frente->sig;
	free(p);
    }
}
