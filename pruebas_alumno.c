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

int main()
{
	pa2m_nuevo_grupo(
		"\n======================= pruebas de creacion de listas ========================");
    se_puede_crear_lista();
    una_lista_recien_creada_tiene_tamano_0();

	return pa2m_mostrar_reporte();
}
