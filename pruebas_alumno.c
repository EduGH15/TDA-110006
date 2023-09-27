#include "pa2m.h"
#include "src/lista.h"

void se_puede_crear_lista()
{
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista != NULL, "Se pudo crear una lista.");
    pa2m_afirmar(lista_tamanio(lista) == 0, "Una lista creada tiene tamaño cero.");
    pa2m_afirmar(lista_primero(lista) == NULL, "El primer elemento de una lista vacia es NULL.");
    pa2m_afirmar(lista_ultimo(lista) == NULL, "El ultimo elemento de una lista vacia es NULL.");
    lista_destruir(lista);
}

void se_puede_agregar_o_quitar_elementos_de_lista_null(){
    lista_t* lista = lista_crear();
    pa2m_afirmar(lista_quitar(lista) == NULL, "Borrar al final de una lista sin elementos devuelve NULL");
    pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == NULL, "Borrar en posicion arbitraria a una lista sin elementos devuelve NULL");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 10) == NULL, "Pedir una posicion arbitraria a una lista sin elementos devuelve NULL");
    lista_destruir(lista);
}

void insertar_varios_elementos_devuelve_lista(){
    lista_t* lista = lista_crear();
    void *e1 = (void*)0xbebecafe, *e2 = (void*)0x1234, *e3 =  (void*)0x13213,  *e4 =  (void*)0x11673, *e5 =  (void*)0x12568;
    
    pa2m_afirmar(lista_insertar(lista, e1) == lista, "Insertar un elemento al final devuelve la lista");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e1, "Al insertar el elemento obtengo el mismo elemento.");
    pa2m_afirmar(lista_tamanio(lista) == 1, "La lista tiene 1 elementos"); // e1

    pa2m_afirmar(lista_insertar_en_posicion(lista, e2, 1) == lista, "Insertar un segundo elemento al final devuelve la lista");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e2, "Al insertar el segundo elemento obtengo el mismo elemento.");
    pa2m_afirmar(lista_tamanio(lista) == 2, "La lista tiene 2 elementos"); // e1 e2

    pa2m_afirmar(lista_insertar_en_posicion(lista, e3, 0) == lista, "Insertar un tercer elemento al inicio devuelve la lista");
    pa2m_afirmar(lista_primero(lista) == e3, "Al insertar el tercer elemento obtengo el mismo elemento.");
    pa2m_afirmar(lista_tamanio(lista) == 3, "La lista tiene 3 elementos"); // e3 e1 e2

    pa2m_afirmar(lista_insertar_en_posicion(lista, e4, 1) == lista, "Insertar un cuarto elemento en el medio devuelve la lista");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e4, "Al insertar el cuarto elemento obtengo el mismo elemento.");
    pa2m_afirmar(lista_tamanio(lista) == 4, "La lista tiene 4 elementos"); // e3 e4 e1 e2

    pa2m_afirmar(lista_insertar_en_posicion(lista, e5, 100) == lista, "Insertar un quinto elemento en una posicion que no existe, lo inserta al final");
    pa2m_afirmar(lista_ultimo(lista) == e5, "Al insertar el quinto elemento obtengo el mismo elemento.");
    pa2m_afirmar(lista_tamanio(lista) == 5, "La lista tiene 5 elementos"); // e3 e4 e1 e2 e5

    pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == e3, "El elemento en la posicion 0 es correcto");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == e4, "El elemento en la posicion 1 es correcto");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == e1, "El elemento en la posicion 2 es correcto");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == e2, "El elemento en la posicion 3 es correcto");
    pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == e5, "El elemento en la posicion 4 es correcto");
    pa2m_afirmar(lista_tamanio(lista) == 5, "La lista tiene en total 5 elementos");

    lista_destruir(lista);
}

void puedo_borrar_elemento_en_lista_con_un_elemento(){
    lista_t* lista = lista_crear();
    void *e1 = (void*)0xbebecafe, *e2 = (void*)0x1234;

    lista_insertar(lista, e1);
    pa2m_afirmar(lista_quitar(lista) == e1, "Puedo borrar un elemento en una lista con un elemento");
    pa2m_afirmar(lista_vacia(lista), "Borrar el unico elemento de la lista la deja vacia");
    pa2m_afirmar(lista_tamanio(lista) == 0, "Una lista vacía tiene 0 elementos.");

    pa2m_afirmar(lista_primero(lista) == NULL, "El primer elemento de una lista vacia es NULL");
    pa2m_afirmar(lista_ultimo(lista) == NULL, "El ultimo elemento de una lista vacia es NULL");
    
    pa2m_afirmar(lista_insertar(lista, e2) == lista, "Puedo insertar un elemento despues de haber borrado uno");
    pa2m_afirmar(lista_tamanio(lista) == 1, "La lista contiene 1 elemento.");
    lista_destruir(lista);
}

void Puedo_borrar_elementos_en_posiciones_arbitrarias(){
    lista_t* lista = lista_crear();
    int elementos[] = {0,1,3,5,7,10};
    for(int i = 0; i < 6; i++){
      lista_insertar(lista, &elementos[i]);
    }
    pa2m_afirmar(lista_tamanio(lista) == 6, "La lista contiene actualmente 6 elementos.");
    pa2m_afirmar(lista_quitar_de_posicion(lista, 100) == &elementos[5], "Puedo borrar un elemento en una posicion mayor a la cantidad de elementos");
    pa2m_afirmar(lista_tamanio(lista) == 5, "La lista contiene actualmente 5 elementos.");
    pa2m_afirmar(lista_ultimo(lista) == &elementos[4], "El elemento final ha cambiado y es el esperado");//0,1,3,5,7

    pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == &elementos[0], "Puedo borrar un elemento al inicio");//1,3,5,7
    pa2m_afirmar(lista_tamanio(lista) == 4, "La lista contiene actualmente 4 elementos.");
    pa2m_afirmar(lista_primero(lista) == &elementos[1], "Ahora el elemento inicial ha cambiado y es el esperado");

    pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == &elementos[3], "Puedo borrar un elemento en una posicion arbitraria");//1,3,7
    pa2m_afirmar(lista_tamanio(lista) == 3, "La lista contiene actualmente 3 elementos.");

    pa2m_afirmar(lista_quitar_de_posicion(lista, 4) == &elementos[4], "Puedo borrar un elemento en una posicion arbitraria");//1,3
    pa2m_afirmar(lista_tamanio(lista) == 2, "La lista contiene actualmente 2 elementos.");

    pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == &elementos[2], "Puedo borrar un elemento en una posicion arbitraria");//1
    pa2m_afirmar(lista_tamanio(lista) == 1, "La lista contiene actualmente 1 elementos.");

    pa2m_afirmar(lista_quitar_de_posicion(lista, 10) == &elementos[1], "Puedo borrar el ultimo elemento en una posicion arbitraria");//1
    pa2m_afirmar(lista_tamanio(lista) == 0, "La lista contiene actualmente 0 elementos.");
    pa2m_afirmar(lista_vacia(lista), "La lista se encuentra vacia");


    lista_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================= pruebas de creacion de listas ========================");
    se_puede_crear_lista();
    
    pa2m_nuevo_grupo(
		"\n======================= pruebas con lista vacia ========================");
    se_puede_agregar_o_quitar_elementos_de_lista_null();

    pa2m_nuevo_grupo(
		"\n======================= pruebas de inserción ========================");
    insertar_varios_elementos_devuelve_lista();

    pa2m_nuevo_grupo(
		"\n======================= pruebas de borrar un solo elemento ========================");
    puedo_borrar_elemento_en_lista_con_un_elemento();
    
    pa2m_nuevo_grupo(
		"\n======================= pruebas de borrado en una posicion arbitraria ========================");
    Puedo_borrar_elementos_en_posiciones_arbitrarias();

	return pa2m_mostrar_reporte();
}
