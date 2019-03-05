//
//  main.c
//  PayETSE
//
//  Created by Uxío García Andrade on 3/10/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include <string.h>
#include "grafo.h"
#include "funcionesPayEtse.h"

int main(int argc, const char * argv[]) {
    
    abb arbol;
    grafo grafoGlobal;
    char opt = 'a';
    
    //Crea el árbol que contendrá las transferencias
    crear_arbol(&arbol);
    //Crea el grafo
    crear_grafo(&grafoGlobal);
    //Lee los datos del archivo
    lerDatos(&arbol,&grafoGlobal);
    
    printf("---------Benvido a PayETSE---------- \n");
    
    while(opt != 'S'){
        printf("--- Seleccione unha das seguintes opcións -- \n");
        printf("--------- L) Iniciar sesión -------------\n");
        printf("--------- S) Saír do programa -----------\n$>");
        scanf(" %c",&opt);
        
        switch (opt) {
            case 'S':
                //Escribe los datos de las transferencias en otro archivo
                escribirDatos(&arbol);
                //Realiza el recorrido inorden, libera la memoria y sale del programa
                sairPrograma(&arbol,&grafoGlobal);
                break;
            default:
                logIn(&arbol,&grafoGlobal);
                break;
        }
    }
    
    return 0;
}
