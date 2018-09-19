#ifndef FUNCIONESARBOLES_H
#define FUNCIONESARBOLES_H

//Función que calcula la altura del árbol A
// @param A Arbol binario
int AlturaArbol(abin A);

//Función que calcula el número de nodos de un árbol A
// @param A Arbol binario
int NumeroNodos(abin A);

//Función que suma los elementos de un árbol A
// @param A Arbol binario
int SumaElementos(abin A);

//Función que busca un elemento info de un árbol A y devuelve un puntero Aux a ese nodo
// @param A Árbol binario
// @param info Elemento a buscar
// @param Aux puntero a nodo
void buscar(abin A, tipoelem inf,abin *aux);

#endif /* FUNCIONESARBOLES_H */

