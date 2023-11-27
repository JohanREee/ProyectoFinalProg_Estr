#include "structs.h"
char input[MAXCHAR];

lista_Usuario *lista_usuario = NULL;
lista_Producto *lista_producto = NULL;
lista_Usuario *usuario_activo = NULL;
lista_Lote_Alerta_Caducidad *lote_caducidad = NULL;
lista_Producto_Alerta_Cantidad *producto_cantidad = NULL;
lista_Producto_Existencia *producto_existencia = NULL;
lista_Reporte_Rango *reporte_rango = NULL;

int conteo_id_producto = 0;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    leerProductosDeArchivo(lista_producto);
    int opcion = 0;
    agregarUsuarioMaestro(lista_usuario);
    leerUsuariosEnJSON(lista_usuario);
    inicioSesion(opcion);
    return 0;
}

void eliminarTodo(lista_Usuario *&lista_usuario, lista_Producto *&lista_producto) //! IMPORTANT
{
    while (lista_usuario != NULL)
    {

        lista_Usuario *aux = lista_usuario;

        delete[] aux->usuario.nombres;
        aux->usuario.nombres = NULL;

        delete[] aux->usuario.apellidos;
        aux->usuario.apellidos = NULL;

        delete[] aux->usuario.correo;
        aux->usuario.correo = NULL;

        delete[] aux->usuario.contrasena;
        aux->usuario.contrasena = NULL;
        lista_usuario = lista_usuario->siguiente;
        delete aux;
    }
    while (lista_producto != NULL)
    {
        lista_Producto *aux = lista_producto;
        delete[] aux->producto.nombre_producto;
        aux->producto.nombre_producto = NULL;
        delete[] aux->producto.descripcion_producto;
        aux->producto.descripcion_producto = NULL;
        while (lista_producto->producto.anos_producto != NULL)
        {
            Lista_Ano *ano_actual = lista_producto->producto.anos_producto;
            for (int i = 0; i < 12; i++)
            {
                while (ano_actual->ano_producto.producto[i].lotes != NULL)
                {
                    cola_Lote *lote_actual = ano_actual->ano_producto.producto[i].lotes;
                    delete[] lote_actual->lote.id_lote;
                    lote_actual->lote.id_lote = NULL;
                    ano_actual->ano_producto.producto[i].lotes = ano_actual->ano_producto.producto[i].lotes->siguiente;
                    delete lote_actual;

                    lote_actual = NULL;
                }
            }
            lista_producto->producto.anos_producto = lista_producto->producto.anos_producto->siguiente;
            delete ano_actual;
            ano_actual = NULL;
        }

        lista_producto = lista_producto->siguiente;
        delete aux;
        aux = NULL;
    }

    exit(1);
}
