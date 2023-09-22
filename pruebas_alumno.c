#include "pa2m.h"
#include "src/lista.h"

void se_puede_crear_lista()
{
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista != NULL, "Se pudo crear una lista.");
    lista_destruir(lista);
}

void una_lista_recien_creada_tiene_tamano_0()
{
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista_tamanio(lista) == 0, "Una lista creada tiene tamaño cero.");
    lista_destruir(lista);
}

void el_primer_elemento_lista_vacia_es_null(){
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista_primero(lista) == NULL, "El primer elemento de una lista vacia es NULL.");
    lista_destruir(lista);
}

void el_ultimo_elemento_lista_vacia_es_null(){
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista_ultimo(lista) == NULL, "El ultimo elemento de una lista vacia es NULL.");
    lista_destruir(lista);
}

void borrar_al_final_lista_vacia_devuelve_null(){
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista_quitar(lista) == NULL, "Borrar al final de una lista sin elementos devuelve NULL");
    lista_destruir(lista);
}

void borrar_en_posicion_arbitraria_de_lista_vacia_devuelve_null(){
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == NULL, "Borrar en posicion arbitraria a una lista sin elementos devuelve NULL");
    lista_destruir(lista);
}

void pedir_una_posicion_arbitraria_de_lista_vacia_devuelve_null(){
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista_elemento_en_posicion(lista, 10) == NULL, "Pedir una posicion arbitraria a una lista sin elementos devuelve NULL");
    lista_destruir(lista);
}

void insertar_un_elemento_al_final_devuelve_lista(){
    lista_t* lista = lista_crear();
    void* e1 = (void*)0x12345;
    pa2m_afirmar(lista_insertar(lista, e1) != NULL, "Insertar un elemento al final devuelve la lista");
    lista_destruir(lista);
}

void la_lista_contiene_un_elemento(){
    lista_t* lista = lista_crear();
    void* e1 = (void*)0x12345;

    lista_insertar(lista, e1);
    pa2m_afirmar(lista_tamanio(lista) == 1, "La lista tiene 1 elemento");
    pa2m_afirmar(lista_tamanio(lista) != 0, "La lista no está vacia");
    lista_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================= pruebas de creacion de listas ========================");
    se_puede_crear_lista();
    una_lista_recien_creada_tiene_tamano_0();

    pa2m_nuevo_grupo(
		"\n======================= pruebas con lista vacia ========================");
    el_primer_elemento_lista_vacia_es_null();
    el_ultimo_elemento_lista_vacia_es_null();
    borrar_al_final_lista_vacia_devuelve_null();
    borrar_en_posicion_arbitraria_de_lista_vacia_devuelve_null();
    pedir_una_posicion_arbitraria_de_lista_vacia_devuelve_null();

    pa2m_nuevo_grupo(
		"\n======================= pruebas de inserción ========================");
    insertar_un_elemento_al_final_devuelve_lista();
    la_lista_contiene_un_elemento();

	return pa2m_mostrar_reporte();
}
