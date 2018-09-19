#ifndef COLA_H
#define COLA_H

//Interfaz del TAD abin

////////////////////////////////////////////////////////////////////
//Tipo de dato abstracto para cola y elemento de celda
////////////////////////////////////////////////////////////////////

//contenido de cada nodo de la cola
//es una cola de árboles binarios
typedef abin tipoelemCola;
//definición del tipo opaco
typedef void *cola;

//Funciones de creación/destrucción
//Funciones de creación y destrucción
/**
 * Crea la cola vacia. 
 * @param C Puntero a la cola. Debe estar inicializada.
 */
void crearCola(cola *C);

/**
 * Destruye la cola
 * @param C puntero a la cola que queremos destruir
 */
void destruirCola(cola *C);

//Funciones de información
/**
 * Comprueba si la cola esta vacia
 * @param C cola
 */
unsigned esVaciaCola(cola C);

/*
 * Recupera la informacion del primer elemento de la cola
 * @param C cola
 * 
*/
tipoelemCola primero(cola C);

//Funciones de inserción/eliminación
/**
 * Inserta un nuevo nodo en la cola para el elemento E
 * al final de la cola
 * @param C puntero a la cola
 * @param E Informacion del nuevo nodo. 
 */
void insertarCola(cola *C, tipoelemCola E);

/**
 * Suprime el primer elemento de la cola
 * @param C puntero a la cola
 */
void suprimirCola(cola *C);

#endif	// COLA_H