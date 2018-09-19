#include <stdio.h>
#include <stdlib.h>


/////////////////////REPETIMOS LA DEFINICIÓN DE LOS TIPOS DE DATOS
//abin es un puntero a struct celda
typedef struct celda *abin;
//contenido de cada nodo del árbol
//es un árbol de números enteros
typedef char tipoelem; 

/////////////////////ESTRUCTURAS DE DATOS
struct celda{
	tipoelem info;
	struct celda *izq, *der;
};

///////////////////////FUNCIONES

//Crea el árbol vacío
void crear(abin *A){
	*A=NULL;
}

//Destruye el árbol recursivamente
//Al elegir la opción b) de implementación, necesito los prototipos
//para poder llamar a estas funciones (con la opción a)#include abb.h, ya estarían
//definidos estos prototipos)
void supizq(abin *A);
void supder(abin *A);
unsigned esVacio(abin A);
void destruir(abin *A){
	abin aux;
	aux=*A;
	if(!esVacio(aux)){
	  supizq(&aux);
	  supder(&aux);
	  free(aux);
	  *A=NULL;
	}	
}

//Comprueba si el árbol está vacío
unsigned esVacio(abin A){
	return (A==NULL);
}

//Devuelve el subárbol izquierdo de A
abin izq(abin A){
	return A->izq;
}

//Devuelve el subárbol derecho de A
abin der(abin A){
	return A->der;
}

//Recupera la informacion de la celda de la raiz del arbol
void info(abin A, tipoelem *E){
	*E=A->info;
}

//Inserta un nuevo nodo en el arbol para el elemento E a la derecha de A
void insizq(abin *A, tipoelem E){
	abin aux;
	aux=(abin)malloc(sizeof(struct celda));
	aux->info=E;
	aux->izq=NULL;
	aux->der=NULL;	

	if(esVacio(*A))
	  *A=aux; 	
	else
	  (*A)->izq=aux;	
}

//Inserta un nuevo nodo en el arbol para el elemento E a la izquierda de A
void insder(abin *A, tipoelem E){
	abin aux;
	aux=(abin)malloc(sizeof(struct celda));
	aux->info=E;
	aux->izq=NULL;
	aux->der=NULL;	
	if(esVacio(*A))
	  *A=aux;
	else
	  (*A)->der=aux;	
}

//Suprime el subárbol a la izquierda de A
void supizq(abin *A){
	abin aux;
	aux=izq(*A);
	if(!esVacio(aux)){
	  supizq(&aux);
	  supder(&aux);	
	  (*A)->izq=NULL;
	  free(aux);
	}	
}

//Suprime el subárbol a la derecha de A
void supder(abin *A){
	abin aux;
	aux=der(*A);
	if(!esVacio(aux)){
	  supizq(&aux);
	  supder(&aux);	
	  (*A)->der=NULL;
	  free(aux);
	}	
}

//Modifica el contenido del nodo apuntado por A con el valor de E
void modificar(abin *A, tipoelem E){
	(*A)->info=E;
}
