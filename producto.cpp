#include "structs.h"
#include "complemento.cpp"

#ifndef product
#define product
/*void agregarProductoEnLista(lista_Producto *&producto, char *input);
void mostrarTodosProducto(lista_Producto *&producto);
void mostrarProducto(lista_Producto *&producto);
void buscarProducto(lista_Usuario *lista, char *id_producto); //! important
void modificarProducto(lista_Usuario *&lista);
void eliminarTodaListaProducto(lista_Usuario *&lista);
void eliminarListaProducto(lista_Usuario *&lista, char *nombre, char *codigo_acceso);*/

void agregarUnidadMedida(lista_Unidad_Medida *&lista, char *input);
bool comprobarUnidadMedida(lista_Unidad_Medida *lista, char *unidad_medida);

void agregarUnidadMedida(lista_Unidad_Medida *&lista, char *input)
{
    char *unidad_medida;
    if (lista == NULL)
    {
        lista_Unidad_Medida *nueva_unidad = new lista_Unidad_Medida;
        nueva_unidad->siguiente = NULL;
        std::cout << "Antes de comenzar a ingresar productos, debes establecer al menos una unidad de medida en el sistema\n";
        std::cout << "Ingresar unidad de medida: ";
        agregarElementoPuntero(nueva_unidad->unidad_medida, input);
        lista = nueva_unidad;
        std::cout << "Unidad de medida agregada exitosamente.";
        system("pause");
        return;
    }
    else
    {
        std::cout << "Ingrese la nueva unidad de medida: ";
        agregarElementoPuntero(unidad_medida, input);
        lista_Unidad_Medida *x = lista;
        while (x != NULL)
        {
            if (strcmp(unidad_medida, x->unidad_medida) == 0)
            {
                std::cout << "Esta unidad de medida ya existe dentro de la lista de unidades de medida.\n";
                system("pause");
                delete[] unidad_medida;
                return;
            }
            if (x->siguiente == NULL)
            {
                lista_Unidad_Medida *nueva_unidad = new lista_Unidad_Medida;
                nueva_unidad->unidad_medida = unidad_medida; 
                x->siguiente = nueva_unidad; 
                std::cout << "Unidad de medida añadida al sistema exitosamente.\n";
                return; 
            }
            x = x->siguiente;
        }

    }
}
void agregarProductoEnLista(lista_Producto *&producto, char *input)
{
    char *unidad_medida;
    if (lista_unidad_medida == NULL)
    {
        agregarUnidadMedida(lista_unidad_medida, input);
    }
    lista_Producto *nuevo_producto = new lista_Producto();
    nuevo_producto->producto.id_producto = ++conteo_id_producto;
    std::cout << "Ingresar el nombre del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.nombre_producto, input);
    std::cout << "Ingresar unidad de medida: ";
    agregarElementoPuntero(unidad_medida, input);
    if (!comprobarUnidadMedida(lista_unidad_medida, unidad_medida))
    {
        std::cout << "\nSerás enviado al menú anterior.\n";
        conteo_id_producto--;
        delete[] unidad_medida;
        delete[] nuevo_producto->producto.nombre_producto;
        delete nuevo_producto;
        system("pause");
        return;
    }
    delete[] unidad_medida;

    std::cout << "Ingresar descripción del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.descripcion_producto, input);
    std::cout << "Para ingresar la cantidad en existencia (no puede ser menor que 0) ";
    std::cout << "Ten en cuenta que, si es un valor mayor que cero, se generará un lote en este preciso momento\n";
    std::cout << "Ingresar cantidad en existencia: ";

    nuevo_producto->producto.existencia_cantidad = soloEnteros(nuevo_producto->producto.existencia_cantidad);
    if (nuevo_producto->producto.existencia_cantidad <= 0)
    {
        nuevo_producto->producto.existencia_cantidad = 0;
    }
    else
    { // Codigo para ingresar el lote del producto nuevo
        agregarPrimerLote(nuevo_producto);
    }
    lista_Producto *aux = producto; // Reservamos el valor original de la lista
    lista_Producto *aux2;
    while (aux != NULL && aux->producto.id_producto)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la lista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (producto == aux)
    { // Nunca pasó por el while
        producto = nuevo_producto;
    }
    else
    { // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
        aux2->siguiente = nuevo_producto;
    }
    nuevo_producto->siguiente = aux; // nuevo_producto apunta a NULL

    std::cout << "Producto ingresado exitosamente.\n";
    system("pause");
    // Ejecutar un codigo para generar un lote con un año nuevo en el caso de que no haya sido ingresado
}

bool comprobarUnidadMedida(lista_Unidad_Medida *lista, char *unidad_medida)
{
    do
    {
        if (strcmp(lista->unidad_medida, unidad_medida) == 0)
        {
            return true;
        }
        lista = lista->siguiente;
    } while (lista != NULL);
    std::cout << "Unidad de medida no encontrada en el sistema. ";
    return false;
}

lista_Producto *buscarProducto(lista_Producto *lista, int id_producto)
{
    while (lista != NULL)
    {
        if (lista->producto.id_producto == id_producto)
        {
            return lista;
        }
        lista = lista->siguiente;
    }
    return NULL;
}

#endif