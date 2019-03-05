//
//  funcionesPayEtse.h
//  PayETSE
//
//  Created by Uxío García Andrade on 3/10/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#ifndef __FUNCIONESPAYETSE_H
#define __FUNCIONESPAYETSE_H

#include <stdio.h>
#include "abb.h"

/**
* Lee la información asociada a las transferencias almacenada en un archivo .txt
* @param A El árbol binario
* @param G El grafo
**/
void lerDatos(abb *A,grafo *G);

/**
 * Escribe la información asociada a las transferencias en un archivo .txt
 * @param A El árbol binario
 **/
void escribirDatos(abb *A);

/**
* Hace el recorrido inorden del árbol
* @param A El árbol binario
**/
void inorden(abb A);

/**
* Escribe por pantalla el grafo
* @param G El grafo
**/
void imprimirGrafo(grafo G);

/**
* Introduce la información asociada a una transferencia, creando el usuario receptor y emisor en el caso de no existir
* @param A El árbol binario
* @param G El grafo global
* @param nome do usuario que realiza a transferencia
**/
void introducirTransferencia(abb *A,grafo *G,char * nome);

/**
* Busca un usuario en el árbol e imprime la información asociada a su última transferencia emitida
* @param A El árbol binario
* @param nome El nombre del usuario
**/
void consultaUsuario(abb A,char * nome);

/**
* Busca un usuario en el árbol e imprime la inforamción asociada a sus transferencias recibidas
* @param A El árbol binario
* @param nome El nombre del usuario
**/
void consultaReceptor(abb A, char * nome);

/**
* Busca un usuario en el árbol, elimina las referencias asociadas al mismo y lo elimina del árbol
* @param A El árbol binario
* @param G El grafo global
* @param nome El nombre del usuario
**/
void eliminarUsuario(abb *A, grafo *G,char * nome);

/**
* Busca un amigo del usuario en el árbol, elimina las referencias asociadas al mismo y lo elimina del árbol
* @param A El árbol binario
* @param G El grafo global
* @param usuario El nombre del usuario
**/
void borrarAmigo(abb *A,grafo *G,char * usuario);

/**
* Obtiene las estadísticas de un usuario
* @param A El árbol binario
* @param nome El nombre del usuario
**/
void obterEstadisticas(abb A, char * nome);

/**
* Obtiene las estadísticas de un usuario
* @param G El grafo global
**/
void obterEstadisticasGlobais(grafo G);

/**
* Calcula el usuario con más transferencias emitidas y recibidas
* @param G El grafo global
**/
void calcularUsuarioMaisActivo(grafo G);

/**
* Realiza el recorrido inorden del árbol y lo destruye
* @param A El árbol binario
* @param G El grafo global
**/
void sairPrograma(abb *A,grafo *G);

/**
* Inicia sesión en la aplicación
* @param A Arbol G Grafo
**/
void logIn(abb *A, grafo *G);
 
#endif /* __FUNCIONESPAYETSE_H */
