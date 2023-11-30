#include "structs.h"

void asignarMesAEstructura(Informacion_Mes *mes_actual)
{
    for (int i = 1; i < 13; i++)
    {
        mes_actual[i - 1].mes = i;
    }
}
void registroDeInformacionLote(Lote &lote_actual)
{
    while (true) // Ingresar precio actual de producto
    {
        std::cout << "\tIngrese el precio actual del producto en Córdobas: ";
        lote_actual.precio_producto = soloFlotantes();
        if (lote_actual.precio_producto != 0)
        {
            break;
        }
        std::cout << "\tError al ingresar el precio. Vuelve a intentarlo.\n";
        pausar();
    }
    std::cout << "\tIngrese la cantidad del producto: ";
    lote_actual.cantidad_de_producto = soloEnteros();
}
char *generarIdLote(int dia, int mes, int ano, Informacion_Mes *mes_actual, Producto producto_actual)
{
    int incremental = mes_actual->lotes_cantidad + 1;
    sprintf(input, "%d%02d%02d%d%d", producto_actual.id_producto, dia, mes, ano % 100, incremental); // 10811231 //1 2 3 4 6
    char *id_total = new char[strlen(input) + 1];
    strcpy(id_total, input);
    input[0] = '\0';
    return id_total;
}

void agregarPrimerLote(lista_Producto *&producto)
{
    // Estructura Lista_Ano
    Lista_Ano *ano_actual = new Lista_Ano();
    ano_actual->siguiente = NULL;
    int ano = obtenerAno();
    ano_actual->ano_producto.ano = ano;
    int mes = obtenerMes();
    asignarMesAEstructura(ano_actual->ano_producto.producto);
    Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[mes - 1];
    int dia = obtenerDia();
    // Estructura cola_Lote dentro de Información_mes[mes] dentro de Ano_Producto dentro de Lista_Ano
    cola_Lote *nuevo_lote = new cola_Lote; // 4   01 02 03
    nuevo_lote->siguiente = NULL;
    char *id_lote = generarIdLote(dia, mes, ano, mes_actual, producto->producto);
    nuevo_lote->lote.id_lote = new char[strlen(id_lote) + 1];
    strcpy(nuevo_lote->lote.id_lote, id_lote);
    delete[] id_lote;
    nuevo_lote->lote.ingreso_fecha = {dia, mes, ano};
    int anoe, mese, diae;
    while (true)
    // bool ingresarFechaExpiracion(int ano, int mes, int dia);
    {
        std::cout << "\n\tIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &diae, &mese, &anoe);
        if (ingresarFechaExpiracion(ano, mes, dia, anoe, mese, diae))
        {
            nuevo_lote->lote.expiracion_fecha = {diae, mese, anoe};
            break;
        }
        std::cout << "\tError al ingresar la fecha. Vuelve a intentarlo.\n";
        limpiarBuffer();
        pausarYLimpiar();
        marco();
    }
    while (true) // Ingresar precio actual de producto
    {
        std::cout << "\tIngrese el precio actual del producto en Córdobas: ";
        nuevo_lote->lote.precio_producto = soloFlotantes();
        if (nuevo_lote->lote.precio_producto != 0)
        {
            break;
        }
        std::cout << "\tError al ingresar el precio. Vuelve a intentarlo.\n";
        pausar();
    }
    // Actualizar la existencia actual con lo puesto en el último lote
    nuevo_lote->lote.cantidad_de_producto += producto->producto.existencia_cantidad;
    // Actualizar el costo de venta del lote.
    nuevo_lote->lote.costo_venta = nuevo_lote->lote.precio_producto * nuevo_lote->lote.cantidad_de_producto;
    std::cout << "\tEl ID del lote es: " << nuevo_lote->lote.id_lote << "\n";
    // Guardar el nuevo lote en la cola de todos los lotes
    guardarLoteEnProducto(mes_actual, nuevo_lote);
    //  Actualizar la cantidad de lotes de toda la cola
    mes_actual->lotes_cantidad++;
    producto->producto.anos_producto = ano_actual;
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
        int ano = obtenerAno();
        bool band = false;
        Lista_Ano *ano_actual = buscarAnoActualDeProducto(producto_actual, ano);
        if (ano_actual == NULL)
        {
            ano_actual = new Lista_Ano();
            ano_actual->ano_producto.ano = ano;
            ano_actual->siguiente = NULL;
            band = true;
        }
        Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[mes - 1];
        // Estructura cola_Lote dentro de Información_mes[mes] dentro de Ano_Producto dentro de Lista_Ano
        cola_Lote *nuevo_lote = new cola_Lote; // 4   01 02 03
        nuevo_lote->siguiente = NULL;

        char *id_lote = generarIdLote(dia, mes, ano, mes_actual, producto_actual->producto);
        nuevo_lote->lote.id_lote = new char[strlen(id_lote) + 1];
        strcpy(nuevo_lote->lote.id_lote, id_lote);
        delete[] id_lote;

        nuevo_lote->lote.ingreso_fecha = {dia, mes, ano};
        int anoe, mese, diae;
        while (true) // Ingresar fecha de expiracion del producto
        {
            std::cout << "\n\tIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
            scanf("%2d/%2d/%4d", &diae, &mese, &anoe);
            if (ingresarFechaExpiracion(ano, mes, dia, anoe, mese, diae))
            {
                nuevo_lote->lote.expiracion_fecha = {diae, mese, anoe};
                break;
            }
            std::cout << "\tError al ingresar la fecha. Vuelve a intentarlo.\n";
            limpiarBuffer();
            pausar();
        }
        registroDeInformacionLote(nuevo_lote->lote);
        producto_actual->producto.existencia_cantidad += nuevo_lote->lote.cantidad_de_producto;
        guardarLoteEnProducto(mes_actual, nuevo_lote);
        // Actualizar la cantidad de lotes de toda la cola
        mes_actual->lotes_cantidad++;
        if (band)
        {
            guardarAnoEnLista(producto_actual, ano_actual);
        }
        nuevo_lote->lote.costo_venta = nuevo_lote->lote.precio_producto * nuevo_lote->lote.cantidad_de_producto;
        nuevo_lote->lote.costo_venta += (nuevo_lote->lote.costo_venta * producto->producto.porcentaje_ganancia);
        calcularCostoVentaTotal(producto);

        escribirProductosEnArchivoJSON(lista_producto);
        std::cout << "\n\tLote agregado con exito.\n";
        std::cout << "\tEl ID del lote es: " << nuevo_lote->lote.id_lote << "\n";
        std::cout << "\t¿Deseas ingresar otro lote para este producto? \n";
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
    std::cout << "\tPara el producto \"" << producto_actual->producto.nombre_producto << "\", Digite el ID de lote que desea buscar: ";
    agregarElementoPuntero(id_lote, input);
    lote_actual = obtenerLote(producto_actual, id_lote);
    delete[] id_lote;
    if (lote_actual == NULL)
    {
        std::cout << "\tLote no encontrado.\n";
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
    Lista_Ano *ano_actual = producto->producto.anos_producto;
    while (ano_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL)
            {
                if (strcmp(lote_actual->lote.id_lote, id_lote) == 0)
                {
                    if (lote_actual->lote.validacion)
                    {
                        int op;
                        std::cout << "\n\tEste lote fue eliminado por el sistema.\n";
                        std::cout << "\tMotivo:";
                        (lote_actual->lote.motivo == 1) ? std::cout << " Fecha de caducidad.\n" : std::cout << " Stock en 0.\n";
                        std::cout << "\t¿Deseas continuar con tu accion?\n";
                        std::cout << "\t1.Sí\n\t2.No";
                        std::cout << "\n\tIngresar numero: ";
                        op = soloEnteros();
                        if (op != 1) // op es 2 por ejemplo
                        {
                            if (op != 2)
                            {
                                std::cout << "\tError al ingresar el numero.\n";
                            }
                            return NULL;
                        }
                    }
                    return lote_actual;
                }
                lote_actual = lote_actual->siguiente;
            }
        }
        ano_actual = ano_actual->siguiente;
    }
    return NULL;
}
void mostrarLotesDeProducto(cola_Lote *cola)
{
    std::cout << "\tID del lote: " << cola->lote.id_lote << "\n";
    std::cout << "\tFecha de ingreso : " << cola->lote.ingreso_fecha.dia << "/" << cola->lote.ingreso_fecha.mes << "/" << cola->lote.ingreso_fecha.ano << "\n";
    std::cout << "\tFecha de expiración: " << cola->lote.expiracion_fecha.dia << "/" << cola->lote.expiracion_fecha.mes << "/" << cola->lote.expiracion_fecha.ano << "\n";
    std::cout << "\tPrecio del producto en Córdobas: C$" << cola->lote.precio_producto << "\n";
    std::cout << "\tCantidad del producto ingresada: " << cola->lote.cantidad_de_producto << "\n";
    std::cout << "\tCosto total en Córdobas: " << cola->lote.costo_venta << "\n";
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
    std::cout << "\tADVERTENCIA. ¿Deseas mostrar los lotes anulados por el sistema? por defecto, no se mostraran.\n";
    verificarModificacionEnProducto(op);

    std::cout << "\tMostrando todos los lotes del producto " << producto_actual->producto.nombre_producto << "...\n";
    Lista_Ano *ano_actual = producto_actual->producto.anos_producto;
    while (ano_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
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
        ano_actual = ano_actual->siguiente;
    }
    return;
}

void mostrarTodosLotesDeTodosProductos(lista_Producto *lista_producto)
{
    lista_Producto *aux = lista_producto;
    int op;
    std::cout << "\tADVERTENCIA. ¿Deseas mostrar los lotes anulados por el sistema? por defecto, no se mostraran.\n";
    verificarModificacionEnProducto(op);
    while (aux != NULL)
    {
        std::cout << "\tMostrando todos los lotes del producto \"" << aux->producto.nombre_producto << "\"...\n";
        Lista_Ano *ano_actual = aux->producto.anos_producto;
        while (ano_actual != NULL)
        {
            for (int i = 0; i < 12; i++)
            {
                Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
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
            ano_actual = ano_actual->siguiente;
        }
        std::cout << "\n\tFin de todos los lotes de \"" << aux->producto.nombre_producto << "\".\n";
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
    int op, anoe, mese, diae;
    int dia = obtenerDia(), mes = obtenerMes(), ano = obtenerAno();
    pausarYLimpiar();
    marco();
    gotoxy(2, 6);
    std::cout << "\tSeleccione el campo del lote " << lote_actual->lote.id_lote << " que desea modificar: \n";
    std::cout << "\t1. Fecha de expiración\n";
    std::cout << "\t2. Precio del producto\n";
    std::cout << "\t3. Cantidad del producto\n";
    std::cout << "\tIngresar número: ";
    op = soloEnteros();
    int opt;
    double precio;
    switch (op)
    {
    case 1:
        verificarModificacionEnLote(opt);
        if (opt != 1)
        {
            if (opt != 2)
            {
                std::cout << "\tError al ingresar el numero.\n";
            }
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        std::cout << "\n\tIngrese la fecha de expiración del lote en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &diae, &mese, &anoe);
        if (ingresarFechaExpiracion(ano, mes, dia, anoe, mese, diae))
        {
            Fecha fecha = lote_actual->lote.expiracion_fecha;

            std::cout << "\tLa fecha de expiración de este lote \"" << fecha.dia << "/" << fecha.mes << "/" << fecha.ano << "\" ha sido reemplazada por ";
            std::cout << "\"" << diae << "/" << mese << "/" << anoe << "\"\n";
            lote_actual->lote.expiracion_fecha = {diae, mese, anoe};
            escribirProductosEnArchivoJSON(lista_producto);
            break;
        }
        std::cout << "\tError al ingresar la fecha.\n";
        std::cout << "\tVolviendo al menu anterior.\n";
        limpiarBuffer();
        break;
    case 2:
        verificarModificacionEnLote(opt);
        if (opt != 1)
        {
            if (opt != 2)
            {
                std::cout << "\tError al ingresar el numero.\n";
            }
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        std::cout << "\tIngrese el nuevo precio del producto para este lote: ";

        precio = soloFlotantes();
        if (precio > 0)
        {
            std::cout << "\tEl precio de \"" << lote_actual->lote.cantidad_de_producto << " \"ha sido reemplazado por \"" << precio << "\" para este lote.\n";
            lote_actual->lote.precio_producto = precio;
            double aux = lote_actual->lote.costo_venta; // 100
            lote_actual->lote.costo_venta = 0;
            lote_actual->lote.costo_venta = (lote_actual->lote.precio_producto * lote_actual->lote.cantidad_de_producto);
            lote_actual->lote.costo_venta += (lote_actual->lote.costo_venta * producto_actual->producto.porcentaje_ganancia); // 120
            aux -= lote_actual->lote.costo_venta;                                                                             // -20
            producto_actual->producto.costo_de_venta_total -= aux;
            escribirProductosEnArchivoJSON(lista_producto);
            break;
        }
        else
        {
            std::cout << "\tEl precio no puede ser 0.\n";
        }
        std::cout << "\tVolviendo al menu anterior.\n";
        break;
    case 3:
        verificarModificacionEnLote(opt);
        if (opt != 1)
        {
            if (opt != 2)
            {
                std::cout << "\tError al ingresar el numero.\n";
            }
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        int cantidad_producto;
        int opti;
        std::cout << "\tCantidad actual del lote: " << lote_actual->lote.cantidad_de_producto << "\n";
        std::cout << "\t¿Desea ingresar o eliminar una cantidad?\n";
        std::cout << "\t1. Ingresar\n2. Eliminar\n";
        std::cout << "\tIngresar número: ";
        opti = soloEnteros();
        if (opti != 1 || opti != 2)
        {
            std::cout << "\tError al ingresar el numero.\n";
            std::cout << "\tVolviendo al menú anterior.\n";
            break;
        }
        std::cout << "\tIngrese la cantidad a ";
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
                    std::cout << "\tLa cantidad ingresada no puede ser mayor que la cantidad del lote.\n";
                    break;
                }
            }
            std::cout << "\tCantidad ";
            (opti == 1) ? std::cout << "ingresada " : std::cout << "eliminada ";
            std::cout << "del lote " << lote_actual->lote.id_lote << "\n";
            std::cout << "\tCambios reflejados en la cantidad en existencia del producto.\n";

            lote_actual->lote.cantidad_de_producto += cantidad_producto;
            producto_actual->producto.existencia_cantidad += cantidad_producto;

            double aux = lote_actual->lote.costo_venta; // 100
            lote_actual->lote.costo_venta = 0;
            lote_actual->lote.costo_venta = (lote_actual->lote.precio_producto * lote_actual->lote.cantidad_de_producto);
            lote_actual->lote.costo_venta += (lote_actual->lote.costo_venta * producto_actual->producto.porcentaje_ganancia); // 120
            aux -= lote_actual->lote.costo_venta;                                                                             // -20
            producto_actual->producto.costo_de_venta_total -= aux;
            escribirProductosEnArchivoJSON(lista_producto);
            break;
        }
        std::cout << "\tLa cantidad ingresada no puede ser 0.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        break;
    default:
        std::cout << "\tHas digitado un valor invalido.\n";
        std::cout << "\tSerás enviado al menú anterior.\n";
        break;
    }
    return;
}

void venderCantidad(lista_Producto *&producto_actual, int &cantidad, double &costo_vendido)
{
    cantidad = soloEnteros();
    if (cantidad > producto_actual->producto.existencia_cantidad)
    {
        std::cout << "\tLa cantidad ingresada es mayor que la cantidad en existencia del producto.\n";
        return;
    }

    while (cantidad != 0 || lote_caducidad != NULL)               // 50
    {                                                             // 7 5 10 41
        int aux = cantidad;                                       // 50 - 7 = 43
        cantidad -= *(lote_caducidad->lote.cantidad_de_producto); // 2 10 = -8
        if (cantidad > 0)
        {
            int op;
            while (true)
            {
                if (lote_caducidad->siguiente == NULL)
                {
                }
                std::cout << "\tLa cantidad de productos para el lote " << lote_caducidad->lote.id_lote << " es menor a la cantidad\n\tactual ingresada(" << aux << ")\n";
                std::cout << "\t¿Desea tomar productos del siguiente lote mas proximo a vencer? (" << lote_caducidad->siguiente->lote.id_lote << ")?"
                          << "\n";
                std::cout << "\tEsta accion establecerá el lote actual con una cantidad en stock de 0.\n";
                std::cout << "\t1. Sí\n";
                std::cout << "\t2. No\n";
                std::cout << "\tIngresar numero: ";
                op = soloEnteros();
                if (op == 1 || op == 2)
                {
                    break;
                }
                else
                {
                    std::cout << "\tError al ingresar un numero.\n";
                    std::cout << "\tVuelve a intentarlo.\n";
                    pausar();
                    continue;
                }
            }
            if (op == 1)
            {
                costo_vendido += *(lote_caducidad->lote.costo_venta);
                producto_actual->producto.existencia_cantidad -= *(lote_caducidad->lote.cantidad_de_producto);
                producto_actual->producto.costo_de_venta_total -= *(lote_caducidad->lote.costo_venta);
                *(lote_caducidad->lote.costo_venta) = 0;
                *(lote_caducidad->lote.cantidad_de_producto) = 0;
                vencerLotes(lista_producto);
                limpiar();
                marco();
                generarAlertaCaducidadPorProducto(producto_actual);
                gotoxy(2,6);
                continue;
            }
            break;
        }
        else if (cantidad < 0)
        {
            *(lote_caducidad->lote.cantidad_de_producto) -= aux;
            producto_actual->producto.existencia_cantidad -= aux;
            *(lote_caducidad->lote.costo_venta) = (*(lote_caducidad->lote.cantidad_de_producto) * *(lote_caducidad->lote.precio_producto));
            costo_vendido += *(lote_caducidad->lote.costo_venta);
            std::cout << "\tLa cantidad de " << aux << " ha sido correctamente vendida en el lote " << lote_caducidad->lote.id_lote << ".\n";
            pausar();
            break;
        }
        else if (cantidad == 0)
        {
            costo_vendido += *(lote_caducidad->lote.costo_venta);
            producto_actual->producto.existencia_cantidad -= *(lote_caducidad->lote.cantidad_de_producto);
            producto_actual->producto.costo_de_venta_total -= *(lote_caducidad->lote.costo_venta);
            *(lote_caducidad->lote.costo_venta) = 0;
            *(lote_caducidad->lote.cantidad_de_producto) = 0;
            std::cout << "\tLa cantidad de " << aux << " ha sido correctamente vendida en el lote " << lote_caducidad->lote.id_lote << ".\n";
            pausar();
        }
    }
    costo_vendido += (costo_vendido * producto_actual->producto.porcentaje_ganancia);

}
void registroDeVentasProximoAVencer(lista_Producto *&producto_actual)
{
    int cantidad;
    double costo_vendido = 0;
    generarAlertaCaducidadPorProducto(producto_actual);
    gotoxy(2,12);
    std::cout << "\tA su derecha, se pueden observar los lotes mas prontos a vencer.\n";
    std::cout << "\tDigite la cantidad a vender del producto (no puede ser \n\tmayor que la cantidad del producto)\n";
    std::cout << "\tCantidad del producto \"" << producto_actual->producto.nombre_producto << "\""
              << ": " << producto_actual->producto.existencia_cantidad << "\n";
    std::cout << "\tIngresar cantidad(0 para salir): ";
    venderCantidad(producto_actual, cantidad, costo_vendido);
    std::cout << "\tCantidad en Córdobas vendida: " << costo_vendido << "\n";
}


void registroDeVentasManual(lista_Producto *&producto_actual)
{
    cola_Lote *lote_actual = NULL;
    if (!ingresarLote(producto_actual, lote_actual))
    {
        return;
    }
    int cantidad;
    std::cout << "\tCantidad actual del lote " << lote_actual->lote.id_lote << ": " << lote_actual->lote.cantidad_de_producto;
    std::cout << "\n\tIngrese la cantidad que vendió en el lote " << lote_actual->lote.id_lote << ": ";
    cantidad = soloEnteros();
    if (lote_actual->lote.cantidad_de_producto < cantidad || cantidad == 0)
    {
        (cantidad == 0) ? std::cout << "\tLa cantidad ingresada no puede ser 0.\n" : std::cout << "\tLa cantidad ingresada no puede ser mayor que la cantidad actual del lote.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        return;
    }
    std::cout << "\tCantidad registrada exitosamente.\n";
    std::cout << "\tCambios reflejados en la cantidad en existencia del producto.\n";
    lote_actual->lote.cantidad_de_producto -= cantidad;
    producto_actual->producto.existencia_cantidad -= cantidad;

    double aux = lote_actual->lote.costo_venta; // 100
    lote_actual->lote.costo_venta = 0;
    lote_actual->lote.costo_venta = (lote_actual->lote.precio_producto * lote_actual->lote.cantidad_de_producto);
    lote_actual->lote.costo_venta += (lote_actual->lote.costo_venta * producto_actual->producto.porcentaje_ganancia); // 120
    aux -= lote_actual->lote.costo_venta;                                                                             // -20
    producto_actual->producto.costo_de_venta_total -= aux;
}
void registroDeVentas()
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    int op;
    std::cout << "\tElegir opciones: \n";
    std::cout << "\t1. Seleccionar lote para vender cantidad.\n";
    std::cout << "\t2. Vender cantidad desde el lotes más próximo a vencer.\n";
    std::cout << "\tIngresar número: ";
    op = soloEnteros();
    if (op == 1)
    {
        registroDeVentasManual(producto_actual);
        escribirProductosEnArchivoJSON(lista_producto);
        return;
    }
    else if (op == 2)
    {
        registroDeVentasProximoAVencer(producto_actual);
        escribirProductosEnArchivoJSON(lista_producto);
        return;
    }
    else
    {
        std::cout << "\tValor invalido.\n";
        std::cout << "\tVolviendo al menú anterior.\n";
        return;
    }
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
    std::cout << "\tPara el producto \"" << producto_actual->producto.nombre_producto << "\", Digite el ID de lote que desea buscar: ";
    agregarElementoPuntero(id_lote, input);
    std::cout << "\t¿Estás seguro de que quieres borrar este lote permanentemente?\n";
    verificarModificacionEnProducto(op);
    if (op != 1)
    {
        if (op != 2)
        {
            std::cout << "\tError al ingresar el número.\n";
        }
        std::cout << "\tVolviendo al menú anterior.\n";
        delete[] id_lote;
        return;
    }
    borrarLote(producto_actual, id_lote);

    delete[] id_lote;
}
void borrarLote(lista_Producto *&producto_actual, char *id_lote) // eliminación permanente
{
    lista_Producto *aux_p = producto_actual;
    Lista_Ano *ano_actual = aux_p->producto.anos_producto;
    while (ano_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
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
                    producto_actual->producto.costo_de_venta_total -= lote_actual->lote.costo_venta;
                    delete lote_actual;
                    std::cout << "\tLote eliminado.\n";
                    escribirProductosEnArchivoJSON(lista_producto);
                    return;
                }
                else if (anterior != NULL && strcmp(lote_actual->lote.id_lote, id_lote) == 0)
                {
                    anterior->siguiente = lote_actual->siguiente;
                    delete[] lote_actual->lote.id_lote;
                    producto_actual->producto.costo_de_venta_total -= lote_actual->lote.costo_venta;
                    delete lote_actual;
                    std::cout << "\tLote eliminado.\n";
                    escribirProductosEnArchivoJSON(lista_producto);
                    return;
                }
            }
        }
        ano_actual = ano_actual->siguiente;
    }
    std::cout << "\tLote no encontrado.\n";
}
void vencerLotes(lista_Producto *&producto)
{
    lista_Producto *aux = producto;
    int dia = obtenerDia();
    int mes = obtenerMes();
    int ano = obtenerAno();

    while (aux != NULL)
    {
        if (!aux->producto.anulado)
        {
            Lista_Ano *ano_actual = aux->producto.anos_producto;
            while (ano_actual != NULL)
            {

                for (int i = 0; i < 12; i++)
                {
                    Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
                    cola_Lote *lote_actual = mes_actual->lotes;
                    while (lote_actual != NULL)
                    {

                        bool fecha = comprobarEstadoFecha(dia, mes, ano, lote_actual); // true = fecha valida, false = fecha menor a la actual
                        if (!fecha)                                                    // Anula por caducidad
                        {                                                              // La fecha de expiracion del lote esta antes que la actual
                            if (!lote_actual->lote.validacion)                         // Si el lote es valido...
                            {
                                lote_actual->lote.validacion = !lote_actual->lote.validacion;
                                aux->producto.existencia_cantidad -= lote_actual->lote.cantidad_de_producto;
                                aux->producto.costo_de_venta_total -= lote_actual->lote.costo_venta;
                                lote_actual->lote.motivo = 1;
                                escribirProductosEnArchivoJSON(lista_producto);
                            }
                        }
                        else if (lote_actual->lote.cantidad_de_producto == 0) // Anula por cantidad
                        {
                            if (!lote_actual->lote.validacion)
                            {
                                lote_actual->lote.validacion = !lote_actual->lote.validacion;
                                lote_actual->lote.motivo = 2;
                                escribirProductosEnArchivoJSON(lista_producto);
                            }
                        }
                        else if ((fecha && lote_actual->lote.cantidad_de_producto > 0) && (lote_actual->lote.validacion))
                        { // Reactiva lote si la fecha es valida y la cantidad es mayor a 0, y tambien si el lote ya estaba anulado
                            lote_actual->lote.validacion = !lote_actual->lote.validacion;
                            aux->producto.existencia_cantidad += lote_actual->lote.cantidad_de_producto;

                            lote_actual->lote.motivo = 0;
                            escribirProductosEnArchivoJSON(lista_producto);

                            // Se reactiva
                        }
                        lote_actual = lote_actual->siguiente;
                    }
                }
                ano_actual = ano_actual->siguiente;
            }
        }

        aux = aux->siguiente;
    }
}
