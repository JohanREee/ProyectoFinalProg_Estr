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
    std::cout << "Unidad de medida no encontrada en el sistema. \n";
    return false;
}

lista_Producto *buscarProducto(lista_Producto *lista, int id_producto) // Leche            leche   1
{
    lista_Producto *aux = lista;
    while (aux != NULL)
    {
        if ((aux->producto.id_producto == id_producto) && (!aux->producto.anulado))
        {
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

void obtenerProducto(lista_Producto *lista)
{
    int id_producto;
    std::cout << "Digite el ID del producto que desea buscar: ";
    id_producto = soloEnteros(id_producto);
    lista_Producto *producto_actual = buscarProductoParaInformacion(lista, id_producto);
    if (producto_actual == NULL)
    {
        std::cout << "El producto no fue encontrado o validado.\n";
        return;
    }
    mostrarProducto(producto_actual);
}

lista_Producto *buscarProductoParaInformacion(lista_Producto *lista, int id_producto)
{
    lista_Producto *aux = lista;
    while (aux != NULL)
    {
        if (aux->producto.id_producto == id_producto)
        {
            if (aux->producto.anulado)
            {
                int op;
                std::cout << "El producto seleccionado ha sido anulado anteriormente del sistema. ¿Deseas observar su información?\n";
                std::cout << "1. Sí\n2. No";
                op = soloEnteros(op);
                if (op == 1)
                {
                    return aux;
                }
                return NULL;
            }
        }
        aux = aux->siguiente;
    }
    return NULL;
}
void mostrarProducto(lista_Producto *producto)
{
    std::cout << producto->producto.nombre_producto << "\n";
    std::cout << producto->producto.descripcion_producto << "\n";
    std::cout << producto->producto.unidad_medida << "\n";
    std::cout << producto->producto.existencia_cantidad << "\n";
    (producto->producto.anulado) ? std::cout << "El producto está anulado\n" : std::cout << "El producto no está anulado\n";
}

void mostrarTodosProducto(lista_Producto *lista_producto)
{
    int op;
    std::cout << "ADVERTENCIA. ¿Desea mostrar los productos anulados?\n";
    std::cout << "1.Sí\n2.No";
    op = soloEnteros(op);
    (op == 1) ? mostrarProductosAnulados(lista_producto) : mostrarProductosNoAnulados(lista_producto);
}

void mostrarProductosNoAnulados(lista_Producto *producto)
{
    lista_Producto *aux = producto;
    while (aux != NULL)
    {
        if (!producto->producto.anulado)
        {
            std::cout << producto->producto.nombre_producto << "\n";
            std::cout << producto->producto.descripcion_producto << "\n";
            std::cout << producto->producto.unidad_medida << "\n";
            std::cout << producto->producto.existencia_cantidad << "\n";
        }
        aux = aux->siguiente;
    }
}
void mostrarProductosAnulados(lista_Producto *producto)
{
    lista_Producto *aux = producto;
    while (aux != NULL)
    {
        std::cout << producto->producto.nombre_producto << "\n";
        std::cout << producto->producto.descripcion_producto << "\n";
        std::cout << producto->producto.unidad_medida << "\n";
        std::cout << producto->producto.existencia_cantidad << "\n";
        aux = aux->siguiente;
    }
}
// Nombre, descripcion, unidad medida, cantidad
void modificarProducto(lista_Producto *&lista)
{
    int id_producto;
    std::cout << "Ingrese el ID del producto: ";
    id_producto = soloEnteros(id_producto);
    lista_Producto *producto_actual = buscarProducto(lista_producto, id_producto);
    if (producto_actual == NULL)
    {
        std::cout << "Producto no encontrado.\n";
        return;
    }
    int op;
    std::cout << "Seleccione el campo de " << producto_actual->producto.nombre_producto << " que desea modificar\n";
    std::cout << "1. Nombre\n";
    std::cout << "2. Descripción\n";
    std::cout << "3. Unidad de medida\n";
    std::cout << "4. Cantidad actual en existencia\n";
    op = soloEnteros(op);
    switch (op)
    {
    case 1:
        char *nombre;
        std::cout << "Digite el nuevo nombre del producto: ";
        agregarElementoPuntero(nombre, input);
        std::cout << "Nombre del producto " << producto_actual->producto.nombre_producto << " ha sido cambiado a " << nombre << " exitosamente.\n";
        //Lineas para modificar un dato.
        delete[] producto_actual->producto.nombre_producto; //Primero se borra la memoria dinamica
        producto_actual->producto.nombre_producto = new char[strlen(nombre) + 1]; //Se reasigna con el tamaño del char ingresado con anterioridad (char *nombre)
        strcpy(producto_actual->producto.nombre_producto, nombre); // se copia el contenido de nombre a el puntero de la estructura que debe contener el nombre real
        //
        delete [] nombre;
        break;
    case 2:
        char *descripcion;
        std::cout << "Digite la nueva descripcion del producto: ";
        agregarElementoPuntero(descripcion, input);
        std::cout << "Descripcion anterior: " << producto_actual->producto.descripcion_producto << "\n";
        std::cout << "Descripcion nueva: " << descripcion << "\n";
        delete[] producto_actual->producto.descripcion_producto;
        producto_actual->producto.descripcion_producto = new char[strlen(descripcion) + 1];
        strcpy(producto_actual->producto.descripcion_producto, descripcion);
        delete[] descripcion;
        break;
    case 3:
        while (true)
        {
            char *unidad_medida;
            std::cout << "Digite la nueva unida de medida: ";
            agregarElementoPuntero(descripcion, input);
            if (!comprobarUnidadMedida(lista_unidad_medida, unidad_medida))
            {
                int opt;
                std::cout << "¿Desea digitar otra unidad de medida?\n";
                std::cout << "1.Sí\n2.No";
                opt = soloEnteros(opt);
                if (opt == 1)
                {
                    continue;
                }
                else
                {
                    std::cout << "Serás enviado al menú anterior.\n";
                    return;
                }
            }
            std::cout << "La unidad de medida " << producto_actual->producto.unidad_medida << " ha sido reemplazada por " << unidad_medida << " exitosamente";
            delete[] producto_actual->producto.unidad_medida;
            producto_actual->producto.unidad_medida = new char[strlen(unidad_medida)+1];
            strcpy(producto_actual->producto.unidad_medida, unidad_medida);
            delete[] unidad_medida;
            break;
        }
        break;
    case 4:
        int cantidad_existencia;
        std::cout << "Digite la nueva cantidad en existencia: ";
        cantidad_existencia = soloEnteros(cantidad_existencia);
        std::cout << "La cantidad en existencia actual (" << producto_actual->producto.existencia_cantidad << ") ha sido reemplazada por " << cantidad_existencia;
        producto_actual->producto.existencia_cantidad = cantidad_existencia;
        break;
    default:
        std::cout << "Has digitado un valor invalido.\n";
        std::cout << "Serás enviado al menú anterior.\n";
        return;
    }
    return;

}
#endif