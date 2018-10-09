#ifndef FUNCIONESEXPRESION_H
#define FUNCIONESEXPRESION_H
//Funciones para construcción del árbol de expresión

//Devuelve la prioridad del operador dentro de la pila.
//Prioridad('(')=0
int prioridadDentro(char op);

//Devuelve la prioridad del operador fuera de la pila.
//Prioridad('(')=4
int prioridadFuera(char op);

//Devuelve 1 si c es un operador: +, -, /, *, ^, ()
unsigned esOperador(char c);

//Devuelve 1 si c es un operando: números de 1 cifra y letras mayúsculas y minúsculas
unsigned esOperando(char c); //COMPLETARLA

//Recibe una cadena de caracteres y devuelve el árbol de expresión
abin arbolExpresion(char *expr_infija) ; //ESCRIBIR ESTA FUNCIÓN

#endif	// FUNCIONESEXPRESION_H