#include <stdio.h>
#include <stdlib.h>

#include "abin.h"

void inorden(abin A){
	tipoelem E;
	if(!esVacio(A)){
	  inorden(izq(A));
	  info(A,&E); printf("%c ",E);
	  inorden(der(A));
	}	
}

void preorden(abin A){
	tipoelem E;
	if(!esVacio(A)){
	  info(A,&E); printf("%c ",E);
	  preorden(izq(A));	
	  preorden(der(A));
	}	
}

void postorden(abin A){
	tipoelem E;
	if(!esVacio(A)){
	  postorden(izq(A));	
	  postorden(der(A));
	  info(A,&E); printf("%c ",E);
	}	
}
