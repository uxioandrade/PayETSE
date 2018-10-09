#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abin.h"
#include "pilaOperandos.h"
#include "pilaOperadores.h"

//Devuelve la prioridad del operador dentro de la pila.
//Prioridad('(')=0
int prioridadDentro(char op) {
    int prior=0;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 0;
            break;
    }
    return prior;
}

//Devuelve la prioridad del operador fuera de la pila.
//Prioridad('(')=4
int prioridadFuera(char op) {
    int prior=0;
    switch (op) {
        case '^': prior = 3;
            break;
        case '*': case '/': prior = 2;
            break;
        case '+': case '-': prior = 1;
            break;
        case '(': prior = 4;
            break;
    }
    return prior;
}

//Devuelve 1 si c es un operador: +, -, /, *, ^, ()
unsigned esOperador(char c) {
    unsigned ope;
    switch (c) {
        case '^': case '*': case '/': case '+': case '-': case '(':
            ope = 1;
            break;
        default:
            ope = 0;
    }
    return ope;
}

//Devuelve 1 si c es un operando: numeros de 1 cifra y letras mayusculas y minusculas
unsigned esOperando(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c>= 48 && c<= 57)) //Ampliamos la función para que permita introducir números
        return 1;
    else
        return 0;
}

//Necesitamos incluír el prototipo por ser una función utilizada antes de ser escrita
void despilarElementos(abin *arbolAuxiliar,pilaOperadores *pOperadores,pilaOperandos *pOperandos);

/*
 Recibe una cadena de caracteres y devuelve el arbol de expresion
 @param expr_infija Expresion a evaluar
*/
abin arbolExpresion(char *expr_infija) {
    
    abin aux;
    pilaOperandos pOpn;
    pilaOperadores pOpd;
    
    //Crea la pila donde se almacenarán los operadores y la pila de punteros a los operandos
    crearPilaOperandos(&pOpn);
    crearPilaOperadores(&pOpd);
    
    char c = expr_infija[0]; //En primer lugar se iguala c al primer elemnto de la expresion
    
    while(c != '\0'){
        if(esOperando(c)){ //Si c es un operando, inserta en un árbol y se apila
            crear(&aux);
            insizq(&aux, c);
            pushOperandos(&pOpn, aux);
        }else if(esOperador(c)){    //Si c es un operador, mientras la pila de operadores no esté vacía y la prioridad del elemento de arriba sea menor que el de abajo, se procederá a:
            while(!esVaciaPilaOperadores(pOpd) && prioridadFuera(c)<=prioridadDentro(topeOperadores(pOpd))){
                despilarElementos(&aux, &pOpd, &pOpn);
            }
            pushOperadores(&pOpd, c); //Inserta el carácter en la pila de operadores
        }else if(c == ')'){
            //Si
            while(topeOperadores(pOpd) != '('){
                despilarElementos(&aux, &pOpd, &pOpn);
            }
            popOperadores(&pOpd); //Desapila el elemento del tope de la pila
        }
        //Recurre a aritmética de punteros para recorrer la cadena de carácteres que almacena la expresión a representar
        expr_infija++;
        c=expr_infija[0];
    }
    while(!esVaciaPilaOperadores(pOpd)){
        despilarElementos(&aux, &pOpd, &pOpn);
    }
    //Se destruyen las dos pilas, devolviendo el elemento restante de la pila de operandos
    destruirPilaOperadores(&pOpd);
    aux = topeOperandos(pOpn);
    destruirPilaOperandos(&pOpn);
    
    return aux;
}

//Funciones privadas, no incluídas en el .h
//Realiza el procedimiento de vaciado de pila cuando se verifican algunas de las condiciones necesarias

void despilarElementos(abin *arbolAuxiliar,pilaOperadores *pOperadores,pilaOperandos *pOperandos){
    
    char caux;
    
    crear(arbolAuxiliar); //Crea un árbol auxiliar
    //Toma el elemento del tope de la pila y lo desapila
    caux = topeOperadores(*pOperadores);
    popOperadores(pOperadores);
    //Inserta caux en la raíz del nuevo árbol
    insizq(arbolAuxiliar, caux);
    //Inserta el elemento del tope de la pila a la derecha de la raíz y lo desapila
    insArbolder(arbolAuxiliar, topeOperandos(*pOperandos));
    popOperandos(pOperandos);
    //Inserta el elemento del tope de la pila a la derecha de la raíz y lo desapila
    insArbolizq(arbolAuxiliar, topeOperandos(*pOperandos));
    popOperandos(pOperandos);
    //Inserta el árbol creado en el tope de la pila
    pushOperandos(pOperandos, *arbolAuxiliar);
}

