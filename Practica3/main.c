//
//  main.c
//  PayETSE
//
//  Created by Uxío García Andrade on 3/10/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#include <stdio.h>
#include "abb.h"
#include "funcionesPayEtse.h"

int main(int argc, const char * argv[]) {
    
    abb arbol;
    char opt = 'a';
    
    crear_arbol(&arbol);
    
    printf("---------Benvido a PayETSE---------- \n");
    
    while(opt != 'Q'){
        printf("--- Seleccione unha das seguintes opcións --- \n");
        printf("--------- [I] Introducir transferencia -------\n");
        printf("--------- [U] Consulta por usuario -----------\n");
        printf("--------- [R] Consulta por receptor ----------\n");
        printf("--------- [E] Eliminar usuario ---------------\n");
        printf("--------- [Q] Saír do programa ---------------\n");
        scanf(" %c",&opt);
        
        switch (opt) {
            case 'I':
                introducirTransferencia(&arbol);
                break;
            case 'U':
                consultaUsuario(arbol);
                break;
            case 'R':
                consultaReceptor(arbol);
                break;
            case 'E':
                eliminarUsuario(&arbol);
                break;
            case 'Q':
                sairPrograma(&arbol);
                break;
            default:
                printf("Introduza un caracter válido\n");
                break;
        }
    }
    
    return 0;
}
