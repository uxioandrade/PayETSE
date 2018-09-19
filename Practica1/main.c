/* Practica 1: Prueba de manejo de Arboles Binarios  */
#include <stdlib.h>
#include <stdio.h>

#include "abin.h"
#include "recorridos.h"
#include "funcionesArboles.h"

int main(int argc, char** argv) {

    abin Arbol, aux;
    char infoNodo;
    
    //Creo el Arbol
    crear(&Arbol);
    printf("Árbol creado\n");
   
    // El primero sera la raiz
    insizq(&Arbol, 'R');
    
    //Insertamos el nodo con valor T a la derecha del nodo raíz
    insder(&Arbol, 'T');

    //Insertamos el nodo con valor S a la izquierda de T.
    //Para eso tendremos que movernos a la derecha de la raíz
    aux = der(Arbol);
    insizq(&aux, 'S');
    //Insertamos el nodo con valor V a la derecha
    insder(&aux, 'V');
    //Nos movemos a la derecha del nodo T
    aux = der(aux);
    //Insertamos un nodo a la izquierda de V
    insizq(&aux, 'U');
    //Nos movemos a la raíz
    //Insertamos a la izquierda P
    insizq(&Arbol,'P');
    //Nos movemos al nodo P;
    aux = izq(Arbol);
    //Insertamos a la izquierda de P una M y a la derecha Q
    insizq(&aux, 'M');
    insder(&aux, 'Q');
    //Nos movemos a la izquierda de P
    aux = izq(aux);
    //Insertamos A a la izquierda y O a la derecha
    insizq(&aux, 'A');
    insder(&aux, 'O');
    //Imprimimos la altura del árbol final
    printf("Altura de arbol: %d\n", AlturaArbol(Arbol));

    printf("\nRecorrido en anchura (usa colas): "); anchura(Arbol);

    /*Método ad-hoc borrar subárbol izquierdo del nodo P
     aux = izq(Arbol);
     supizq(&aux);
    */
     
    //Borramos el subárbol izquierdo del nodo P
    //Nos colocamos en el nodo P mediante la función buscar
    printf("\nIntroduzca el contenido del nodo a buscar\n");
    scanf(" %c",&infoNodo);
    crear(&aux);
    buscar(Arbol,infoNodo, &aux);
    supizq(&aux);
    //Imprimimos el nuevo árbol en postorden
    printf("\nRecorrido PostOrden (IDR):"); postorden(Arbol);
    //Imprimimos la nueva altura
    printf("\nAltura de arbol: %d", AlturaArbol(Arbol));
    
    //Por último, imprimimos el número de nodos del árbol
    printf("\nNumero de nodos: %d\n", NumeroNodos(Arbol));
    

    // Liberamos memoria asociada al arbol:
    destruir(&Arbol);
    

    return (EXIT_SUCCESS);
}
