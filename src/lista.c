#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t* nodo_fin;
	size_t cantidad;
};

struct lista_iterador {
	nodo_t* nodo_actual;
	lista_t* lista;
};

lista_t *lista_crear()
{	
	return calloc(1, sizeof(struct lista));
}

lista_t *lista_insertar(lista_t *lista, void *elemento) {
    if (lista == NULL) {
        return NULL; 
    }

    nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
    if (nuevo_nodo == NULL) {
		lista_destruir(lista);
        return NULL; 
    }
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->siguiente = NULL;

    if(lista_vacia(lista)){
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
	}else{
		lista->nodo_fin->siguiente = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
	}

    (lista->cantidad)++;
    return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(lista == NULL){
		return NULL;
	}

	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if(nodo_nuevo == NULL){
		lista_destruir(lista);
		return NULL;
	}
	nodo_nuevo->elemento = elemento;
	nodo_nuevo->siguiente = NULL;


	if(posicion == 0 || lista->cantidad == 0){
		nodo_nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_nuevo;
		
		if(lista->cantidad == 0){
			lista->nodo_fin = nodo_nuevo;
		}
		(lista->cantidad)++;
		return lista;
	}
	
	if(posicion >= lista_tamanio(lista)){
		lista->nodo_fin->siguiente = nodo_nuevo;
		lista->nodo_fin = nodo_nuevo;
		(lista->cantidad)++;
		return lista;
	}

	nodo_t* nodo_anterior = lista->nodo_inicio;
	size_t contador = 0;
	while(contador < posicion - 1){
		nodo_anterior = nodo_anterior->siguiente;
		contador++;
	}
	nodo_nuevo->siguiente = nodo_anterior->siguiente; //si fuera 0 1 2, y quiero insertar en la posicion nodo anterior es 1 y nodo anterior siguiente es 2
	nodo_anterior->siguiente = nodo_nuevo; //aca el siguiente al 1 tiene que ser el nodo nuevo
	(lista->cantidad)++;
	return lista;
}
	
void *lista_quitar(lista_t *lista)
{	
	if(lista == NULL || lista->cantidad == 0){
		return NULL;
	}

	if(lista->cantidad == 1){
		void* elemento = lista->nodo_inicio->elemento;
		free(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		lista->cantidad = 0;
		return elemento;
	}
	
	nodo_t* penultimo = lista->nodo_inicio;
	while(penultimo->siguiente != lista->nodo_fin){
		penultimo = penultimo->siguiente;
	}

	nodo_t* ultimo = penultimo->siguiente;
	penultimo->siguiente = NULL;
	lista->nodo_fin = penultimo;
	void* elemento = ultimo->elemento;
	free(ultimo);
	(lista->cantidad)--;
	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(lista == NULL || lista->nodo_inicio == NULL){
		return NULL;
	}

	if(posicion >= lista_tamanio(lista)){
		return lista_quitar(lista);
	}

	nodo_t* nodo;
	void* elemento;

	if(posicion == 0){
		nodo = lista->nodo_inicio->siguiente;
		elemento = lista->nodo_inicio->elemento;
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo;
		(lista->cantidad)--;
		return elemento;
	}

	
	nodo_t* nodo_anterior = lista->nodo_inicio;
	for (size_t i = 0; i < posicion - 1; i++) 
	{
        nodo_anterior = nodo_anterior->siguiente;
    }

	nodo_t* nodo_a_eliminar = nodo_anterior->siguiente;
	elemento = nodo_a_eliminar->elemento;
	nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
	free(nodo_a_eliminar);
	(lista->cantidad)--;
	if(nodo_a_eliminar == lista->nodo_fin){
		lista->nodo_fin = nodo_anterior;
	}
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{	
	if(lista == NULL || lista_vacia(lista) || posicion >= lista->cantidad){
		return NULL;
	}

	nodo_t* nodo_actual = lista->nodo_inicio;
	for(size_t i = 0; i < posicion; i++){
		nodo_actual = nodo_actual->siguiente;
	}
	return nodo_actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if(lista == NULL || comparador == NULL || lista_vacia(lista)){
		return NULL;
	}

	nodo_t* nodo_actual = lista->nodo_inicio;
	size_t contador = 0;
	bool encontrado = false;
	while(contador < lista_tamanio(lista) && !encontrado){
		if((*comparador)(nodo_actual->elemento, contexto) == 0){
			encontrado = true;
		}else{
			nodo_actual = nodo_actual->siguiente;
		}
		contador++;
	}
	
	if(encontrado)
		return nodo_actual->elemento;
	else
		return NULL;
}

void *lista_primero(lista_t *lista)
{	
	if(lista == NULL || lista_vacia(lista)){
		return NULL;
	}

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{	
	if(lista == NULL || lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{	
	return lista == NULL || lista_tamanio(lista) == 0;
}

size_t lista_tamanio(lista_t *lista)
{	
	if(lista == NULL)
		return 0;
		
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if(lista == NULL){
		return;
	}

	if(!lista_vacia(lista)){
		nodo_t* nodo_actual = lista->nodo_inicio;
		size_t contador = 0;
		while(contador < lista_tamanio(lista)){
			nodo_t* nodo_siguiente = nodo_actual->siguiente;
			free(nodo_actual);
			nodo_actual = nodo_siguiente;
			contador++;
		}
	}

	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(lista == NULL)
		return;

	if(funcion == NULL){
		lista_destruir(lista);
		return;
	}
	
	if(!lista_vacia(lista)){
		nodo_t* nodo_actual = lista->nodo_inicio;
		size_t contador = 0;
		while(contador < lista_tamanio(lista)){
			nodo_t* nodo_siguiente = nodo_actual->siguiente;
			(*funcion)(nodo_actual->elemento);
			free(nodo_actual);
			nodo_actual = nodo_siguiente;
			contador++;
		}
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{	
	if(lista == NULL)
		return NULL;

	struct lista_iterador* lista_iterador = malloc(sizeof(struct lista_iterador));
	if(lista_iterador == NULL)
		return NULL;
	
	lista_iterador->nodo_actual = lista->nodo_inicio;
	lista_iterador->lista = lista;
	return lista_iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{	
    if(iterador == NULL || iterador->lista == NULL || lista_vacia(iterador->lista)) 
        return false;

    return iterador->nodo_actual != NULL;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{	
	if(iterador == NULL || iterador->nodo_actual == NULL || iterador->lista == NULL)
		return false;
	
	iterador->nodo_actual = iterador->nodo_actual->siguiente;
	
	if(iterador->nodo_actual == NULL){
		return false;
	}
	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{	
	if(iterador == NULL || iterador->nodo_actual == NULL || iterador->lista == NULL)
		return NULL;

	return iterador->nodo_actual->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if(iterador == NULL)
		return;
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{	
	if(lista == NULL || funcion == NULL || contexto == NULL){
		return 0;
	}

	size_t contador = 0;
	nodo_t* nodo_actual = lista->nodo_inicio;
	while(nodo_actual != NULL && (funcion)(nodo_actual->elemento, contexto)){
		nodo_actual = nodo_actual->siguiente;
		contador++;
	}

	return contador;
}

