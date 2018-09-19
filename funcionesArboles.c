#include <stdio.h>
#include <stdlib.h>
#include "abin.h"

/////////////////////PROTOTIPOS DE FUNCIONES PRIVADAS: no visibles para el usuario
//////ESTAS FUNCINES NO APARECEN EL EL FICHERO funcionesArboles.h

// Funcion auxiliar para calcular altura 
//Se utiliza en la función AlturaArbol()
int maxAltura(int a, int b);

//Funcion auxiliar para contar nodos
//Se utiliza en NumeroNodos()
void auxContador(abin nodo, int *c);

//Función auxiliar para sumar nodos
//Se utiliza en SumaElementos()
void auxSuma(abin A, int *suma);

//////////////////////////////////FUNCIONES PÚBLICAS
//////////////////APARECEN EN EL FICHERO funcionesArboles.h

//Función que calcula la altura del árbol A
int AlturaArbol(abin A) {
    int altura;
    if (A == NULL)
        altura = 0;
    else
        /* Función auxiliar privada */
        altura = 1 + maxAltura(AlturaArbol(izq(A)), AlturaArbol(der(A)));
    return altura;
}

//Función que calcula el número de nodos de un árbol A
int NumeroNodos(abin A) {
    int contador = 0;
    auxContador(A, &contador); /* Función auxiliar privada */
    return contador;
}

//Función que suma los elementos de un árbol A
//Esta función debe llamar a la función recursiva PRIVADA, que es la que va
//acumulando la suma
//Su propósito es inicializar el valor de la suma a 0 y devolver el resultado
//al programa
int SumaElementos(abin A){
    int suma=0;
    auxSuma(A,&suma); //suma se pasa por referencia para que las llamadas recursivas acumulen
    return suma;
}

//Función que busca un elemento del árbol
void buscar(abin A, tipoelem inf,abin *aux){
    tipoelem E;
    if (!esVacio(A)) {
        info(A, &E);
        if(E == inf){
            *aux = A;
        }
        if(esVacio(*aux)){
            printf("%c",E);
            buscar(izq(A),inf,aux);
            buscar(der(A),inf,aux);
        }
    }
}


//////////////////////////////////FUNCIONES PRIVADAS
//////////////////NO APARECEN EN EL FICHERO funcionesArboles.h

/* Función auxiliar para calcular altura */
int maxAltura(int a, int b) {
    if (a > b) return a;
    else return b;
}

/* Función auxiliar para contar nodos. Función recursiva de recorrido en
   preorden, el proceso es aumentar el contador */
void auxContador(abin nodo, int *c) {
    if (!esVacio(nodo)){
	(*c)++; /* Otro nodo */
    	/* Continuar recorrido */
    	auxContador(izq(nodo), c);
    	auxContador(der(nodo), c);
    }
}
//Función auxiliar recursiva para sumar los nodos
void auxSuma(abin A, int *suma){
    tipoelem E;
    if (!esVacio(A)){
        info(A,&E);
        *suma=*suma+E;
        auxSuma(izq(A),suma);
        auxSuma(der(A),suma);
    }
}


