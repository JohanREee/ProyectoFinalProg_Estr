#include "structs.h"
#include "complemento.cpp"

#ifndef product
#define product
/*
void agregarProductoEnLista(lista_Producto *&producto, char *input);
void mostrarTodosProducto(lista_Producto *lista_producto);
void mostrarProducto(lista_Producto *producto);
void mostrarProductosNoAnulados(lista_Producto *producto);
void mostrarProductosAnulados(lista_Producto *producto);
lista_Producto *buscarProducto(lista_Producto *lista, int id_producto);
void modificarProducto(lista_Producto *&lista_producto);
void eliminarTodaListaProducto(lista_Producto *&lista_producto);
void eliminarProducto(lista_Producto *&lista_producto);
void obtenerProducto(lista_Producto *lista_producto);
lista_Producto *buscarProductoParaInformacion(lista_Producto *lista, int id_producto);
*/

void agregarProductoEnLista(lista_Producto *&producto, char *input)
{
    lista_Producto *nuevo_producto = new lista_Producto();
    nuevo_producto->producto.id_producto = ++conteo_id_producto;
    std::cout << "Ingresar el nombre del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.nombre_producto, input);
    std::cout << "Ingresar descripción del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.descripcion_producto, input);
    std::cout << "Consideraciones a tomar en cuenta para ingresar la cantidad del producto.\n";
    std::cout << "-Si la cantidad es menor o igual a 0, su valor sera modificado para ser 0 en todos los casos.\n";
    std::cout << "-De otra forma, se creara un nuevo lote con la cantidad ingresada.\n";
    std::cout << "Ingresar cantidad en existencia: ";
    nuevo_producto->producto.existencia_cantidad = soloEnteros();
    if (nuevo_producto->producto.existencia_cantidad <= 0)
    {
        nuevo_producto->producto.existencia_cantidad = 0;
    }
    else
    { // Codigo para ingresar el lote del producto nuevo
        agregarPrimerLote(nuevo_producto);
    }
    int op;
    while (true)
    {
        std::cout << "¿Desea estandarizar la cantidad mínima de este producto en 10?\n";
        std::cout << "1. Sí\n";
        std::cout << "2. No\n";
        std::cout << "Ingresar número: ";
        op = soloEnteros();

        if (op == 1)
        {
            nuevo_producto->producto.minima_cantidad = 10;
            break;
        }
        else if (op == 2)
        {
            while (true)
            {
                std::cout << "Digite la cantidad mínima para este producto: ";
                nuevo_producto->producto.minima_cantidad = soloEnteros();
                if (nuevo_producto->producto.minima_cantidad >= 0)
                {
                    break;
                }
                std::cout << "La cantidad no puede ser menor a 0.\nIntente de nuevo.\n";
            }
            break;
        }
        else
        {
            std::cout << "Numero incorrecto.\nIntente de nuevo.\n";
        }
    }

    guardarProductoEnLista(lista_producto, nuevo_producto);

    std::cout << "Producto ingresado exitosamente.\n";
    std::cout << "El ID del producto es: " << nuevo_producto->producto.id_producto << "\n";
    system("pause");
}

void guardarProductoEnLista(lista_Producto *&lista_producto, lista_Producto *&nuevo_producto)
{

    lista_Producto *aux = lista_producto; // Reservamos el valor original de la lista
    lista_Producto *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la lista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (lista_producto == aux)
    { // Nunca pasó por el while
        lista_producto = nuevo_producto;
    }
    else
    { // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
        aux2->siguiente = nuevo_producto;
    }
    nuevo_producto->siguiente = aux; // nuevo_producto apunta a NULL
}

bool ingresarProducto(lista_Producto *&producto_actual)
{
    int id_producto;
    std::cout << "Digite el ID del producto que desea buscar: ";
    id_producto = soloEnteros();
    producto_actual = buscarProducto(lista_producto, id_producto);
    if (producto_actual == NULL)
    {
        std::cout << "El producto no fue encontrado o validado.\n";
        return false;
    }
    return true;
}

lista_Producto *buscarProducto(lista_Producto *lista, int id_producto) // Leche            leche   1
{
    lista_Producto *aux = lista;
    while (aux != NULL)
    {
        if ((aux->producto.id_producto == id_producto))
        {
            if (aux->producto.anulado)
            {
                int op;
                std::cout << "El producto \"" << aux->producto.nombre_producto << "\" ha sido anulado anteriormente del sistema. ¿Deseas continuar con tu acción?\n";
                verificarModificacionEnProducto(op);
                if (op == 1)
                {
                    return aux;
                }
                return NULL;
            }
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

void obtenerProducto(lista_Producto *lista_producto)
{
    lista_Producto *producto_actual = NULL;
    if (ingresarProducto(producto_actual))
    {
        mostrarProducto(producto_actual);
    }
}

void mostrarProducto(lista_Producto *producto)
{
    std::cout << "Nombre: " << producto->producto.nombre_producto << "\n";
    std::cout << "Descripcion: " << producto->producto.descripcion_producto << "\n"; // Controlar el flujo
    std::cout << "Cantidad en existencia: " << producto->producto.existencia_cantidad << "\n";
    std::cout << "Cantidad mínima de existencia: " << producto->producto.minima_cantidad << "\n";
    if (producto->producto.anulado)
    {
        std::cout << "\nEl producto está anulado\n";
    }
    else
    {
        std::cout << "\nEl producto no está anulado\n";
    }
    return;
}

void mostrarTodosProducto(lista_Producto *lista_producto)
{
    int op;
    std::cout << "ADVERTENCIA. ¿Desea mostrar los productos anulados?\n";
    verificarModificacionEnProducto(op);
    (op == 1) ? mostrarProductos(lista_producto, true) : mostrarProductos(lista_producto, false);
}

void mostrarProductos(lista_Producto *producto, bool show)
{ // mostrarProducto
    lista_Producto *aux = producto;
    while (aux != NULL)
    {
        if (!producto->producto.anulado || show)
        {
            std::cout << "Nombre del producto: " << producto->producto.nombre_producto << "\n";
            std::cout << "Descripción del producto: " << producto->producto.descripcion_producto << "\n";
            std::cout << "Cantidad en existencia:" << producto->producto.existencia_cantidad << "\n";
            std::cout << "Cantidad mínima de existencia: " << producto->producto.minima_cantidad << "\n";
            if (producto->producto.anulado)
            {
                std::cout << "\nEl producto está anulado\n";
            }
            else
            {
                std::cout << "\nEl producto no está anulado\n";
            }
            return;
        }
        aux = aux->siguiente;
    }
}
// Nombre, descripcion, unidad medida, cantidad
void modificarProducto(lista_Producto *&lista_producto)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    int op;
    std::cout << "Seleccione el campo de \"" << producto_actual->producto.nombre_producto << "\" que desea modificar\n";
    std::cout << "1. Nombre\n";
    std::cout << "2. Descripción\n";
    std::cout << "3. Cantidad minima en existencia.\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros();
    switch (op)
    {
    case 1:
        char *nombre;
        std::cout << "Digite el nuevo nombre del producto: ";
        agregarElementoPuntero(nombre, input);
        std::cout << "Nombre del producto \"" << producto_actual->producto.nombre_producto << "\" ha sido cambiado a \"" << nombre << "\" exitosamente.\n";
        // Lineas para modificar un dato.
        delete[] producto_actual->producto.nombre_producto;                       // Primero se borra la memoria dinamica
        producto_actual->producto.nombre_producto = new char[strlen(nombre) + 1]; // Se reasigna con el tamaño del char ingresado con anterioridad (char *nombre)
        strcpy(producto_actual->producto.nombre_producto, nombre);                // se copia el contenido de nombre a el puntero de la estructura que debe contener el nombre real
        //
        delete[] nombre; // Se elimina la memoria dinamica temporal
        break;
    case 2:
        char *descripcion;
        std::cout << "Digite la nueva descripcion del producto \"" << producto_actual->producto.nombre_producto << "\": ";
        agregarElementoPuntero(descripcion, input);
        std::cout << "Descripcion anterior: " << producto_actual->producto.descripcion_producto << "\n";
        std::cout << "Descripcion nueva: " << descripcion << "\n";
        delete[] producto_actual->producto.descripcion_producto;
        producto_actual->producto.descripcion_producto = new char[strlen(descripcion) + 1];
        strcpy(producto_actual->producto.descripcion_producto, descripcion);
        delete[] descripcion;
        break;
    case 3:
        int cantidad;
        std::cout << "Ingrese la nueva cantidad minima para el producto\"" << producto_actual->producto.nombre_producto << "\": ";
        cantidad = soloEnteros();
        if (cantidad >= 0)
        {
            std::cout << "La cantidad minima para el producto \"" << producto_actual->producto.nombre_producto << "\"";
            std::cout << " de " << producto_actual->producto.minima_cantidad << ".";
            std::cout << "\nHa sido reemplazada por: " << cantidad << "\n";
            producto_actual->producto.minima_cantidad = cantidad;
            break;
        }
        std::cout << "La cantidad minima no puede ser menor a 0.\n";
        std::cout << "Volviendo al menú anterior.\n";
        break;
    default:
        std::cout << "Has digitado un valor invalido.\n";
        std::cout << "Serás enviado al menú anterior.\n";
        break;
    }
    return;
}
void anularProducto(lista_Producto *&lista)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    if (producto_actual->producto.anulado)
    {
        std::cout << "Este producto ya fue anulado.\n";
        return;
    }
    int op;
    std::cout << "¿Estás seguro de querer anular el producto \"" << producto_actual->producto.nombre_producto << "\"?\n";
    verificarModificacionEnProducto(op);
    if (op == 1)
    {
        producto_actual->producto.anulado = !producto_actual->producto.anulado;
        std::cout << "Producto anulado exitosmanete. \n";
        return;
    }
    std::cout << "Error al ingresar un numero valido.\n";
    std::cout << "Volviendo al menú anterior.\n";
    return;
}
void activarProducto(lista_Producto *&lista_producto)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    if (!producto_actual->producto.anulado)
    {
        std::cout << "Este producto ya está activado.\n";
        return;
    }
    int op;
    std::cout << "¿Estás seguro de querer volver a activar el producto \"" << producto_actual->producto.nombre_producto << "\"?\n";
    verificarModificacionEnProducto(op);
    if (op == 1)
    {
        producto_actual->producto.anulado = !producto_actual->producto.anulado;
        std::cout << "Producto activado exitosmanete. \n";
        return;
    }
    if (op != 2)
        std::cout << "Error al ingresar un numero valido.\n";
    std::cout << "Volviendo al menú anterior.\n";
    return;
}
#endif