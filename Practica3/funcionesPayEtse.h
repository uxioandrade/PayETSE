//
//  funcionesPayEtse.h
//  PayETSE
//
//  Created by Uxío García Andrade on 3/10/18.
//  Copyright © 2018 Uxío García Andrade. All rights reserved.
//

#ifndef __FUNCIONESPAYETSE_H
#define __FUNCIONESPAYETSE_H

#include "abb.h"

/**
* Introduce la información asociada a una transferencia, creando el usuario receptor y emisor en el caso de no existir
* @param A El árbol binario
**/
void introducirTransferencia(abb *A);

/**
* Busca un usuario en el árbol e imprime la información asociada a su última transferencia emitida
* @param A El árbol binario
**/
void consultaUsuario(abb A);

/**
* Busca un usuario en el árbol e imprime la inforamción asociada a sus transferencias recibidas
* @param A El árbol binario
**/
void consultaReceptor(abb A);

/**
* Busca un usuario en el árbol, elimina las referencias asociadas al mismo y lo elimina del árbol
* @param A El árbol binario
**/
void eliminarUsuario(abb *A);

/**
* Realiza el recorrido inorden del árbol y lo destruye
* @param A El árbol binario
**/
void sairPrograma(abb *A);

#endif /* __FUNCIONESPAYETSE_H */
