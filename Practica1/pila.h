#ifndef PILA_H
#define PILA_H

//Interfaz TAD pila

typedef void *pila; /*tipo opaco*/

//contenido de cada elemento de la pila: pila de árboles binarios
typedef abin tipoelemPila;

//Funciones de creación y destrucción
/**
 * Crea la pila vacia. 
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPila(pila *P);

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPila(pila *P);

//Funciones de información
/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPila(pila P);

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 * 
*/
tipoelemPila tope(pila P);

//Funciones de inserción/eliminación
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * en el tope de la pila
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo. 
 */
void push(pila *P, tipoelemPila E);

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void pop(pila *P);

#endif	// PILA_H

