//
//  pilaOperandos.h
//  EntregaSesion2
//
//  Created by Uxío García Andrade on 26/9/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#ifndef pilaOperandos_h
#define pilaOperandos_h

#include <stdio.h>
#include "abin.h"

//Interfaz TAD pila
typedef void *pilaOperandos; /*tipo opaco*/

//CONTENIDO DE CADA ELEMENTO DE LA PILA
typedef abin tipoelemOperandos;

//Funciones de creaciÛn y destrucciÛn
/**
 * Crea la pila vacia.
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPilaOperandos(pilaOperandos *P);

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPilaOperandos(pilaOperandos *P);

//Funciones de informaciÛn
/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPilaOperandos(pilaOperandos P);

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 *
 */
tipoelemOperandos topeOperandos(pilaOperandos P);

//Funciones de inserciÛn/eliminaciÛn
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * en el tope de la pila
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo.
 */
void pushOperandos(pilaOperandos *P, tipoelemOperandos E);

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void popOperandos(pilaOperandos *P);

#endif /* pilaOperandos_h */
