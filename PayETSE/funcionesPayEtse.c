//
//  funcionesPayEtse.c
//  PayETSE
//
//  Created by Uxío García Andrade on 3/10/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#include "funcionesPayEtse.h"
#include <stdlib.h>
#include "abb.h"
#include "pila.h"
#include <string.h>
#include <stdio.h>
#include "grafo.h"
#define ARQUIVO "./listaTransferencias.txt"

///////////////FUNCIONES PRIVADAS

//Inicializa los grafos de un usuario
void _crear_grafos_usuario(grafo *G,tipoelem *usr){
    
    tipovertice aux;
    //Crea un vértice con el nombre del usuario
    strcpy(aux.usuario, usr->nomeUsuario);
    //Crea el grafo local del usuario
    crear_grafo(&(usr->gLocal));
    //Inserta el vértice creado en el grafo local
    insertar_vertice(&(usr->gLocal), aux);
    //Inserta el vértice en el grafo global
    insertar_vertice(G, aux);
}

//Inicializa todos los campos de un usuario a unos valores por defecto e inserta el usuario en el árbol
void _inicializar_campos(abb *A,grafo *G,tipoclave nome){
    
    tipoelem e;
    
    //Inicializa el nombre del usuario con la clave pasada
    strcpy(e.nomeUsuario,nome);
    //Crea la pila que contendrá las transferencias del usuario
    crear_pila(&(e.pilaTransferencia));
    //Crea el grafo local del usuario
    _crear_grafos_usuario(G, &e);
    //Inserta el nuevo usuario en el árbol
    insertar(A, e);
}

//Vuelve a rellenar la pila original a partir de una pila auxiliar
void _recuperar_pila(pila * p, pila * aux){
    
    tipoelempila pEl;
    
    while (!(es_vacia_pila(*aux))) {
        //Cogemos el tope de la pila auxiliar
        pEl = tope(*aux);
        //Lo metemos de nuevo en la pila principal
        push(p, pEl);
        //Desapilamos el elemento de la pila auxiliar
        pop(aux);
    }
}

//Imprime todos los campos de una transferencia
void _imprimir_transferencia(tipoelem usr){
    
    tipoelempila p;

    p = tope(usr.pilaTransferencia);
    
    printf("\nUsuario: %s\n",usr.nomeUsuario);
    //printf("Última transferencia:\n");
    if(p.cantidade != 0){
        //Se imprimen los datos de la transferencia, en el caso de que se haya realizado alguna
        printf("Receptor: %s \t",p.receptor);
        printf("Cantidade: %.2lf \t",p.cantidade);
        printf("Concepto: %s\n",p.concepto);
    }else //En el caso de que no haya ninguna, se imprime el siguiente mensaje
        printf("Este usuario non realizou ningunha transferencia\n\n");
}

//Imprime todos los elementos de una pila
void _imprimir_pila(pila *P){
    
    pila aux;
    crear_pila(&aux);
    tipoelempila pEl;
    int count = 1;  //Permite que la salida por pantalla sea más fácil de interpretar
    
    while(!es_vacia_pila(*P)){
        //Toma el elemento del tope de la pila
        pEl = tope(*P);
        //Lo apila en la pila auxiliar
        push(&aux, pEl);
        if(!es_vacia_pila(*P)){
            //Imprime todas las transferencias de la pila
            printf("\tTransferencia %d",count);
            printf("\tReceptor: %-10s",pEl.receptor);
            printf("\tCantidade: %5.2f €",pEl.cantidade);
            printf("\tConcepto: %s\n",pEl.concepto);
            count++;
        }
        //Desapila el elemento superior de la pila principal
        pop(P);
    }
    printf("\n");
    //Vuelve a rellenar la pila del usuario
    _recuperar_pila(P, &aux);
    //Destruye la pila auxiliar
    destruir_pila(&aux);
}

//Imprime un grafo
void imprimirGrafo(grafo G) {
    tipovertice *VECTOR; //Para almacenar el vector de vertices del grafo
    int N; //numero de vertices del grafo
    
    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);
    
    int i, j;
    for (i = 0; i < N; i++) {
        //Imprimo el vertice
        printf("Vertice(%d): %s\n", i, VECTOR[i].usuario);
        //Chequeo sus arcos
        for (j = 0; j < N; j++)
            if (son_adyacentes(G, i, j))
                printf("\t%s-->%s\n", VECTOR[i].usuario, VECTOR[j].usuario);
    }
}

//Imprime todas las transferencias de un usuario
void _imprimir_nodo(tipoelem *E){
    //Imprime el nombre del usuario
    printf("\nUsuario: %s \n",(E->nomeUsuario));
    if(num_vertices(E->gLocal)>1){
        if(!es_vacia_pila(E->pilaTransferencia))
            //Si la pila no está vacía, imprime su contenido
            _imprimir_pila(&(E->pilaTransferencia));
        else
            printf("\tEste usuario non realizou ningunha transferencia.\n\n");
        printf("Su grafo local es:\n\n");
        //Imprime el grafo asociado al usuario
        imprimirGrafo(E->gLocal);
    }
    else
        printf("Este usuario non realizou ningunha transferencia\n\n");
}
//Es necesario invocar a la función modificar después de esta función, para poder actualizar el puntero a la pila que ha sido modificado previamente

//Imprime el árbol mediante el recorrido inorden
void inorden(abb A){
    tipoelem E;
    
    if(!es_vacio(A)){
        //Toma el elemento del árbol a la que se apunta en ese momento
        info(A, &E);
        //Imprime el contenido del nodo actual
        _imprimir_nodo(&E);
        printf("\n---------------------------------------\n");
        //Se modifica el árbol con el puntero a la pila actualizado
        modificar(&A, E);
        //Se invoca el recorrido inorden con el hijo izquierdo del nodo actual
        inorden(izq(A));
        //Se invoca el recorrido inorden con el hijo derecho del nodo actual
        inorden(der(A));
    }
}

//Función recursiva que comprueba todos los nodos del árbol e imprime todos aquellos en los que encuentra la clave cl como receptor
void _buscar_receptor(abb A,char* cl,int *flag){
    tipoelem usr;
    pila aux;
    tipoelempila pEl;
    
    if(!es_vacio(A)){
        //Es necesario recorrer todo el árbol
        //Se toma el elemento que contiene el nodo actual
        info(A, &usr);
        //Crea la pila
        crear_pila(&aux);
        while(!es_vacia_pila(usr.pilaTransferencia)){
            pEl = tope(usr.pilaTransferencia);
            //Compara la clave pasada como argumento con el campo receptor del elemento actual. Si es 0, se imprime la transferencia
            if(!strcmp(cl,pEl.receptor)){
                _imprimir_transferencia(usr);
                //Se incluye una flag para poder comprobar si un usuario ha recibido alguna transferencia
                (*flag)++;
            }
            //Se inserta el elemento en la pila auxiliar
            push(&aux, pEl);
            //Desapila el elemento superior de la pila principal
            pop(&(usr.pilaTransferencia));
        }
        //Vuelve a rellenar la pila del usuario
        _recuperar_pila(&(usr.pilaTransferencia), &aux);
        //Destruye la pila
        destruir_pila(&aux);
        //Se modifica el árbol con el puntero a la pila actualizado
        modificar(&A, usr);
        //Invoca a la función con el puntero al Árbol izquierdo como argumento
        _buscar_receptor(izq(A), cl,flag);
        //Invoca a la función con el puntero al Árbol derecho como argumento
        _buscar_receptor(der(A), cl,flag);
    }
}

//Función recursiva que reinicia los valores de los nodos en los que se encuentra la clave como receptor
void _borrar_referencia(abb A,char* cl,tipovertice V){
//Aunque por convención se debería pasar el argumento A como *A, eso forzaría a crear un árbol auxiliar
//por lo que, en este caso el código queda más optimizado no respetando esa convencioón
    
    tipoelem usr;
    pila aux;
    tipoelempila pEl;
    
    if(!es_vacio(A)){
        //Es necesario recorrer todo el árbol
        //Se toma el elemento que contiene el nodo actual
        info(A, &usr);
        //Crea la pila
        crear_pila(&aux);
        while(!es_vacia_pila(usr.pilaTransferencia)){
            pEl = tope(usr.pilaTransferencia);
            pop(&(usr.pilaTransferencia));
            //Compara la clave con el receptor
            //Si es distinto, se apila en la pila auxiliar para después devolverlo a la pila principal
            if(strcmp(cl, pEl.receptor))
                push(&aux, pEl);
        }
        //Borra la referencia en el grafo local
        if(existe_vertice(usr.gLocal, V))
            borrar_vertice(&(usr.gLocal), V);
        //Vuelve a rellenar la pila del usuario
        _recuperar_pila(&(usr.pilaTransferencia), &aux);
        //Destruye la pila
        destruir_pila(&aux);
        //Es necesario invocar a la función modificar después de esta función, para poder actualizar el puntero a la pila que ha sido modificado previamente
        modificar(&A, usr);
        //Se procede a invocar la función de manera recursiva, similar al recorrido inorden
        //Invoca a la función con el puntero al Árbol izquierdo como argumento
        _borrar_referencia(izq(A), cl,V);
        //Invoca a la función con el puntero al Árbol derecho como argumento
        _borrar_referencia(der(A), cl, V);

    }
}

void _crear_relaciones(grafo *G,abb *A,tipoelem E, tipoelempila pEl){
    
    tipovertice verticeEmisor, verticeReceptor;
    tipoelem receptor;
    //Se procede a crear todos los grafos y vértices necesarios
    //Copia el nombre del usuario emisor al vértice
    strcpy(verticeEmisor.usuario, E.nomeUsuario);
    //Copia el nombre del usuario receptor en el vértice del receptor
    strcpy(verticeReceptor.usuario, pEl.receptor);
    //
    strcpy(receptor.nomeUsuario, pEl.receptor);
    //Comprueba que el usuario receptor no está presente en el árbol
    if(!es_miembro_clave(*A, receptor.nomeUsuario)){
        //Inserta el vértice del receptor en el grafo global
        insertar_vertice(G,verticeReceptor);
        //Crea la pila asociada al elemento receptor
        crear_pila(&(receptor.pilaTransferencia));
        //Crea el grafo local del receptor
        crear_grafo(&(receptor.gLocal));
        //Inserta el vértice en el grafo local
        insertar_vertice(&(receptor.gLocal), verticeReceptor);
        //Inserta el elemento asociado al receptor en el árbol
        insertar(A, receptor);
    }else
        buscar_nodo(*A, receptor.nomeUsuario, &receptor);
    //Crea los arcos en todos los grafos
    //Crea el arco en el grafo global
    crear_arco(G, posicion(*G, verticeEmisor), posicion(*G,verticeReceptor));
    //Comprueba si el usuario emisor ya había realizado una transferencia al usuario receptor
    if(!existe_vertice(E.gLocal, verticeReceptor))
        //Inserta el vértice del receptor en el grafo local del emisor
        insertar_vertice(&(E.gLocal), verticeReceptor);
    if(!son_adyacentes(E.gLocal, posicion(E.gLocal, verticeEmisor), posicion(E.gLocal,verticeReceptor)))
        //Crea el arco en el grafo local del emisor
        crear_arco(&(E.gLocal), posicion(E.gLocal, verticeEmisor), posicion(E.gLocal,verticeReceptor));
    //Comprueba si el usuario emisor ya había realizado una transferencia al usuario receptor
    if(!existe_vertice(receptor.gLocal, verticeEmisor))
        //Inserta el vértice del receptor en el grafo local del emisor
        insertar_vertice(&(receptor.gLocal), verticeEmisor);
    if(!son_adyacentes(receptor.gLocal, posicion(receptor.gLocal, verticeEmisor), posicion(receptor.gLocal,verticeReceptor)))
        //Crea el arco en el grafo local del emisor
        crear_arco(&(receptor.gLocal), posicion(receptor.gLocal, verticeEmisor), posicion(receptor.gLocal,verticeReceptor));
}

//Función que introduce los datos de una transferencia
void _introducir_datos(abb *A,grafo *G, tipoelem E,tipoelempila pEl){
    tipoelem receptor;
    //Inicializa los campos de un usuario en el caso de que no haya realizado ninguna transferencia
    if(!strcmp(pEl.receptor, "*")){
        _inicializar_campos(A, G,E.nomeUsuario);
        return;
    }
    strcpy(receptor.nomeUsuario, pEl.receptor);
    //Si el usuario ya es miembro, simplemente se modificará
    if(es_miembro_clave(*A, E.nomeUsuario)){
        //Busca el usuario dentro del árbol
        buscar_nodo(*A, E.nomeUsuario, &E);
        //Apila la nueva transferencia
        push(&(E.pilaTransferencia), pEl);
        //Modifica el usuario
        modificar(A, E);
        //Crea todas las relaciones entre grafos
        _crear_relaciones(G, A, E,pEl);
    }else{
        //Si no es miembro, se procederá de forma similar a la creación del primer usuario
        _crear_grafos_usuario(G, &E);
        //Crea la pila del usuario
        crear_pila(&(E.pilaTransferencia));
        //Apila el primer elemento del primer usuario
        push(&(E.pilaTransferencia), pEl);
        //Inserta el primer usuario en el árbol
        insertar(A, E);
        _crear_relaciones(G, A, E, pEl);
    }
}
/////////////////////FIN FUNCIONES PRIVADAS


////////////////////FUNCIONES PÚBLICAS

//Permite leer los datos de las transferencias guardados en un archivo de texto .txt
void lerDatos(abb *A,grafo *G){
    
    tipoelem E;
    tipoelempila pEl;
    
    FILE *fp = NULL;
    //Abre el archivo
    fp = fopen(ARQUIVO,  "rt");
    //Comprueba que el archivo ha sido abierto
    if(fp){
        //Lee la primera línea
        fscanf(fp, "%s %s ",E.nomeUsuario,pEl.receptor);
        if(strcmp(pEl.receptor, "*")){
            //Evita que lea la cantidad y el concepto en el caso que un usuario no tenga transferencias
            fscanf(fp, " %lf %[^\r\n]", &pEl.cantidade,pEl.concepto);
        }
        while(!feof(fp)){
            _introducir_datos(A, G, E, pEl);
            //Lee una linea, que está asociada a una única transferencia
            fscanf(fp, "%s %s",E.nomeUsuario,pEl.receptor);
            if(strcmp(pEl.receptor, "*")){
                //Evita que lea la cantidad y el concepto en el caso que un usuario no tenga transferencias
                fscanf(fp, " %lf %[^\r\n]", &pEl.cantidade,pEl.concepto);
            }
        }
        //Cierra el archivo
        fclose(fp);
    }else{
        printf("O arquivo non foi aberto\n");
       return;
    }
}

//Recorre todo el árbol de manera recursiva e imprime en el archivo los datos de todas las transferencias
void _escribir_recursivo(abb A,FILE *f){
    
    tipoelem E;
    tipoelempila pEl;
    pila aux;
    
    //Comprueba que el árbol no sea vacío
    if(!es_vacio(A)){
        //Recibe la información asociada al usuario contenido en el nodo actual del árbol
        info(A, &E);
        if(!es_vacia_pila(E.pilaTransferencia)){
            //Crea la pila auxiliar
            crear_pila(&aux);
            //Invierte el orden de la pila mediante una pila auxiliar
            while(!es_vacia_pila(E.pilaTransferencia)){
                push(&aux, tope(E.pilaTransferencia));
                pop(&(E.pilaTransferencia));
            }
            while(!es_vacia_pila(aux)){
                //Toma el elemento del tope de la pila
                pEl = tope(aux);
                if(strcmp(pEl.receptor, "*")){
                    //Imprime la información de la transferencia en el archivo
                    fprintf(f, "%s %s %.2lf %s\n",E.nomeUsuario,pEl.receptor,pEl.cantidade,pEl.concepto);
                }else
                    fprintf(f, "%s *\n", E.nomeUsuario);
                //Apila de nuevo el elemento en la pila principal
                push(&(E.pilaTransferencia), pEl);
                //Desapila el elemento de la pila auxiliar
                pop(&aux);
            }
            //Destruye la pila auxiliar
            destruir_pila(&aux);
            //Actualiza el puntero a la pila
            modificar(&A, E);
        }else{
            //Comprueba que el usuario no haya emitido ni recibido ninguna transferencia
            if(num_vertices(E.gLocal) ==1)
                fprintf(f, "%s *\n", E.nomeUsuario);
        }
        //Invoca a la función con el hijo derecho
        _escribir_recursivo(der(A),f);
        //Invoca a la función con el hijo izquierdo
        _escribir_recursivo(izq(A),f);
    }
}

//Permite escribir los datos de las transferencias en un archivo de texto .txt
void escribirDatos(abb *A){
    
    FILE *fp = NULL;
    //Abre el archivo en modo escritura
    fp = fopen(ARQUIVO,  "w+");
    //Comprueba que el archivo ha sido abierto
    if(fp){
        //Escribe los datos
        _escribir_recursivo(*A, fp);
        //Cierra el archivo
        fclose(fp);
    }else
        printf("El archivo no ha sido abierto");
}

//Permite introducir una transferencia a partir de los datos proporcionados por el usuario
void introducirTransferencia(abb *A,grafo *G,char *nome){
    
    tipoelem emisor;
    tipoelempila pElem;
    
    //Toma el nombre del usuario actual
    strcpy(emisor.nomeUsuario, nome);
    printf("Introduza o nome do usuario receptor\n$>");
    scanf(" %s", pElem.receptor);

    printf("Introduza o concepto da transferencia\n$>");
    scanf(" %[^\r\n]", pElem.concepto);
    
    printf("Introduza a cantidade a transferir\n$>");
    scanf(" %lf", &(pElem.cantidade));
    
    //Llama a la función que crea todos los usuarios y relaciones necesarias
    _introducir_datos(A, G, emisor, pElem);
}

//Permite buscar si el usuario está presente en el árbol e imprime su última transferencia
void consultaUsuario(abb A,char * nome){
    
    tipoelem usr;
    
    if(es_miembro_clave(A, nome)){
        //Se busca el nodo en el que está el usuario y se obtiene su valor
        buscar_nodo(A, nome, &usr);
        //Si la pila no es vacía, imprime las transferencias asociadass
        if(!es_vacia_pila(usr.pilaTransferencia))
            _imprimir_pila(&(usr.pilaTransferencia));
        else
            printf("Este usuario non realizou ningunha transferencia\n");
        //Se actualiza el usuario con el nuevo puntero a la pila
        modificar(&A, usr);
    }else
        printf("O usuario consultado non existe\n");
}

//Permite buscar si el usuario está en el árbol e imprime las transferencias que ha recibido
void consultaReceptor(abb A, char * nome){
    
    int aux = 0;
    
    if(es_miembro_clave(A, nome)){
        //Llama a la función recursiva que busca referencias al receptors
        _buscar_receptor(A, nome,&aux);
        //Se imprime el número de transferencias que ha recibido, también para prevenir el caso de que no se muestre nada si no ha recibido ninguna
        printf("O usuario recibiu %d transferencias\n",aux);
    }else
        printf("O usuario introducido non existe\n");
    
}

//Permite eliminar el usuario del árbol, eliminando también sus referencias
void eliminarUsuario(abb *A,grafo *G, char * nome){
    
    tipoelem usr;
    tipovertice v;
    
    if(es_miembro_clave(*A, nome)){
        //En primer lugar, se busca el usuario en el árbol
        buscar_nodo(*A, nome, &usr);
        //Crea el vértice a eliminar
        strcpy(v.usuario, usr.nomeUsuario);
        //Se reinicializan las posibles referencias al usuario
        _borrar_referencia(*A, usr.nomeUsuario,v);
        //Borra el vértice en el grafo global
        borrar_vertice(G, v);
        //Finalmente se suprime del árbol
        suprimir(A, usr);
    }else
        printf("O usuario introducido non existe\n");
}

//Permite calcular el grado de entrada de un vértice
int _calcular_grao_entrada(grafo G, tipovertice V){
    //Toma la posición del vértice en el grafo G
    int pos = posicion(G, V),count = 0;
    //Recorre todos los vértices del grafo
    for(int i = 0; i < num_vertices(G);i++){
        //Si existe un grafo de i a pos, entonces el grado de entrada aumenta en 1
        if(son_adyacentes(G, i, pos))
            count++;
    }
    return count;
}

//Permite calcular el grado de salida de un vértice
int _calcular_grao_salida(grafo G, tipovertice V){
    //Toma la posición del vértice en el grafo G
    int pos = posicion(G, V),count = 0;
    //Recorre todos los vértices del grafo
    for(int i = 0; i < num_vertices(G);i++){
        //Si existe un grafo de pos a i, entonces el grado de entrada aumenta en 1
        if(son_adyacentes(G, pos, i))
            count++;
    }
    return count;
}

//Permite obtener las estadísticas de un usuario
void obterEstadisticas(abb A, char * nome){
    
    tipoelem usr;
    tipoelempila pEl;
    tipoelempila * maxEl; //Variable que almacena las transferencias máximas de un usuario
    int maxCount = 1; //Lleva la cuenta de elementos en el array de transferencias máximas
    pila aux;
    double totalTransferido = 0;
    //Crea la pila auxiliar
    crear_pila(&aux);
    if(es_miembro_clave(A, nome)){
            //Se busca el usuario en el árbol
            buscar_nodo(A, nome, &usr);
            if(!es_vacia_pila(usr.pilaTransferencia)){
                //Se reserva memoria para un elemento
                maxEl = (tipoelempila *)malloc(sizeof(tipoelempila));
                //Inicializa el primer elemento de maxEl al tope de la pila de transferencias
                *maxEl = tope(usr.pilaTransferencia);
                //Apila el elemento en la pila auxiliar
                push(&aux, *maxEl);
                //Inicializa la cantidad de dinero transferido a la primera transferencia
                totalTransferido = (*maxEl).cantidade;
                //Desapila el elemento superior de la pila principal
                pop(&(usr.pilaTransferencia));
                //Es necesario recorrer toda la pila
                while(!es_vacia_pila(usr.pilaTransferencia)){
                    //Toma el elemento superior de la pila
                    pEl = tope(usr.pilaTransferencia);
                    //Almacena la suma de las cantidades transferidas por el usuario
                    totalTransferido += pEl.cantidade;
                    //Si el elemento actual es mayor que el almacenado, su valor se cambia
                    if(pEl.cantidade > (*maxEl).cantidade){
                        //Se reinicializa a 1
                        maxCount = 1;
                        //Reserva memoria para solo un elemento
                        maxEl = (tipoelempila *)realloc(maxEl, sizeof(tipoelempila));
                        //Toma el elemento actual como único elemento de maxEl
                        *maxEl = pEl;
                    }else if(pEl.cantidade == (*maxEl).cantidade){
                        //Se aumenta el tamaño del array en 1
                        maxCount++;
                        //Reserva memoria para otro elemento
                        maxEl = (tipoelempila *)realloc(maxEl, maxCount*sizeof(tipoelempila));
                        //Se añade el elemento al array
                        *(maxEl + maxCount - 1) = pEl;
                    }
                    //Apila el elemento en la pila auxiliar
                    push(&aux, pEl);
                    //Desapila el elemento superior de la pila principal
                    pop(&(usr.pilaTransferencia));
                }
                //Vuelve a rellenar la pila principal
                _recuperar_pila(&(usr.pilaTransferencia), &aux);
                destruir_pila(&aux);
                //Se actualiza el usuario con el nuevo puntero a la pila
                modificar(&A, usr);
                //Imprime el total transferido
                printf("Total transferido: \t %.2lf \n",totalTransferido);
                //Imprime la mayor transferencia
                printf("Máxima transferencia: \n");
                for(int i = 0; i < maxCount; i++){
                    printf("\tReceptor:\t %-10s",(*(maxEl + i)).receptor);
                    printf("\tCantidade:\t %5.2lf €",(*(maxEl + i)).cantidade);
                    printf("\tConcepto:\t %s\n",(*(maxEl + i)).concepto);
                }
                //Libera la memoria asociada al vector maxEl
                free(maxEl);
        }else{
            printf("----Este usuario non realizou ningunha transferencia----\n");
        }
    }else
        printf("O usuario introducido non existe\n");
}

//Imprime los usuarios que más transferencias han emitido
void  _maior_transferencias_emitidas(grafo G){
    tipovertice *V;
    //Variable que lleva la cuenta del número de usuarios con el número máximo de transferencias emitidas
    int maxCount = 1;
    //Como es posible que exista más de un usuario con el mismo número de transferencias, se creará un vector para devolver todas las posiciones
    tipovertice * arrayVertices = (tipovertice *) malloc(sizeof(tipovertice));
    //Inicializa V al array de vértices del grafo
    V = array_vertices(G);
    //Asigna a la primera posición de arrayVertices el primer elemento de V
    *arrayVertices = *V;
    for(int i = 1; i < num_vertices(G); i++){
        //Se comprueba si existe un usuario con mayor grado de salida que el grado de salida de los elementos del array de vértices
        if(_calcular_grao_salida(G, *(V + i)) > _calcular_grao_salida(G, *arrayVertices)){
            //Se reinicializa a 1
            maxCount = 1;
            //Reserva memoria para solo un elemento
            arrayVertices = (tipovertice *)realloc(arrayVertices, sizeof(tipovertice));
            //Toma el elemento actual como único elemento de arrayVértices
            *arrayVertices = *(V + i);
        }else if(_calcular_grao_salida(G, *(V + i)) == _calcular_grao_salida(G, *arrayVertices)){
            //Reserva memoria para otro elemento en el array
            arrayVertices = (tipovertice *)realloc(arrayVertices, (maxCount+1)*sizeof(tipovertice));
            //Se añade a la nueva posición del array
            *(arrayVertices + maxCount) = *(V + i);
            //Aumenta la cuenta
            maxCount++;
        }
    }
    for(int i = 0; i < maxCount;i++){
        printf("%s:\t %d\n",(arrayVertices + i)->usuario,_calcular_grao_salida(G, *arrayVertices));
    }
    //Libera la memoria asociada al array a devolver
    free(arrayVertices);
}

//Imprime los usuarios que más transferencias han recibido
void _maior_transferencias_recibidas(grafo G){
    tipovertice *V;
    //Variable que lleva la cuenta del número de usuarios con el número máximo de transferencias emitidas
    int maxCount = 1;
    //Como es posible que exista más de un usuario con el mismo número de transferencias, se creará un vector para devolver todas las posiciones
    tipovertice * arrayVertices = (tipovertice *) malloc(sizeof(tipovertice));
    //Inicializa V al array de vértices del grafo
    V = array_vertices(G);
    //Asigna a la primera posición de arrayVertices el primer elemento de V
    *arrayVertices = *V;
    for(int i = 1; i < num_vertices(G); i++){
        //Se comprueba si existe un usuario con mayor grado de salida que el grado de salida de los elementos del array de vértices
        if(_calcular_grao_entrada(G, *(V + i)) > _calcular_grao_entrada(G, *arrayVertices)){
            //Se reinicializa a 1
            maxCount = 1;
            //Reserva memoria para solo un elemento
            arrayVertices = (tipovertice *)realloc(arrayVertices, sizeof(tipovertice));
            //Toma el elemento actual como único elemento de arrayVértices
            *arrayVertices = *(V + i);
        }else if(_calcular_grao_entrada(G, *(V + i)) == _calcular_grao_entrada(G, *arrayVertices)){
            //Reserva memoria para otro elemento en el array
            arrayVertices = (tipovertice *)realloc(arrayVertices, (maxCount+1)*sizeof(tipovertice));
            //Se añade a la nueva posición del array
            *(arrayVertices + maxCount) = *(V + i);
            //Aumenta la cuenta
            maxCount++;
        }
    }
    for(int i = 0; i < maxCount;i++){
        printf("%s:\t %d\n",(arrayVertices + i)->usuario,_calcular_grao_entrada(G, *arrayVertices));
    }
    //Libera la memoria asociada al array a devolver
    free(arrayVertices);
}

//Imprime el numéro de amigos medio por usuario
double _media_amigos(grafo G){
    double media = 0;
    tipovertice * varray;
    //Inicializa varray al array de vértices del grafo
    varray = array_vertices(G);
    for(int i = 0; i < num_vertices(G); i++){
        for(int j = 0; j < num_vertices(G);j++){
            //Comprueba si existe un arco entre dos vértices
            if(son_adyacentes(G, posicion(G, varray[i]), posicion(G, varray[j])) || son_adyacentes(G, posicion(G, varray[j]), posicion(G, varray[i])))
                media++;
        }
    }
    //Devuelve el número de arcos dividido entre el número de vértices
    return media/(double)num_vertices(G);
}
//Calcula las estadísticas globales a partir del grafo
void obterEstadisticasGlobais(grafo G){
    //Invoca a la función num_vértices para saber el número total de usuarios
    printf("Número de usuarios rexistrados:\t%d\n",num_vertices(G));
    //Invoca a la función que calcula la media de amigos
    printf("Media de amigos por usuario:\t%.2f\n",_media_amigos(G));
    //Invoca a la función que calcula los usuarios con el mayor número de transferencias emitidass
    printf("Usuarios que realizaron o maior número de transferencias:\n");
    _maior_transferencias_emitidas(G);
    //Invoca a la función que calcula los usuarios con el mayor número de transferencias recibidas
    printf("Usuarios que recibiron o maior número de transferencias:\n");
    _maior_transferencias_recibidas(G);
}

//Calcula el usuario con mayor actividad en la plataforma
void calcularUsuarioMaisActivo(grafo G){
    tipovertice *V;
    int maxCount = 1,suma = 0;
    //Como es posible que exista más de un usuario con el mismo valor de actividad, se creará un array
    tipovertice * arrayVertices = (tipovertice *) malloc(sizeof(tipovertice));
    //Inicializa V al array de vértices del grafo G
    V = array_vertices(G);
    //Inicializa el primer elemento de arrayVertices al primer elemento de V
    *arrayVertices = *V;
    //Recorre todo el array
    for(int i = 1; i < num_vertices(G); i++){
        //Suma el grado de entrada y el grado de salida
        suma = _calcular_grao_entrada(G, *(V + i)) + _calcular_grao_salida(G, *(V+i));
        //Comprueba si el elemento actual tiene una actividad mayor que los elementos de arrayVertices
        if(suma > _calcular_grao_entrada(G, *arrayVertices) + _calcular_grao_salida(G, *arrayVertices)){
            //Reinicia la cuenta
            maxCount = 1;
            //Reserva memoria para un único elemento
            arrayVertices = (tipovertice *)realloc(arrayVertices, sizeof(tipovertice));
            //Inserta el elemento actual en arrayVertices
            *arrayVertices = *(V + i);
        }else if(suma == _calcular_grao_entrada(G, *arrayVertices) + _calcular_grao_salida(G, *arrayVertices)){
            //Reserva memoria para un elemento más
            arrayVertices = (tipovertice *)realloc(arrayVertices, (maxCount+1)*sizeof(tipovertice));
            //Inserta el elemento actual en arrayVertices
            *(arrayVertices + maxCount) = *(V + i);
            //Aumenta la cuenta
            maxCount++;
        }
    }
    printf("Os usuarios mais activos son:\n");
    for(int i = 0; i < maxCount;i++){
        printf("%s:\n\tGrao de entrada: %d\n\tGrao de saída: %d\n\tTotal: %d\n",(arrayVertices + i)->usuario,_calcular_grao_entrada(G, *(arrayVertices + i)),_calcular_grao_salida(G, *(arrayVertices + i)),_calcular_grao_entrada(G, *(arrayVertices + i))+_calcular_grao_salida(G, *(arrayVertices + i)));
    }
    //Libera la memoria asociada a arrayVertices
    free(arrayVertices);
}

void _borrar_referencia_amigo(abb *A, tipoelem *E, char * amigo){
    
    pila aux;
    tipoelempila pEl;
    
    //Borra las transferencias
    crear_pila(&aux);
    while(!es_vacia_pila(E->pilaTransferencia)){
        pEl = tope(E->pilaTransferencia);
        pop(&(E->pilaTransferencia));
        //Compara la clave con el receptor
        //Si es distinto, se apila en la pila auxiliar para después devolverlo a la pila principal
        if(strcmp(amigo, pEl.receptor))
            push(&aux, pEl);
    }
    //Vuelve a rellenar la pila del usuario
    _recuperar_pila(&(E->pilaTransferencia), &aux);
    //Destruye la pila
    destruir_pila(&aux);
    //Es necesario invocar a la función modificar después de esta función, para poder actualizar el puntero a la pila que ha sido modificado previamente
    modificar(A, *E);
}

void borrarAmigo(abb *A,grafo *G,char * usuario){
    
    tipoelem E,amigo;
    char nomeAmigo[MAXLONXITUDE];
    tipovertice Vusr,Vamigo;
    
    //Busca el nodo asociado al usuario en el árbol
    buscar_nodo(*A, usuario, &E);
    printf("Este é o seu grafo local actual:\n");
    //Imprime el grafo local del usuario
    imprimirGrafo(E.gLocal);
    printf("Introduza o nome do amigo a eliminar:\n$>");
    scanf(" %s",nomeAmigo);
    //Introduce el nombre del amigo en un vértice
    strcpy(Vamigo.usuario, nomeAmigo);
    //Comprueba que sea amigo del usuario
    if(existe_vertice(E.gLocal, Vamigo)){
        //Borra el vértice del amigo en el grafo local del usuario
        borrar_vertice(&(E.gLocal), Vamigo);
        //Busca el nodo asociado al amigo en el árbol
        buscar_nodo(*A, nomeAmigo, &amigo);
        //Introduce el nombre del usuario en un vértice
        strcpy(Vusr.usuario,usuario);
        //Borra el vértice del usuario en el grafo local del amigo
        borrar_vertice(&(amigo.gLocal), Vusr);
        //Borra el arco en el grafo global
        borrar_arco(G, posicion(*G, Vusr), posicion(*G, Vamigo));
        //Hay que contemplar el otro caso
        borrar_arco(G, posicion(*G, Vamigo), posicion(*G, Vusr));
        //Borra las transferencias emitidas por el usuario al amigo
        _borrar_referencia_amigo(A, &E,nomeAmigo);
        //Borra las transferencias emitidas por el amigo al usuario
        _borrar_referencia_amigo(A, &amigo, E.nomeUsuario);
        //Se imprime el grafo local del usuario
        printf("Novo grafo local de %s:\n\n",E.nomeUsuario);
        imprimirGrafo(E.gLocal);
        //Se imprime el grafo global
        printf("\n\nNovo grafo global:\n");
        imprimirGrafo(*G);
    }else{
        printf("O usuario introducido non é o seu amigo actualmente\n");
    }
}
//Inicia sesión en payETSE
void logIn(abb *A,grafo *G){
    
    char usuario[20],opt = 'L';
    
    printf("--- Introduza o nome de usuario ----\n$>");
    scanf(" %s",usuario);
    
    if(!strcmp(usuario, "admin")) {
        while(opt != 's'){
            printf("--------- Seleccione unha das seguintes opcións -----------\n");
            printf("----------- a) Imprimir usuarios ----------------------\n");
            printf("----------- b) Imprimir grafo global ------------------\n");
            printf("----------- c) Obter estatísticas globais -------------\n");
            printf("----------- d) Calcular usuario máis activo --------------\n");
            printf("----------- e) Dar de baixa a un usuario -------------\n");
            printf("----------- s) Saír do menú de administrador ----------\n$>");
            scanf(" %c",&opt);
            
            switch (opt) {
                case 'a':
                    //Realizamos el recorrido inorden del árbol, imprimiendo su nombre, pila de transferencias y grafo privado
                    inorden(*A);
                    break;
                case 'b':
                    //Imprime grafo global
                    imprimirGrafo(*G);
                    break;
                case 'c':
                    //Calcula las estadísticas globales del grafo
                    obterEstadisticasGlobais(*G);
                    break;
                case 'd':
                    //Usuario más activo
                    calcularUsuarioMaisActivo(*G);
                    break;
                case 'e':
                    //Elimina un usuario del árbol
                    printf("Introduza o nome do usuario a borrar\n$>");
                    scanf(" %s",usuario);
                    eliminarUsuario(A,G,usuario);
                    break;
                case 's':
                    break;
                default:
                    printf("Introduza un caracter válido\n");
                    break;
            }
        }
    }else{
        if(!es_miembro_clave(*A, usuario)){
            printf("---- Para darse de alta na aplicación, introduza unha transferencia ----\n");
            introducirTransferencia(A, G, usuario);
        }
        while(opt != 's'){
            printf("---- Benvido/a %s, seleccione unha das seguintes opcións ----\n",usuario);
            printf("--------- a) Introducir transferencia -------\n");
            printf("--------- b) Consultar transferencias emitidas -----------\n");
            printf("--------- c) Consultar transferencias recibidas ----------\n");
            printf("--------- d) Estatísticas de usuario ---------------\n");
            printf("--------- e) Darse de baixa -------------\n");
            printf("--------- f) Borrar amigo ----------------\n");
            printf("--------- s) Saír do menú de usuario ---------------\n$>");
            scanf(" %c",&opt);
            switch (opt) {
                case 'a':
                    //Introduce una nueva transferencia en el árbol y realiza el recorrido inorden
                    introducirTransferencia(A,G,usuario);
                    break;
                case 'b':
                    //Consulta la información asociada a un usuario
                    consultaUsuario(*A,usuario);
                    break;
                case 'c':
                    //Consulta las transferencias que el usuario solicitado ha recibido
                    consultaReceptor(*A,usuario);
                    break;
                case 'd':
                    //Calcula la máxima transferencia realizada por un usuario, así como el total transferido por el mismo
                    obterEstadisticas(*A,usuario);
                    break;
                case 'e':
                    //Elimina un usuario del árbol
                    eliminarUsuario(A,G,usuario);
                    return;
                    break;
                case 'f':
                    //Elimina a un amigo
                    borrarAmigo(A,G,usuario);
                    break;
                case 's':
                    break;
                default:
                    printf("Introduza un caracter válido\n");
                    break;
            }
        }
    }
}


//Realiza el recorrido inorden del árbol y lo destruye
void sairPrograma(abb *A,grafo *G){
    inorden(*A);
    //Dest
    destruir_arbol(A);
    //Borra el grafo global
    borrar_grafo(G);
    printf("Teña un bo día \n");
}
