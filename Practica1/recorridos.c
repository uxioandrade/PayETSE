#include <stdio.h>
#include <stdlib.h>

#include "abin.h"
#include "pila.h"
#include "cola.h"

//RECORRIDOS SUPONIENDO QUE ES UN ÁRBOL DE NÚMEROS ENTEROS
//revisar los printf si se cambia el contenido de cada nodo

//Recorrido recursivo inorden: I-R-D
void inorden(abin A) {
    tipoelem E;
    if (!esVacio(A)) {
        inorden(izq(A));
        info(A, &E);
        printf("%c\t", E);
        inorden(der(A));
    }
}

//Recorrido recursivo preorden: R-I-D
void preorden(abin A) {
    tipoelem E;
    if (!esVacio(A)) {
        info(A, &E);
        printf("%c\t", E);
        preorden(izq(A));
        preorden(der(A));
    }
}

//Recorrido recursivo postorden: I-D-R
void postorden(abin A) {
    tipoelem E;
    if (!esVacio(A)) {
        postorden(izq(A));
        postorden(der(A));
        info(A, &E);
        printf("%c\t", E);
    }
}

//Recorrido no recursivo inorden utilizando pilas como estructura auxiliar
void inordenNR(abin A) {
    tipoelem E;
    abin aux;
    pila p;
    aux = A;
    crearPila(&p);
    do {
        while (!esVacio(aux)) { //se meten en la pila todos los punteros izquierdos
            info(aux, &E);
            push(&p, aux);
            aux = izq(aux);
        }
        if (!esVaciaPila(p)) {
            aux = tope(p);
            pop(&p);
            info(aux, &E);
            printf("%c\t", E);
            aux = der(aux); //se sigue por la derecha del tope de la pila
        }
    } while (!esVaciaPila(p) || !esVacio(aux));
    destruirPila(&p);
}

//Recorrido no recursivo en anchura utilizando colas como estructura auxiliar
void anchura(abin A) {
    tipoelem E;
    abin aux;
    cola c;
    crearCola(&c);
    if (!esVacio(A)) //Insertamos nodo raiz, primer nivel
        insertarCola(&c, A);
    while (!esVaciaCola(c)) {
        aux = primero(c); //Se extrae un elemento de la cola
        suprimirCola(&c);
        info(aux, &E);
        printf("%c\t", E);
        if (!esVacio(izq(aux)))
            insertarCola(&c, izq(aux));
        if (!esVacio(der(aux)))
            insertarCola(&c, der(aux));
    }
    destruirCola(&c);
}
