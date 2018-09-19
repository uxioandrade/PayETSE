#ifndef RECORRIDOS_H
#define RECORRIDOS_H

//Recorrido recursivo inorden: I-R-D
// @param A Arbol binario
void inorden(abin A);

//Recorrido recursivo preorden: R-I-D
// @param A Arbol binario
void preorden(abin A);

//Recorrido recursivo postorden: I-D-R
// @param A Arbol binario
void postorden(abin A);

//Recorrido no recursivo inorden utilizando pilas como estructura auxiliar
// @param A Arbol binario
void inordenNR(abin A);

//Recorrido no recursivo en anchura utilizando colas como estructura auxiliar
// @param A Arbol binario
void anchura(abin A);

#endif /* RECORRIDOS_H */

