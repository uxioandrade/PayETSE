//
//  pilaOperadores.h
//  EntregaSesion2
//
//  Created by Uxío García Andrade on 26/9/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#ifndef pilaOperadores_h
#define pilaOperadores_h

#include <stdio.h>


//Interfaz TAD pila
typedef void *pilaOperadores; /*tipo opaco*/

//CONTENIDO DE CADA ELEMENTO DE LA PILA
typedef char tipoelemOperadores;

//Funciones de creaciÛn y destrucciÛn
/**
 * Crea la pila vacia.
 * @param P Puntero a la pila. Debe estar inicializada.
 */
void crearPilaOperadores(pilaOperadores *P);

/**
 * Destruye la pila
 * @param P puntero a la pila
 */
void destruirPilaOperadores(pilaOperadores *P);

//Funciones de informaciÛn
/**
 * Comprueba si la pila esta vacia
 * @param P pila
 */
unsigned esVaciaPilaOperadores(pilaOperadores P);

/*
 * Recupera la informacion del tope de la pila
 * @param P pila
 *
 */
tipoelemOperadores topeOperadores(pilaOperadores P);

//Funciones de inserciÛn/eliminaciÛn
/**
 * Inserta un nuevo nodo en la pila para el elemento E
 * en el tope de la pila
 * @param P puntero a la pila
 * @param E Informacion del nuevo nodo.
 */
void pushOperadores(pilaOperadores *P, tipoelemOperadores E);

/**
 * Suprime el elemento en el tope de la pila
 * @param P puntero a la pila
 */
void popOperadores(pilaOperadores *P);


#endif /* pilaOperadores_h */
