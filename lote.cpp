#include "structs.h"
#include "complemento.cpp"

/*void agregarLotesAProducto(cola_Lote *&cola);
void mostrarLotesDeProducto(cola_Lote *cola, char *id_producto);
void mostrarLotesDeTodosProductos(cola_Lote *cola);
void buscarLote(cola_Lote *cola, char *id_producto);
void modificarLoteDeProducto(cola_Lote *&cola);
void eliminarLoteYMovimientoDeProducto(cola_Lote *&cola_lote, lista_Movimiento *&cola_movimiento, char *id_producto, char *codigo_acceso);
void eliminarLotesYMovimientosTodoDeProducto(cola_Lote *&cola_lote, lista_Movimiento *&cola_movimiento, char *id_producto, char *codigo_acceso);
*/

#ifndef lot
#define lot

char *generarIdLote(int dia, int mes, int año, Informacion_Mes *mes_actual)
{
    char id[20];
    int incremental = mes_actual->lotes_cantidad + 1;
    sprintf(id, "%d%02d%02d%d%d", conteo_id_producto, dia, mes, año % 100, incremental); // 10811231 //1 2 3 4 6
    char *id_total = new char[strlen(id) + 1];
    strcpy(id_total, id);
    return id_total;
}

void agregarPrimerLote(lista_Producto *&producto)
{
    // Estructura Lista_Año
    Lista_Año *año_actual = new Lista_Año();
    año_actual->siguiente = NULL;
    Lista_Año *lista_año = producto->producto.años_producto;
    int año = obtenerAño();
    año_actual->año_producto.año = año;
    int mes = obtenerMes();
    Informacion_Mes *mes_actual = &año_actual->año_producto.producto[mes - 1];
    int dia = obtenerDia();
    Lote lote_actual;
    // Estructura cola_Lote dentro de Información_mes[mes] dentro de Año_Producto dentro de Lista_Año
    cola_Lote *nuevo_lote = new cola_Lote; // 4   01 02 03
    char *id_lote = generarIdLote(dia, mes, año, mes_actual);
    lote_actual.id_lote = new char[strlen(id_lote) + 1];
    strcpy(lote_actual.id_lote, id_lote);
    delete[] id_lote;
    lote_actual.ingreso_fecha = {dia, mes, año};
    int añoe, mese, diae;
    while (true)
    {
        std::cout << "\nIngrese la fecha de expiración del lote en formato dd/mm/yy: ";
        scanf("%2d/%2d/%2d", &diae, &mese, &añoe);
        if (!((diae < 1 || diae > 31) || (mese < 1 || mese > 12) || (añoe < 1)))
        {
            lote_actual.expiracion_fecha = {diae, mese, añoe};
            break;
        }
        std::cout << "Error al ingresar la fecha. Vuelve a intentarlo.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        std::cout << "Ingrese el precio actual del producto: ";
        if (std::cin >> lote_actual.precio_producto)
        {
            if (lote_actual.precio_producto > 0)
                break;
        }
        std::cout << "Error al ingresar el precio. Vuelve a intentarlo.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        system("pause");
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Actualizar la existencia actual con lo puesto en el último lote
    lote_actual.cantidad_de_producto = producto->producto.existencia_cantidad;
    // Guardar el nuevo lote en la cola de todos los lotes
    nuevo_lote->lote = lote_actual;
    nuevo_lote->siguiente = NULL;

    if (mes_actual->lotes == NULL)
    {
        // Si no hay lotes para este mes, el nuevo lote será el primero
        mes_actual->lotes = nuevo_lote;
    }
    else
    {
        // Si ya hay otros lotes, agregar el nuevo ltoe al final de la cola
        cola_Lote *aux_lote = mes_actual->lotes;
        while (aux_lote->siguiente != NULL) // Bucle para encontrar el penúltimo
        {
            aux_lote = aux_lote->siguiente;
        }
        aux_lote->siguiente = nuevo_lote; // Hacer que el penúltimo apunte al nuevo, que ahora es el último
    }
    // Actualizar la cantidad de lotes de toda la cola
    mes_actual->lotes_cantidad++;
    // Agregar el año actual en la cabecera de la lista de todos los años
    año_actual->siguiente = producto->producto.años_producto;
    producto->producto.años_producto = año_actual;
}
void agregarLotesAProducto(lista_Producto *&producto)
{
    int id_producto;
    std::cout << "Ingrese el id del producto: ";
    id_producto = soloEnteros(id_producto);
    fflush(stdin);
    lista_Producto *producto_actual = buscarProducto(producto, id_producto);
    if (producto_actual == NULL)
    {
        std::cout << "El producto no fue encontrado.\n";
        return;
    }
    while (true)
    {
        int dia = obtenerDia();
        int mes = obtenerMes();
        int año = obtenerAño();
        bool band = false;
        Lista_Año *año_actual = buscarAñoActualDeProducto(producto_actual, año);
        if (año_actual == NULL)
        {
            año_actual = new Lista_Año();
            año_actual->siguiente = NULL;
            bool band = true;
        }
        Informacion_Mes *mes_actual = &año_actual->año_producto.producto[mes - 1];
        Lote lote_actual;
        // Estructura cola_Lote dentro de Información_mes[mes] dentro de Año_Producto dentro de Lista_Año
        cola_Lote *nuevo_lote = new cola_Lote; // 4   01 02 03
        char *id_lote = generarIdLote(dia, mes, año, mes_actual);
        lote_actual.id_lote = new char[strlen(id_lote) + 1];
        strcpy(lote_actual.id_lote, id_lote);
        delete[] id_lote;
        lote_actual.ingreso_fecha = {dia, mes, año};
        int añoe, mese, diae;
        while (true)
        {
            std::cout << "\nIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
            scanf("%2d/%2d/%2d", &diae, &mese, &añoe);
            if ((añoe == año) && (mese == mes) && (diae > dia)) // Validar en el mes actual
            {
                if (validarDiaPorMes(añoe, mese, diae))
                {
                    lote_actual.expiracion_fecha = {diae, mese, añoe};
                    break;
                }
            }
            else if ((añoe == año) && (mese > mes))
            {
                if (validarDiaPorMes(añoe, mese, diae))
                {
                    lote_actual.expiracion_fecha = {diae, mese, añoe};
                    break;
                }
            }
            else if (añoe > año)
            {
                if (validarDiaPorMes(añoe, mese, diae))
                {
                    lote_actual.expiracion_fecha = {diae, mese, añoe};
                    break;
                }
            }
            std::cout << "Error al ingresar la fecha. Vuelve a intentarlo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (true)
        {
            std::cout << "Ingrese el precio actual del producto: ";
            if (std::cin >> lote_actual.precio_producto)
            {
                if (lote_actual.precio_producto > 0)
                    break;
            }
            std::cout << "Error al ingresar el precio. Vuelve a intentarlo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        nuevo_lote->lote = lote_actual;
        nuevo_lote->siguiente = NULL;
        if (mes_actual->lotes == NULL)
        {
            // Si no hay lotes para este mes, el nuevo lote será el primero
            mes_actual->lotes = nuevo_lote;
        }
        else
        {
            // Si ya hay otros lotes, agregar el nuevo ltoe al final de la cola
            cola_Lote *aux_lote = mes_actual->lotes;
            while (aux_lote->siguiente != NULL) // Bucle para encontrar el penúltimo
            {
                aux_lote = aux_lote->siguiente;
            }
            aux_lote->siguiente = nuevo_lote; // Hacer que el penúltimo apunte al nuevo, que ahora es el último
        }
        // Actualizar la cantidad de lotes de toda la cola
        mes_actual->lotes_cantidad++;
        if (band)
        {
            Lista_Año *aux = producto_actual->producto.años_producto; // Reservamos el valor original de la lista
            Lista_Año *aux2;
            while (aux != NULL)
            {                         // Comprobamos que aux no apunte a null
                aux2 = aux;           // Reservamos el valor original de aux que por ahora es la llista
                aux = aux->siguiente; // Corre una posición, buscando NULL
            }
            if (aux == producto_actual->producto.años_producto) // Nunca pasó por el while
            {
                producto_actual->producto.años_producto = año_actual;
            }
            else // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
            {
                aux2->siguiente = año_actual;
            }
            año_actual->siguiente = aux; // año_actual apunta a NULL
        }
        std::cout << "\nLote agregado con exito.\n";
        int op;
        std::cout << "¿Desea agregar otro lote para este producto?\n";
        std::cout << "1. Sí\n";
        std::cout << "2. No\n";
        op = soloEnteros(op);
        if (op != 1)
        {
            break;
        }
    }
}

void buscarLote(lista_Producto *producto)
{
    int id_producto;
    std::cout << "Digite el ID del producto para buscar un lote: ";
    id_producto = soloEnteros(id_producto);
    lista_Producto *producto_actual = buscarProducto(lista_producto, id_producto);
    if (producto_actual == NULL)
    {
        std::cout << "Producto no encontrado.\n";
        return;
    }
    char *id_lote;
    std::cout << "Para el producto " << producto_actual->producto.nombre_producto << ", Digite el ID de lote que desea buscar: ";
    agregarElementoPuntero(id_lote, input);
    cola_Lote *lote_actual = obtenerLote(producto_actual, id_lote);
    delete[] id_lote;
    if (lote_actual == NULL)
    {
        std::cout << "Lote no encontrado.\n";
        return;
    }
    mostrarLotesDeProducto(lote_actual);
    // Mostrar el lote
}

cola_Lote *obtenerLote(lista_Producto *producto, char *id_lote)
{
    Lista_Año *año_actual = producto->producto.años_producto;
    while (año_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
            while (mes_actual->lotes != NULL)
            {
                if (strcmp(mes_actual->lotes->lote.id_lote, id_lote) == 0)
                {
                    if (mes_actual->lotes->lote.validacion)
                    {
                        std::cout << "Este lote no cumple con los requerimientos para estar validado.\n";
                        return NULL;
                    }
                    return mes_actual->lotes;
                }
            }
            mes_actual->lotes = mes_actual->lotes->siguiente;
        }
        año_actual = año_actual->siguiente;
    }
    return NULL;
}
/*struct Lote
{
    char *id_lote;
    Fecha ingreso_fecha;
    Fecha expiracion_fecha;
    double precio_producto;
    int cantidad_de_producto;
    bool validacion = false;
};
*/
void mostrarLotesDeProducto(cola_Lote *cola)
{
    std::cout << "ID del lote: " << cola->lote.id_lote << "\n";
    std::cout << "Fecha de ingreso del lote: " << cola->lote.ingreso_fecha.dia << "/" << cola->lote.ingreso_fecha.mes << "/" << cola->lote.ingreso_fecha.año << "\n";
    std::cout << "Fecha de expiración del lote: " << cola->lote.expiracion_fecha.dia << "/" << cola->lote.expiracion_fecha.mes << "/" << cola->lote.expiracion_fecha.año << "\n";
    std::cout << "Precio del producto en Córdobas: C$" << cola->lote.precio_producto << "\n";
    std::cout << "Cantidad del producto ingresada en este lote: " << cola->lote.cantidad_de_producto << "\n";
}
//
void mostrarTodosLotesDeProductos(lista_Producto *producto)
{
    std::cout << "Mostrando todos los lotes del producto " << producto->producto.nombre_producto << "...\n";
    Lista_Año *año_actual = producto->producto.años_producto;
    while (año_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
            while (mes_actual->lotes != NULL)
            {
                mostrarLotesDeProducto(mes_actual->lotes);
                std::cout << "\n\n";
            }
            mes_actual->lotes = mes_actual->lotes->siguiente;
        }
        año_actual = año_actual->siguiente;
    }
    return;
}
#endif