/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "gestion_tienda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

lista_usuario *obj_lista_usuarios;
lista_producto *obj_lista_producto;
lista_compras *obj_lista_compras;

void agregarProducto(char *, char *, float);

int tamanio_lista_usuario = 0;
int tamanio_lista_compras = 0;
int id=1;
int cantidad_productos=0;

lista_usuario *crear_lista_usuario();
lista_producto *crear_lista_producto();
lista_compras *crear_lista_compras();
void mostrar_usuarios();
float calcular_total_compra();

bool_t *
registrar_usuario_1_svc(usuario *argp, struct svc_req *rqstp)
{
	static bool_t  result;
	printf("======Se ha llamado la funcion registrar usuario======\n");
	nodo_usuario *obj_nodo_usuario = (nodo_usuario*)malloc(sizeof(nodo_usuario));
	obj_nodo_usuario->obj_usuario = *argp;
	
	free(obj_lista_compras);
	
	if(tamanio_lista_usuario == 0){
		obj_lista_usuarios = crear_lista_usuario();
		printf("======lista de usuarios creada======");
	}
	
	if(obj_lista_usuarios -> tamanio == 0)
        {
                obj_lista_usuarios -> cabeza_usuario = obj_nodo_usuario;
                obj_nodo_usuario -> siguiente = NULL;
                printf("\n======Primer usuario registrado======\n");
        }
        else
        {
                nodo_usuario *cabeza_anterior = obj_lista_usuarios -> cabeza_usuario;
                obj_lista_usuarios-> cabeza_usuario = obj_nodo_usuario;
                obj_nodo_usuario -> siguiente = cabeza_anterior;
                printf("\n======Nuevo usuario registrado======\n");
        }

        tamanio_lista_usuario = 1;
        obj_lista_usuarios -> tamanio = obj_lista_usuarios -> tamanio + 1;

        if(obj_lista_usuarios -> tamanio > 0)
        {
                result = TRUE;
        }
        else
        {
                result = FALSE;
        }
	mostrar_usuarios();

	return &result;
}

lista_producto *
imprimir_productos_1_svc(void *argp, struct svc_req *rqstp)
{
	static lista_producto  *result;

	printf("\n ======Se ha llamado la funcion imprimir productos======\n");

	obj_lista_producto = (lista_producto *)malloc(sizeof(lista_producto));
	obj_lista_producto -> tamanio = 0;
	obj_lista_producto -> cabeza_producto = NULL;

	agregarProducto("60", "Arroz", 2000.0);
	agregarProducto("50", "Sal", 1300.0);
	agregarProducto("40", "Azucar", 1700.0);
	agregarProducto("30", "Pastas", 2000.0);
	agregarProducto("20", "Cafe", 2700.0);
	agregarProducto("10", "Harina", 3000.0);

	result = obj_lista_producto;

	return result;
}

bool_t *
agregrar_a_la_lista_de_compras_1_svc(codigo *argp, struct svc_req *rqstp)
{
	static bool_t  result;
	
	
	printf("\n ======Se ha llamado la funcion agregar producto a la lista de compras======\n");
	
	nodo_producto *obj_producto_actual = obj_lista_producto -> cabeza_producto;
	
	while(obj_producto_actual != NULL){
		
		if (strcmp(obj_producto_actual->obj_producto.id, argp->id) == 0) {
		    break;
		}else{
			obj_producto_actual = obj_producto_actual -> siguiente;	
		}
	}
	
	printf("nombre del producto: %s \n",obj_producto_actual->obj_producto.nombre);
	
	if(tamanio_lista_compras == 0){
		obj_lista_compras = crear_lista_compras();
		printf("======lista de compras creada======");
		tamanio_lista_compras = 1;
	}
	
	if(obj_lista_compras -> tamanio == 0)
        {
                obj_lista_compras -> obj_producto_cabeza = obj_producto_actual;
                obj_producto_actual -> siguiente = NULL;
                printf("\n======Primer producto agregado a la lista de compras======\n");
        }
	else
	{
		nodo_producto *obj_anterior_cabeza = obj_lista_compras -> obj_producto_cabeza;
		obj_lista_compras -> obj_producto_cabeza = obj_producto_actual;
		obj_producto_actual -> siguiente = obj_anterior_cabeza;
		printf("\n======Otro producto agregado a la lista de compras======\n");
	}
	obj_lista_compras -> tamanio = obj_lista_compras -> tamanio + 1;
	if(obj_lista_compras -> tamanio > 0){
		result = TRUE;
	}else{
		result = FALSE;
	}
	
	return &result;
}

lista_compras *
imprimir_listas_compras_1_svc(void *argp, struct svc_req *rqstp)
{
	static lista_compras  *result;
	
	result = obj_lista_compras;

	return result;
}

bool_t *
abrir_sesion_1_svc(datos_credenciales *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	 printf("\n ======Se ha llamado la funcion abrir sesion======");
	 nodo_usuario *obj_nodo_actual = obj_lista_usuarios  -> cabeza_usuario;

        while(obj_nodo_actual != NULL)
        {
                if(strcmp(obj_nodo_actual -> obj_usuario.user_name, argp -> user_name) == 0
                   && strcmp(obj_nodo_actual -> obj_usuario.password, argp -> password) == 0)
                {
                	printf("\n ======Bienvenido Cliente Fiel======\n");
                        result = TRUE;
                        break;
                }
                else
                {
                        obj_nodo_actual = obj_nodo_actual -> siguiente;
                        result = FALSE;
                }
        }

	return &result;
}

factura *
imprimir_factura_1_svc(void *argp, struct svc_req *rqstp)
{
	static factura result;
	
	printf("\n ======Se ha llamado la funcion imprimir factura======");

	result.id =id;
	result.obj_compra = obj_lista_compras;
	result.total_compra = 0.0f;
	result.cantidad_productos = 0;
	
	nodo_producto *obj_actual = obj_lista_compras->obj_producto_cabeza;

        while(obj_actual != NULL)
        {
        	result.total_compra = result.total_compra + obj_actual->obj_producto.valor;
        	result.cantidad_productos = result.cantidad_productos+1;
                obj_actual = obj_actual -> siguiente;
        }
	
	if(result.cantidad_productos > 2){
		result.descuento=result.total_compra * 0.1;
	}
	else
	{
		result.descuento = 0.0;
	}
	
	result.total_compra = result.total_compra - result.descuento;
	

	return &result;
}

lista_usuario * crear_lista_usuario(){
	lista_usuario *lista = (lista_usuario *)malloc(sizeof(lista_usuario));
	lista -> tamanio = 0;
	lista -> cabeza_usuario = NULL;
	return lista;
}

lista_compras * crear_lista_compras(){
	lista_compras *lista = (lista_compras *)malloc(sizeof(lista_compras));
	lista -> tamanio = 0;
	lista -> obj_producto_cabeza = NULL;
	return lista;
}

void mostrar_usuarios()
{
        nodo_usuario *objNodoActual = obj_lista_usuarios  -> cabeza_usuario;

        while(objNodoActual != NULL)
        {
                printf("\n Nombre del usuario agregado: ");
                puts(objNodoActual -> obj_usuario.full_name);
                objNodoActual = objNodoActual -> siguiente;
        }
}

void agregarProducto(char *prm_id, char *prm_nombre, float prm_valor)
{
	nodo_producto *obj_actual_producto = (nodo_producto *)malloc(sizeof(nodo_producto));

	strcpy(obj_actual_producto -> obj_producto.id, prm_id);
	strcpy(obj_actual_producto -> obj_producto.nombre, prm_nombre);
	obj_actual_producto -> obj_producto.valor = prm_valor;

	if(obj_lista_producto -> tamanio == 0)
	{
		obj_lista_producto -> cabeza_producto = obj_actual_producto;
		obj_actual_producto -> siguiente = NULL;
	}
	else
	{
		nodo_producto *obj_cabeza_anterior = obj_lista_producto -> cabeza_producto;
		obj_lista_producto -> cabeza_producto = obj_actual_producto;
		obj_actual_producto -> siguiente = obj_cabeza_anterior;
	}

	obj_lista_producto -> tamanio = obj_lista_producto -> tamanio + 1;
}






