/*Estructuras remotas para gestionar la tienda*/ 
const max_name=30;
const max_lastname=30;
const max_id=20;
const max_user_name=20;
const max_password=30;
const max_rol=15;

/*estructuras para el manejo de listas de usuarios*/
struct usuario{
	char full_name[max_name];
	char last_name[max_lastname];
	char id[max_id];
	char user_name[max_user_name];
	char password[max_password];
};
struct nodo_usuario{
	usuario obj_usuario;
	nodo_usuario *siguiente;
};
struct lista_usuario{
	nodo_usuario *cabeza_usuario;
	int tamanio;
};

/*estructura para verificar el login del usuario */
struct datos_credenciales    
{
        char user_name[max_user_name];
        char password[max_password];
};

/*estructura para el manejo de listas de productos*/
struct producto{
	char id[max_id];
	char nombre[max_name];
	float valor;
};
struct nodo_producto{
	producto obj_producto;
	nodo_producto *siguiente;
};
struct lista_producto{
	nodo_producto *cabeza_producto;
	int tamanio;
};

/*estructura para el manejo de listas de compra de productos*/
struct lista_compras{
	nodo_producto *obj_producto_cabeza;
	int tamanio;
};


/*estructura para la gestion de la factura */
struct factura{
	int id;
	lista_compras *obj_compra;
	usuario obj_usuario;
	float total_compra;
	float cantidad_productos;
	float descuento;	
};

struct codigo{
	char id[max_id];
};



/*Definir funciones o procedimientos remotos  en comun con cliente servidor*/

program gestion_usuarios
{ 
        version gestion_usuarios_version
        { 
                bool registrar_usuario(usuario prm_obj_usuario) = 1;
                lista_producto imprimir_productos() = 2;
                bool agregrar_a_la_lista_de_compras(codigo prm_id) = 3;
                lista_compras imprimir_listas_compras() = 4;
		bool abrir_sesion(datos_credenciales prm_obj_credenciales) = 5;
		factura imprimir_factura() = 6;
        } = 1;
} = 0x20000020;
