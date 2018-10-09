#include <stdio.h>
#include <stdlib.h>

typedef char tipoelem; //Repetimos la definición de tipoelem

struct celda {
    tipoelem info;
    struct celda *izq, *der;
};
typedef struct celda *abin;



void crear(abin *A) {
    *A = NULL;
}

unsigned esVacio(abin A) {
    return (A == NULL);
}

//Tengo que poner el prototipo de las funciones por ser funciones
//recursivas o funciones que se usan antes de escribirlas.
void supizq(abin *A);
void supder(abin *A);
void destruir(abin *A) {
    abin aux;
    aux = *A;
    if (!esVacio(aux)) {
        supizq(&aux);
        supder(&aux);
        free(aux);
        *A = NULL;
    }
}

abin izq(abin A) {
    return A->izq;
}

abin der(abin A) {
    return A->der;
}

void info(abin A, tipoelem *E) {
    *E = A->info;
}

void modificar(abin *A, tipoelem E) {
    (*A)->info = E;
}

void insizq(abin *A, tipoelem E) {
    abin aux;
    aux = (abin) malloc(sizeof (struct celda));
    aux->info = E;
    aux->izq = NULL;
    aux->der = NULL;

    if (esVacio(*A))
        *A = aux;
    else
        (*A)->izq = aux;
}

void insder(abin *A, tipoelem E) {
    abin aux;
    aux = (abin) malloc(sizeof (struct celda));
    aux->info = E;
    aux->izq = NULL;
    aux->der = NULL;
    if (esVacio(*A))
        *A = aux;
    else
        (*A)->der = aux;
}

void supizq(abin *A) {
    abin aux;
    aux = izq(*A);

    if (!esVacio(aux)) {
        supizq(&aux);
        supder(&aux);
        (*A)->izq = NULL;
        free(aux);
    }
}

void supder(abin *A) {
    abin aux;
    aux = der(*A);
    if (!esVacio(aux)) {
        supizq(&aux);
        supder(&aux);
        (*A)->der = NULL;
        free(aux);
    }
}

//NUEVAS FUNCIONALIDADES PARA INSERTAR UN SUBÁRBOL a la izquierda o a la derecha
//NECESARIAS PARA CREAR LOS ÁRBOLES DE EXPRESIÓN

void insArbolizq(abin *A, abin aux) {
    if (esVacio(*A))
        *A = aux;
    else
        (*A)->izq = aux;
}

void insArbolder(abin *A, abin aux) {
    if (esVacio(*A))
        *A = aux;
    else
        (*A)->der = aux;
}

