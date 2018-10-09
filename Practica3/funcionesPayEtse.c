//
//  funcionesPayEtse.c
//  PayETSE
//
//  Created by Uxío García Andrade on 3/10/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#include "funcionesPayEtse.h"
#include "abb.h"
#include <string.h>
#include <stdio.h>

///////////////FUNCIONES PRIVADAS


//Inicializa todos los campos de un usuario a unos valores por defecto e inserta el usuario en el árbol
void _inicializar_campos(abb *A,tipoclave nome){
    
    tipoelem e;
    
    strcpy(e.nomeUsuario,nome);
    e.cantidade = 0;
    strcpy(e.concepto,"");
    strcpy(e.receptor,"");
    insertar(A, e);
}

//Imprime todos los campos de una transferencia
void _imprimir_transferencia(tipoelem usr){
    
    printf("Usuario:\t %s \n",usr.nomeUsuario);
    printf("Última transferencia:\n");
    if(usr.cantidade != 0){ //Se imprimen los datos de la transferencia, en el caso de que se haya realizado alguna
        printf("Receptor:\t %s \n",usr.receptor);
        printf("Cantidade:\t %lf \n",usr.cantidade);
        printf("Concepto:\t %s \n\n",usr.concepto);
    }else
        printf("Este usuario non realizou ningunha transferencia\n\n");
    
}

//Imprime el árbol mediante el recorrido inorden
void _inorden(abb A){
    tipoelem E;
    
    if(!es_vacio(A)){
        info(A, &E);
        _inorden(izq(A));
        _imprimir_transferencia(E);
        _inorden(der(A));
    }
}

//Función recursiva que comprueba todos los nodos del árbol e imprime todos aquellos en los que encuentra la clave cl como receptor
void _buscar_receptor(abb A,char* cl,int *flag){
    tipoelem usr;
    
    if(!es_vacio(A)){
        info(A, &usr);
        if(!strcmp(cl, usr.receptor)){
            _imprimir_transferencia(usr);
            (*flag)++;                      //Se incluye una flag para poder comprobar si un usuario ha recibido alguna transferencia
        }
        _buscar_receptor(izq(A), cl,flag);
        _buscar_receptor(der(A), cl,flag);
    }
}

//Función recursiva que reinicia los valores de los nodos en los que se encuentra la clave como receptor
void _borrar_referencia(abb A,char* cl){
//Aunque por convención se debería pasar el argumento A como *A, eso forzaría a crear un árbol auxiliar
//por lo que, en este caso el código queda más optimizado no respetando esa convencioón
    
    tipoelem usr;
    
    if(!es_vacio(A)){
        info(A, &usr);
        if(!strcmp(cl, usr.receptor)){
            //Se resetean las referencias al receptor a los valores por defecto
            strcpy(usr.receptor,"");
            usr.cantidade = 0;
            strcpy(usr.concepto, "");
            modificar(&A, usr);
        }
        //Se procede a invocar la función de manera recursiva, similar al recorrido inorden
        _borrar_referencia(izq(A), cl);
        _borrar_referencia(der(A), cl);
    }
}
/////////////////////FIN FUNCIONES PRIVADAS


////////////////////FUNCIONES PÚBLICAS


//Permite introducir una transferencia a partir de los datos proporcionados por el usuario
void introducirTransferencia(abb *A){
    
    tipoelem emisor;
    
    printf("Introduza o nome do usuario emisor\n");
    scanf(" %[^\r\n]", emisor.nomeUsuario);
    
    printf("Introduza o nome do usuario receptor\n");
    scanf(" %[^\r\n]", emisor.receptor);
          
    printf("Introduza o concepto da transferencia\n");
    scanf(" %[^\r\n]", emisor.concepto);
    
    printf("Introduza a cantidade a transferir\n");
    scanf(" %lf", &(emisor.cantidade));
    
    //Si el usuario emisor es miembro, simplemente se modifican los datos del nodo que contiene a ese usuario
    if(es_miembro(*A, emisor)){
        modificar(A, emisor);
    }else{
        //Si no es miembro, se inserta en un nuevo nodo del árbol
        insertar(A, emisor);
    }
    
    if(!es_miembro_clave(*A, emisor.receptor)){
        //Si el usuario receptor no es miembro, se inicializan sus campos a unos valores por defecto y se inserta en el árbol
        _inicializar_campos(A, emisor.receptor);
    }//No hace falta incluir el caso en el que si sea miembro porque en ese caso no es necesario realizar ninguna operación
    
    //Finalmente, se realiza el recorrido inorden del árbol para imprimir todas las transferencias
    _inorden(*A);
}

//Permite buscar si el usuario está presente en el árbol e imprime su última transferencia
void consultaUsuario(abb A){
    
    tipoelem usr;
    
    printf("Introduza o nome do usuario a buscar\n");
    scanf(" %[^\r\n]",usr.nomeUsuario);
          
    if(es_miembro_clave(A, usr.nomeUsuario)){
        //Se busca el nodo en el que está el usuario y se obtiene su valor
        buscar_nodo(A, usr.nomeUsuario, &usr);
        _imprimir_transferencia(usr);
    }else
        printf("O usuario consultado non existe\n");
}

//Permite buscar si el usuario está en el árbol e imprime las transferencias que ha recibido
void consultaReceptor(abb A){
    
    char receptor[lonxitude] = "";
    int aux = 0;
    
    printf("Introduza o nome do receptor a buscar\n");
    scanf(" %s",receptor);
    
    if(es_miembro_clave(A, receptor)){
        _buscar_receptor(A, receptor,&aux);
        //Se imprime el número de transferencias que ha recibido, también para prevenir el caso de que no se muestre nada si no ha recibido ninguna
        printf("O usuario recibiu %d transferencias\n",aux);
    }else
        printf("O usuario introducido non existe\n");
    
}

//Permite eliminar el usuario del árbol, eliminando también sus referencias
void eliminarUsuario(abb *A){
    
    tipoelem usr;
    
    printf("Introduza o nome do usuario a borrar\n");
    scanf(" %[^\r\n]",usr.nomeUsuario);
    
    if(es_miembro_clave(*A, usr.nomeUsuario)){
        //En primer lugar, se busca el usuario en el árbol
        buscar_nodo(*A, usr.nomeUsuario, &usr);
        //Se reinicializan las posibles referencias al usuario
        _borrar_referencia(*A, usr.nomeUsuario);
        //Finalmente se suprime del árbol
        suprimir(A, usr);
    }else
        printf("O usuario introducido non existe\n");
}

//Realiza el recorrido inorden del árbol y lo destruye
void sairPrograma(abb *A){
    _inorden(*A);
    destruir_arbol(A);
    printf("Tenha un bo día \n");
}

