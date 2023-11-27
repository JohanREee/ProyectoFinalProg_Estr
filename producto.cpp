#include "structs.h"

void agregarProductoEnLista(lista_Producto *&producto, char *input)
{
    lista_Producto *nuevo_producto = new lista_Producto();
    nuevo_producto->producto.id_producto = ++conteo_id_producto;
    gotoxy(2,6);
    std::cout << "\tIngresar el nombre del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.nombre_producto, input);
    std::cout << "\tIngresar descripción del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.descripcion_producto, input);
    std::cout << "\tIngresar cantidad en existencia del producto: ";
    nuevo_producto->producto.existencia_cantidad = soloEnteros();
    if (nuevo_producto->producto.existencia_cantidad != 0)
    {
        agregarPrimerLote(nuevo_producto);
    }
    int op;
    while (true)
    {
        std::cout << "\t¿Desea estandarizar la cantidad mínima de este producto en 10?\n";
        std::cout << "\t1. Sí\n";
        std::cout << "\t2. No\n";
        std::cout << "\tIngresar número: ";
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
                std::cout << "\tDigite la cantidad mínima para este producto: ";
                nuevo_producto->producto.minima_cantidad = soloEnteros();
                if (nuevo_producto->producto.minima_cantidad >= 0)
                {
                    break;
                }
                std::cout << "\tLa cantidad no puede ser menor a 0.\nIntente de nuevo.\n";
            }
            break;
        }
        else
        {
            std::cout << "\tNumero incorrecto.\nIntente de nuevo.\n";
        }
    }
    calcularCostoVentaTotal(nuevo_producto);
    guardarProductoEnLista(lista_producto, nuevo_producto);
    escribirProductosEnArchivoJSON(lista_producto);
    std::cout << "\tProducto ingresado exitosamente.\n";
    std::cout << "\tEl ID del producto es: " << nuevo_producto->producto.id_producto << "\n";

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
    gotoxy(2,6);
    std::cout << "\tDigite el ID del producto que desea buscar: ";
    id_producto = soloEnteros();
    producto_actual = buscarProducto(lista_producto, id_producto);
    if (producto_actual == NULL)
    {
        std::cout << "\tEl producto no fue encontrado o validado.\n";
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
                std::cout << "\tEl producto \"" << aux->producto.nombre_producto << "\" ha sido anulado anteriormente del sistema. ¿Deseas continuar con tu acción?\n";
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
    pausarYLimpiar();
    marco();
    gotoxy(2,6);
    std::cout << "\tNombre: " << producto->producto.nombre_producto << "\n";
    std::cout << "\tDescripcion: " << producto->producto.descripcion_producto << "\n"; // Controlar el flujo
    std::cout << "\tCantidad en existencia: " << producto->producto.existencia_cantidad << "\n";
    std::cout << "\tCantidad mínima de existencia: " << producto->producto.minima_cantidad << "\n";
    std::cout << "\tCosto de venta total en Córdobas: C$" << producto->producto.costo_de_venta_total << "\n";;
    if (producto->producto.anulado)
    {
        std::cout << "\n\tEl producto está anulado\n";
    }
    else
    {
        std::cout << "\n\tEl producto no está anulado\n";
    }
    return;
}

void mostrarTodosProducto(lista_Producto *lista_producto)
{
    int op;
    std::cout << "\tADVERTENCIA. ¿Desea mostrar los productos anulados?\n";
    verificarModificacionEnProducto(op);
    if (op == 1)
    {
        mostrarProductos(lista_producto, true);
    }
    else if (op == 2)
    {
        mostrarProductos(lista_producto, false);
    }
    else
    {
        std::cout << "\tValor inválido ingresado.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
    }
}

void mostrarProductos(lista_Producto *producto, bool show)
{ // mostrarProducto
    lista_Producto *aux = producto;
    while (aux != NULL)
    {
        if (!producto->producto.anulado || show)
        {
            gotoxy(2,6);
            std::cout << "\tNombre del producto: " << producto->producto.nombre_producto << "\n";
            std::cout << "\tDescripción del producto: " << producto->producto.descripcion_producto << "\n";
            std::cout << "\tCantidad en existencia:" << producto->producto.existencia_cantidad << "\n";
            std::cout << "\tCantidad mínima de existencia: " << producto->producto.minima_cantidad << "\n";
            std::cout << "\tCosto de venta total en Córdobas: C$" << producto->producto.costo_de_venta_total << "\n";
            if (producto->producto.anulado)
            {
                std::cout << "\t\nEl producto está anulado\n";
            }
            else
            {
                std::cout << "\t\nEl producto no está anulado\n";
            }
        }
        aux = aux->siguiente;
    }
}

void modificarProducto(lista_Producto *&lista_producto)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    gotoxy(2,6);
    std::cout << "\tSeleccione el campo de \"" << producto_actual->producto.nombre_producto << "\" que desea modificar\n";
    std::cout << "\t1. Nombre\n";
    std::cout << "\t2. Descripción\n";
    std::cout << "\t3. Cantidad minima en existencia.\n";
    std::cout << "\tIngresar número: ";
    int op = soloEnteros();
    int porcentaje_ganancia = 0;
    switch (op)
    {
    case 1:
        char *nombre;
        std::cout << "\tDigite el nuevo nombre del producto: ";
        agregarElementoPuntero(nombre, input);
        std::cout << "\tNombre del producto \"" << producto_actual->producto.nombre_producto << "\" ha sido cambiado a \"" << nombre << "\" exitosamente.\n";
        // Lineas para modificar un dato.
        delete[] producto_actual->producto.nombre_producto;                       // Primero se borra la memoria dinamica
        producto_actual->producto.nombre_producto = new char[strlen(nombre) + 1]; // Se reasigna con el tamano del char ingresado con anterioridad (char *nombre)
        strcpy(producto_actual->producto.nombre_producto, nombre);                // se copia el contenido de nombre a el puntero de la estructura que debe contener el nombre real
        //
        delete[] nombre; // Se elimina la memoria dinamica temporal
        escribirProductosEnArchivoJSON(lista_producto);
        break;
    case 2:
        char *descripcion;
        std::cout << "\tDigite la nueva descripcion del producto \"" << producto_actual->producto.nombre_producto << "\": ";
        agregarElementoPuntero(descripcion, input);
        std::cout << "\tDescripcio\tn anterior: " << producto_actual->producto.descripcion_producto << "\n";
        std::cout << "\tDescripcion nueva: " << descripcion << "\n";
        delete[] producto_actual->producto.descripcion_producto;
        producto_actual->producto.descripcion_producto = new char[strlen(descripcion) + 1];
        strcpy(producto_actual->producto.descripcion_producto, descripcion);
        delete[] descripcion;
        escribirProductosEnArchivoJSON(lista_producto);
        break;
    case 3:
        int cantidad;
        std::cout << "\tIngrese la nueva cantidad minima para el producto\"" << producto_actual->producto.nombre_producto << "\": ";
        cantidad = soloEnteros();
        if (cantidad >= 0)
        {
            std::cout << "\tLa cantidad minima para el producto \"" << producto_actual->producto.nombre_producto << "\"";
            std::cout << " de " << producto_actual->producto.minima_cantidad << ".";
            std::cout << "\n\tHa sido reemplazada por: " << cantidad << "\n";
            producto_actual->producto.minima_cantidad = cantidad;
            break;
        }
        std::cout << "\tLa cantidad minima no puede ser menor a 0.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        escribirProductosEnArchivoJSON(lista_producto);
        break;
    default:
        std::cout << "\tHas digitado un valor invalido.\n";
        std::cout << "\tSerás enviado al menú anterior.\n";
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
        std::cout << "\tEste producto ya fue anulado.\n";
        return;
    }
    int op;
    std::cout << "\t¿Estás seguro de querer anular el producto \"" << producto_actual->producto.nombre_producto << "\"?\n";
    verificarModificacionEnProducto(op);
    if (op == 1)
    {
        producto_actual->producto.anulado = !producto_actual->producto.anulado;
        std::cout << "\tProducto anulado exitosamente. \n";
        escribirProductosEnArchivoJSON(lista_producto);
        return;
    }
    if (op != 2)
    {
        std::cout << "\tError al ingresar un numero valido.\n";
    }
    std::cout << "\tVolviendo al menú anterior.\n";
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
        std::cout << "\tEste producto ya está activado.\n";
        return;
    }
    int op;
    std::cout << "\t¿Estás seguro de querer volver a activar el producto \"" << producto_actual->producto.nombre_producto << "\"?\n";
    verificarModificacionEnProducto(op);
    if (op == 1)
    {
        producto_actual->producto.anulado = !producto_actual->producto.anulado;
        std::cout << "\tProducto activado exitosmanete. \n";
        escribirProductosEnArchivoJSON(lista_producto);
        return;
    }
    if (op != 2)
    {
        std::cout << "\tError al ingresar un numero valido.\n";
    }
    std::cout << "\tVolviendo al menú anterior.\n";
    return;
}
void calcularCostoVentaTotal(lista_Producto *&producto_actual)
{
    Lista_Ano *ano_actual = producto_actual->producto.anos_producto;
    producto_actual->producto.costo_de_venta_total = 0;
    while (ano_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL)
            {
                if (!lote_actual->lote.validacion)
                {
                    producto_actual->producto.costo_de_venta_total += lote_actual->lote.costo_venta;
                }
                lote_actual = lote_actual->siguiente;
            }
        }
        ano_actual = ano_actual->siguiente;
    }
}
void asignarCostoVentaACadaLote(lista_Producto *&producto_actual)
{
    Lista_Ano *ano_actual = producto_actual->producto.anos_producto;
    while (ano_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL)
            {
                lote_actual->lote.costo_venta = (lote_actual->lote.precio_producto * lote_actual->lote.cantidad_de_producto);
                lote_actual->lote.costo_venta += (lote_actual->lote.costo_venta * producto_actual->producto.porcentaje_ganancia);
                lote_actual = lote_actual->siguiente;
            }
        }
        ano_actual = ano_actual->siguiente;
    }
}