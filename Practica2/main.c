//
//  main.c
//  EntregaSesion2
//
//  Created by Uxío García Andrade on 26/9/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "abin.h"
#include "FuncionesExpresion.h"
#include "recorridos.h"

int main(int argc, const char * argv[]) {
    
    //Podríamos emplear prácticas de memoria dinámica para evitar malgastar memoria, pero al no ser le objetivo de la práctica y no emplear
    //demasiada memoria en este ejercicio, podemos omitir ese paso y recurrir a una política más cómoda
    char expr[100] = "";
    abin arb;
    crear(&arb); //Crea el árbol
   
    //Pide la expresión a evaluar
    printf("Introduza a expresión infixa\n");
    scanf(" %s",expr);
    
    //Construye el árbol de expresión
    arb = arbolExpresion(expr);
    
    //Imprime la expresión en inorden
    printf("\nA expresión prefixa correspondente é:\n");
    preorden(arb);
    
    //Impirme la expresión en postorden
    printf("\nA expresión postfixa correspondente é:\n");
    postorden(arb);
    
    printf("\n");
    
    //Destruye el árbol
    destruir(&arb);
    
    return 0;
}
