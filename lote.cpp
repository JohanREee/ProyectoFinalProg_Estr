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

void registroDeInformacionLote(Lote &lote_actual)
{
    while (true) // Ingresar precio actual de producto
    {
        std::cout << "Ingrese el precio actual del producto en Córdobas: ";
        lote_actual.precio_producto = soloFlotantes();
        if (lote_actual.precio_producto != 0)
        {
            break;
        }
        std::cout << "Error al ingresar el precio. Vuelve a intentarlo.\n";
        pausar();
    }
    std::cout << "Ingrese la cantidad del producto: ";
    lote_actual.cantidad_de_producto = soloEnteros();
}
char *generarIdLote(int dia, int mes, int año, Informacion_Mes *mes_actual, Producto producto_actual)
{
    int incremental = mes_actual->lotes_cantidad + 1;
    sprintf(input, "%d%02d%02d%d%d", producto_actual.id_producto, dia, mes, año % 100, incremental); // 10811231 //1 2 3 4 6
    char *id_total = new char[strlen(input) + 1];
    strcpy(id_total, input);
    input[0] = '\0';
    return id_total;
}

void agregarPrimerLote(lista_Producto *&producto)
{
    // Estructura Lista_Año
    Lista_Año *año_actual = new Lista_Año();
    año_actual->siguiente = NULL;
    int año = obtenerAño();
    año_actual->año_producto.año = año;
    int mes = obtenerMes();
    Informacion_Mes *mes_actual = &año_actual->año_producto.producto[mes - 1];
    int dia = obtenerDia();
    // Estructura cola_Lote dentro de Información_mes[mes] dentro de Año_Producto dentro de Lista_Año
    cola_Lote *nuevo_lote = new cola_Lote; // 4   01 02 03
    nuevo_lote->siguiente = NULL;
    char *id_lote = generarIdLote(dia, mes, año, mes_actual, producto->producto);
    nuevo_lote->lote.id_lote = new char[strlen(id_lote) + 1];
    strcpy(nuevo_lote->lote.id_lote, id_lote);
    delete[] id_lote;
    nuevo_lote->lote.ingreso_fecha = {dia, mes, año};
    int añoe, mese, diae;
    while (true)
    // bool ingresarFechaExpiracion(int año, int mes, int dia);
    {
        std::cout << "\nIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &diae, &mese, &añoe);
        if (ingresarFechaExpiracion(año, mes, dia, añoe, mese, diae))
        {
            nuevo_lote->lote.expiracion_fecha = {diae, mese, añoe};
            break;
        }
        std::cout << "Error al ingresar la fecha. Vuelve a intentarlo.\n";
        limpiarBuffer();
        pausar();
    }
    while (true) // Ingresar precio actual de producto
    {
        std::cout << "Ingrese el precio actual del producto en Córdobas: ";
        nuevo_lote->lote.precio_producto = soloFlotantes();
        if (nuevo_lote->lote.precio_producto != 0)
        {
            break;
        }
        std::cout << "Error al ingresar el precio. Vuelve a intentarlo.\n";
        pausar();
    }
    // Actualizar la existencia actual con lo puesto en el último lote
    nuevo_lote->lote.cantidad_de_producto += producto->producto.existencia_cantidad;
    std::cout << "El ID del lote es: " << nuevo_lote->lote.id_lote << "\n";
    // Guardar el nuevo lote en la cola de todos los lotes
    guardarLoteEnProducto(mes_actual, nuevo_lote);
    crearMovimiento(movimientos, producto, nuevo_lote, true, nuevo_lote->lote.cantidad_de_producto);
    // void crearMovimiento(lista_Movimiento *&movimientos, lista_Producto *producto_actual, cola_Lote *lote_actual, bool band = false, int cantidad)
    //  Actualizar la cantidad de lotes de toda la cola
    mes_actual->lotes_cantidad++;
    producto->producto.años_producto = año_actual;
}

void agregarLotesAProducto(lista_Producto *&producto)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
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
            band = true;
        }
        Informacion_Mes *mes_actual = &año_actual->año_producto.producto[mes - 1];
        // Estructura cola_Lote dentro de Información_mes[mes] dentro de Año_Producto dentro de Lista_Año
        cola_Lote *nuevo_lote = new cola_Lote; // 4   01 02 03
        nuevo_lote->siguiente = NULL;
        char *id_lote = generarIdLote(dia, mes, año, mes_actual, producto_actual->producto);
        nuevo_lote->lote.id_lote = new char[strlen(id_lote) + 1];
        strcpy(nuevo_lote->lote.id_lote, id_lote);
        delete[] id_lote;
        nuevo_lote->lote.ingreso_fecha = {dia, mes, año};
        int añoe, mese, diae;
        while (true) // Ingresar fecha de expiracion del producto
        {
            std::cout << "\nIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
            scanf("%2d/%2d/%4d", &diae, &mese, &añoe);
            if (ingresarFechaExpiracion(año, mes, dia, añoe, mese, diae))
            {
                nuevo_lote->lote.expiracion_fecha = {diae, mese, añoe};
                break;
            }
            std::cout << "Error al ingresar la fecha. Vuelve a intentarlo.\n";
            limpiarBuffer();
            system("pause");
        }
        registroDeInformacionLote(nuevo_lote->lote);
        producto_actual->producto.existencia_cantidad += nuevo_lote->lote.cantidad_de_producto;
        guardarLoteEnProducto(mes_actual, nuevo_lote);
        // Actualizar la cantidad de lotes de toda la cola
        mes_actual->lotes_cantidad++;
        if (band)
        {
            guardarProductoEnLista(lista_producto, producto_actual);
        }
        crearMovimiento(movimientos, producto, nuevo_lote, true, nuevo_lote->lote.cantidad_de_producto);
        std::cout << "\nLote agregado con exito.\n";
        std::cout << "El ID del lote es: " << nuevo_lote->lote.id_lote << "\n";
        std::cout << "¿Deseas ingresar otro lote para este producto? \n";
        int op;
        verificarModificacionEnProducto(op);
        if (op == 1)
        {
            continue;
        }
        else if (op != 2)
        {
            std::cout << "Valor invalido. Volviendo al menú anterior.\n";
        }
        break;
    }
    return;
}
void guardarLoteEnProducto(Informacion_Mes *mes_actual, cola_Lote *&lote_lista)
{
    if (mes_actual->lotes == NULL)
    {
        // Si no hay lotes para este mes, el nuevo lote será el primero
        mes_actual->lotes = lote_lista;
    }
    else
    {
        // Si ya hay otros lotes, agregar el nuevo lotee al final de la cola
        cola_Lote *aux_lote = mes_actual->lotes;
        while (aux_lote->siguiente != NULL) // Bucle para encontrar el penúltimo
        {
            aux_lote = aux_lote->siguiente;
        }
        aux_lote->siguiente = lote_lista; // Hacer que el penúltimo apunte al nuevo, que ahora es el último
    }
}
bool ingresarLote(lista_Producto *producto_actual, cola_Lote *&lote_actual)
{
    char *id_lote;
    std::cout << "Para el producto \"" << producto_actual->producto.nombre_producto << "\", Digite el ID de lote que desea buscar: ";
    agregarElementoPuntero(id_lote, input);
    lote_actual = obtenerLote(producto_actual, id_lote);
    delete[] id_lote;
    if (lote_actual == NULL)
    {
        std::cout << "Lote no encontrado.\n";
        return false;
    }
    return true;
}

void buscarLote(lista_Producto *lista_producto)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    cola_Lote *lote_actual = NULL;
    if (!ingresarLote(producto_actual, lote_actual))
    {
        return;
    }
    mostrarLotesDeProducto(lote_actual);
}

cola_Lote *obtenerLote(lista_Producto *producto, char *id_lote)
{
    Lista_Año *año_actual = producto->producto.años_producto;
    while (año_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL)
            {
                if (strcmp(lote_actual->lote.id_lote, id_lote) == 0)
                {
                    if (lote_actual->lote.validacion)
                    {
                        int op;
                        std::cout << "\nEste lote fue eliminado por el sistema.\n";
                        std::cout << "Motivo:";
                        (lote_actual->lote.motivo == 1) ? std::cout << " Fecha de caducidad.\n" : std::cout << " Stock en 0.\n";
                        std::cout << "¿Deseas continuar con tu accion?\n";
                        std::cout << "1.Sí\n2.No";
                        std::cout << "\nIngresar numero: ";
                        op = soloEnteros();
                        if (op != 1) // op es 2 por ejemplo
                        {
                            if (op != 2)
                            {
                                std::cout << "Error al ingresar el numero.\n";
                            }
                            return NULL;
                        }
                    }
                    return lote_actual;
                }
                lote_actual = lote_actual->siguiente;
            }
        }
        año_actual = año_actual->siguiente;
    }
    return NULL;
}
void mostrarLotesDeProducto(cola_Lote *cola)
{
    std::cout << "ID del lote: " << cola->lote.id_lote << "\n";
    std::cout << "Fecha de ingreso del lote: " << cola->lote.ingreso_fecha.dia << "/" << cola->lote.ingreso_fecha.mes << "/" << cola->lote.ingreso_fecha.año << "\n";
    std::cout << "Fecha de expiración del lote: " << cola->lote.expiracion_fecha.dia << "/" << cola->lote.expiracion_fecha.mes << "/" << cola->lote.expiracion_fecha.año << "\n";
    std::cout << "Precio del producto en Córdobas en este lote: C$" << cola->lote.precio_producto << "\n";
    std::cout << "Cantidad del producto ingresada en este lote: " << cola->lote.cantidad_de_producto << "\n\n";
    (cola->lote.validacion) ? std::cout << "Lote anulado\n" : std::cout << "Lote activo\n";
}

void mostrarTodosLotesDeProducto(lista_Producto *lista_producto)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    int op;
    std::cout << "ADVERTENCIA. ¿Deseas mostrar los lotes anulados por el sistema? por defecto, no se mostraran.\n";
    verificarModificacionEnProducto(op);

    std::cout << "Mostrando todos los lotes del producto " << producto_actual->producto.nombre_producto << "...\n";
    Lista_Año *año_actual = producto_actual->producto.años_producto;
    while (año_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL)
            {
                if (op != 1) // si por ejemplo el valor es 2
                {
                    if (!lote_actual->lote.validacion) // Lote valido
                    {
                        asociarMesConNumero(i);
                        std::cout << "\n";
                        mostrarLotesDeProducto(lote_actual);
                        std::cout << "\n\n";
                    }
                }
                else
                {
                    asociarMesConNumero(i);
                    std::cout << "\n";
                    mostrarLotesDeProducto(lote_actual);
                    std::cout << "\n\n";
                }
                lote_actual = lote_actual->siguiente;
            }
        }
        año_actual = año_actual->siguiente;
    }
    return;
}

void mostrarTodosLotesDeTodosProductos(lista_Producto *lista_producto)
{
    lista_Producto *aux = lista_producto;
    int op;
    std::cout << "ADVERTENCIA. ¿Deseas mostrar los lotes anulados por el sistema? por defecto, no se mostraran.\n";
    verificarModificacionEnProducto(op);
    while (aux != NULL)
    {
        std::cout << "Mostrando todos los lotes del producto " << aux->producto.nombre_producto << "...\n";
        Lista_Año *año_actual = aux->producto.años_producto;
        while (año_actual != NULL)
        {
            for (int i = 0; i < 12; i++)
            {
                Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
                cola_Lote *lote_actual = mes_actual->lotes;
                while (lote_actual != NULL)
                {
                    if (op != 1) // No mostrar
                    {
                        if (!lote_actual->lote.validacion) // Lote valido
                        {
                            asociarMesConNumero(i);
                            std::cout << "\n";
                            mostrarLotesDeProducto(lote_actual);
                            std::cout << "\n\n";
                        }
                    }
                    else
                    {
                        asociarMesConNumero(i);
                        std::cout << "\n";
                        mostrarLotesDeProducto(lote_actual);
                        std::cout << "\n\n";
                    }
                    lote_actual = lote_actual->siguiente;
                }
            }
            año_actual = año_actual->siguiente;
        }
        std::cout << "\nFin de todos los lotes de \"" << aux->producto.nombre_producto << "\".\n";
        aux = aux->siguiente;
    }
    return;
}

void modificarLoteDeProducto(lista_Producto *&lista_producto)
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    cola_Lote *lote_actual = NULL;
    if (!ingresarLote(producto_actual, lote_actual))
    {
        return;
    }
    int op, añoe, mese, diae;
    int dia = obtenerDia(), mes = obtenerMes(), año = obtenerAño();
    std::cout << "Seleccione el campo del lote " << lote_actual->lote.id_lote << " que desea modificar: \n";
    std::cout << "1. Fecha de expiración\n";
    std::cout << "2. Precio del producto\n";
    std::cout << "3. Cantidad del producto\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros();
    int opt;
    switch (op)
    {
    case 1:
        verificarModificacionEnLote(opt);
        if (opt != 1)
        {
            if (opt != 2)
            {
                std::cout << "Error al ingresar el numero.\n";
            }
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        std::cout << "\nIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &diae, &mese, &añoe);
        if (ingresarFechaExpiracion(año, mes, dia, añoe, mese, diae))
        {
            Fecha fecha = lote_actual->lote.expiracion_fecha;

            std::cout << "La fecha de expiración de este lote \"" << fecha.dia << "/" << fecha.mes << "/" << fecha.año << "\" ha sido reemplazada por ";
            std::cout << "\"" << diae << "/" << mese << "/" << añoe << "\"\n";
            lote_actual->lote.expiracion_fecha = {diae, mese, añoe};
            break;
        }
        std::cout << "Error al ingresar la fecha.\n";
        std::cout << "Volviendo al menu anterior.\n";
        limpiarBuffer();
        break;
    case 2:
        verificarModificacionEnLote(opt);
        if (opt != 1)
        {
            if (opt != 2)
            {
                std::cout << "Error al ingresar el numero.\n";
            }
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        double precio;
        std::cout << "Ingrese el nuevo precio del producto para este lote: ";
        precio = soloFlotantes();
        if (precio > 0)
        {
            std::cout << "El precio de \"" << lote_actual->lote.cantidad_de_producto << " \"ha sido reemplazado por \"" << precio << "\" para este lote.\n";
            lote_actual->lote.cantidad_de_producto = precio;
            break;
        }
        else
        {
            std::cout << "El precio no puede ser 0.\n";
        }
        std::cout << "Volviendo al menu anterior.\n";
        break;
    case 3:
        verificarModificacionEnLote(opt);
        if (opt != 1)
        {
            if (opt != 2)
            {
                std::cout << "Error al ingresar el numero.\n";
            }
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        int cantidad_producto;
        int opti;
        std::cout << "Cantidad actual del lote: " << lote_actual->lote.cantidad_de_producto << "\n";
        std::cout << "¿Desea ingresar o eliminar una cantidad?\n";
        std::cout << "1. Ingresar\n2. Eliminar\n";
        std::cout << "Ingresar número: ";
        opti = soloEnteros();
        if (opti != 1 || opti != 2)
        {
            std::cout << "Error al ingresar el numero.\n";
            std::cout << "Volviendo al menú anterior.\n";
            break;
        }
        std::cout << "Ingrese la cantidad a ";
        (opti == 1) ? std::cout << "ingresar " : std::cout << "eliminar ";
        std::cout << "para este lote: ";
        cantidad_producto = soloEnteros();
        if (cantidad_producto != 0)
        {
            if (opti == 2)
            {
                if (lote_actual->lote.cantidad_de_producto >= cantidad_producto)
                {
                    cantidad_producto *= -1;
                }
                else
                {
                    std::cout << "La cantidad ingresada no puede ser mayor que la cantidad del lote.\n";
                    break;
                }
            }
            std::cout << "Cantidad ";
            (opti == 1) ? std::cout << "ingresada " : std::cout << "eliminada ";
            std::cout << "del lote " << lote_actual->lote.id_lote << "\n";
            std::cout << "Cambios reflejados en la cantidad en existencia del producto.\n";
            lote_actual->lote.cantidad_de_producto += cantidad_producto;
            producto_actual->producto.existencia_cantidad += cantidad_producto;
            break;
        }
        std::cout << "La cantidad ingresada no puede ser 0.\n";
        std::cout << "Volviendo al menú anterior.\n";
        break;
    default:
        std::cout << "Has digitado un valor invalido.\n";
        std::cout << "Serás enviado al menú anterior.\n";
        break;
    }
    return;
}
void registroDeVentas()
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    cola_Lote *lote_actual = NULL;
    if (!ingresarLote(producto_actual, lote_actual))
    {
        return;
    }
    int cantidad;
    std::cout << "Cantidad actual del lote " << lote_actual->lote.id_lote << ": " << lote_actual->lote.cantidad_de_producto;
    std::cout << "\nIngrese la cantidad que vendió en el lote " << lote_actual->lote.id_lote << ": ";
    cantidad = soloEnteros();
    if (lote_actual->lote.cantidad_de_producto < cantidad || cantidad == 0)
    {
        (cantidad == 0) ? std::cout << "La cantidad ingresada no puede ser 0.\n" : std::cout << "La cantidad ingresada no puede ser mayor que la cantidad actual del lote.\n";
        std::cout << "Volviendo al menú anterior.\n";
        return;
    }
    std::cout << "Cantidad registrada exitosamente.\n";
    std::cout << "Cambios reflejados en la cantidad en existencia del producto.\n";
    lote_actual->lote.cantidad_de_producto -= cantidad;
    producto_actual->producto.existencia_cantidad -= cantidad;
    crearMovimiento(movimientos, producto_actual, lote_actual, false, cantidad);
}
void eliminarLoteDeProducto()
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    int op;
    char *id_lote = NULL;
    std::cout << "Para el producto \"" << producto_actual->producto.nombre_producto << "\", Digite el ID de lote que desea buscar: ";
    agregarElementoPuntero(id_lote, input);
    std::cout << "¿Estás seguro de que quieres borrar este lote permanentemente?\n";
    verificarModificacionEnProducto(op);
    if (op != 1)
    {
        if (op != 2)
        {
            std::cout << "Error al ingresar el número.\n";
        }
        std::cout << "Volviendo al menú anterior.\n";
        delete[] id_lote;
        return;
    }
    borrarLote(producto_actual, id_lote);
    delete[] id_lote;
}
void borrarLote(lista_Producto *&producto_actual, char *id_lote) // eliminación permanente
{
    lista_Producto *aux_p = producto_actual;
    Lista_Año *año_actual = aux_p->producto.años_producto;
    while (año_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            cola_Lote *anterior = NULL;
            while (lote_actual != NULL && strcmp(lote_actual->lote.id_lote, id_lote) != 0)
            {
                anterior = lote_actual;
                lote_actual = lote_actual->siguiente;
            }
            if (lote_actual != NULL)
            {
                if (anterior == NULL && strcmp(lote_actual->lote.id_lote, id_lote) == 0)
                {
                    mes_actual->lotes = mes_actual->lotes->siguiente;
                    delete[] lote_actual->lote.id_lote;
                    delete lote_actual;
                    std::cout << "Lote eliminado.\n";
                    return;
                }
                else if (anterior != NULL && strcmp(lote_actual->lote.id_lote, id_lote) == 0)
                {
                    anterior->siguiente = lote_actual->siguiente;
                    delete[] lote_actual->lote.id_lote;
                    delete lote_actual;
                    std::cout << "Lote eliminado.\n";
                    return;
                }
            }
        }
        año_actual = año_actual->siguiente;
    }
    std::cout << "Lote no encontrado.\n";
}
void vencerLotes(lista_Producto *&producto)
{
    lista_Producto *aux = producto;
    int dia = obtenerDia();
    int mes = obtenerMes();
    int año = obtenerAño();

    while (aux != NULL)
    {
        if (!aux->producto.anulado)
        {
            Lista_Año *año_actual = aux->producto.años_producto;
            while (año_actual != NULL)
            {

                for (int i = 0; i < 12; i++)
                {
                    Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
                    cola_Lote *lote_actual = mes_actual->lotes;
                    while (lote_actual != NULL)
                    {

                        bool fecha = comprobarEstadoFecha(dia, mes, año, lote_actual); // true = fecha valida, false = fecha menor a la actual
                        if (!fecha)                                                    // Anula por caducidad
                        {                                                              // La fecha de expiracion del lote esta antes que la actual
                            if (!lote_actual->lote.validacion)                         // Si el lote es valido...
                            {
                                lote_actual->lote.validacion = !lote_actual->lote.validacion;
                                aux->producto.existencia_cantidad -= lote_actual->lote.cantidad_de_producto;
                                lote_actual->lote.motivo = 1;
                                crearMovimiento(movimientos, aux, lote_actual, false, lote_actual->lote.cantidad_de_producto);
                            }
                        }
                        else if (lote_actual->lote.cantidad_de_producto == 0) // Anula por cantidad
                        {
                            if (!lote_actual->lote.validacion)
                            {
                                lote_actual->lote.validacion = !lote_actual->lote.validacion;
                                lote_actual->lote.motivo = 2;
                            }
                        }
                        else if ((fecha && lote_actual->lote.cantidad_de_producto > 0) && (lote_actual->lote.validacion))
                        { // Reactiva lote si la fecha es valida y la cantidad es mayor a 0, si el lote ya estaba anulado
                            lote_actual->lote.validacion = !lote_actual->lote.validacion;
                            aux->producto.existencia_cantidad += lote_actual->lote.cantidad_de_producto;
                            lote_actual->lote.motivo = 0;
                            crearMovimiento(movimientos, aux, lote_actual, true, lote_actual->lote.cantidad_de_producto);
                            // Se reactiva
                        }
                        lote_actual = lote_actual->siguiente;
                    }
                }
                año_actual = año_actual->siguiente;
            }
        }

        aux = aux->siguiente;
    }
}

#endif