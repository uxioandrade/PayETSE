#ifndef ABIN_H
#define ABIN_H

//Interfaz del TAD abin

////////////////////////////////////////////////////////////////////
//Tipo de dato abstracto para arbol binario y elemento de celda
////////////////////////////////////////////////////////////////////

//TIPO OPACO, no sabemos como esta construido  
//https://es.wikipedia.org/wiki/Puntero_opaco
//Dos opciones:
//Opción a:
//      -Importar abin.h en abin.c: #include abin.h
//      -Esto evita repetir la sentencia typedef int tipoelem; 
//       en abin.c (sólo se pondría en abin.h)
//      -También evita definir en abin.c el tipo opaco como un puntero a celda: 
//       typedef struct celda *abin; (sólo se pondría en abin.h)
//Opción b: (es la que usaremos en esta ocasión)
//      -Podemos lograr mas opacidad usando en abin.h:
//       typedef void *abin;
//      -Y teniendo en abin.c la definicion typedef struct celda *abin;
//      -Pero tenemos que repetir la sentencia typedef int tipoelem; 
//       en ambos ficheros (abin.h y abin.c)
// Tenemos que decidir que preferimos: mayor opacidad (opcion b) o menos
// codigo repetido (opcion a).

//En este caso hemos optado por lo primero (opcion b), por lo que:
//-Debemos repetir la definición de tipoelem en ambos ficheros (abin.h y abin.c)
//-Definimos abin como un tipo totalmente opaco en abin.h
//-Definimos abin como un puntero a struct celda en abin.c

//contenido de cada nodo del árbol
//es un árbol de números enteros
typedef char tipoelem;
//definición del tipo opaco
typedef void *abin; 

/////////////////////////////// FUNCIONES
/*
 * Crea el arbol vacio. 
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crear(abin *A);

/*
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruir(abin *A);

/**
 * Comprueba si el arbol esta vacio
 * @param A El arbol binario
 */
unsigned esVacio(abin A);

/**
 * Devuelve el subarbol izquierdo de A
 * @param A - Arbol original
 */
abin izq(abin A);

/**
 * Devuelve el subarbol derecho de A
 * @param A - Arbol original
 */
abin der(abin A);

/**
 * Recupera la informacion de la celda de la raiz del arbol
 * @param A Arbol Binario
 * @param E Puntero al nodo que apuntara a la informacion
 */
void info(abin A, tipoelem *E);

/**
 * Inserta un nuevo nodo en el arbol para el elemento E
 * a la izquierda de A
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo. 
 */
void insizq(abin *A, tipoelem E);

/**
 * Inserta un nuevo nodo en el arbol para el elemento E
 * a la derecha de A
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo. 
 */
void insder(abin *A, tipoelem E);

/**
 * Suprime el subárbol a la izquierda de A
 * @param A Arbol binario
 */
void supizq(abin *A);

/**
 * Suprime el subárbol a la derecha de A
 * @param A Arbol binario
 */
void supder(abin *A);

/**
 * Modifica el contenido del nodo apuntado por A con el valor de E
 * @param A Arbol binario
 * @param E Información a modificar
 */
void modificar(abin *A, tipoelem E);

#endif	// ABIN_H
