#include "structs.h"

void generarReporteDeExistenciasActuales(lista_Producto *lista_producto, lista_Producto_Existencia *&producto_existencia)
{
    lista_Producto *producto_actual = lista_producto;
    while (producto_actual != NULL)
    {
        if (!producto_actual->producto.anulado)
        {
            lista_Producto_Existencia *nuevo_nodo = new lista_Producto_Existencia();
            nuevo_nodo->producto.id_producto = producto_actual->producto.id_producto;
            nuevo_nodo->producto.nombre_producto = producto_actual->producto.nombre_producto;
            nuevo_nodo->producto.actual_cantidad = producto_actual->producto.existencia_cantidad;
            guardarProductoEnListaDeReporteDeExistencia(nuevo_nodo);
        }
        producto_actual = producto_actual->siguiente;
    }
    if (producto_existencia != NULL)
    {
        lista_Producto_Existencia *aux = producto_existencia;
        while (aux != NULL)
        {
            std::cout << "Existencias de cada producto.\n";
            mostrarProductoDeReporteDeExistencia(aux);
            aux = aux->siguiente;
        }
        std::cout << "Fin del reporte.\n";
        // Agregar la parte de exportar archivos
        eliminarListaDeReporteDeExistencia(producto_existencia);
        return;
    }
    else
        std::cout << "No hay ningún producto en el sistema.\n";
}

void guardarProductoEnListaDeReporteDeExistencia(lista_Producto_Existencia *&producto_actual)
{
    if (producto_existencia == NULL)
    {
        producto_existencia = producto_actual;
    }
    else
    {
        lista_Producto_Existencia *aux = producto_existencia;
        lista_Producto_Existencia *aux2 = NULL;

        while (aux != NULL)
        {
            aux2 = aux;
            aux = aux->siguiente;
        }
        producto_actual->siguiente = aux;
        aux2->siguiente = producto_actual;
    }
}
void mostrarProductoDeReporteDeExistencia(lista_Producto_Existencia *producto_actual)
{
    std::cout << "Nombre: " << producto_actual->producto.nombre_producto << "\n";
    std::cout << "ID: " << producto_actual->producto.id_producto << "\n";
    std::cout << "Existencia: " << producto_actual->producto.actual_cantidad << "\n\n";
}
void eliminarListaDeReporteDeExistencia(lista_Producto_Existencia *&producto_existencia)
{
    while (producto_existencia != NULL)
    {
        lista_Producto_Existencia *aux = producto_existencia;
        producto_existencia = producto_existencia->siguiente;
        delete aux;
    }
}

void generarReporteDeLotesPorRango()
{
    lista_Producto *producto_actual = NULL;
    if (!ingresarProducto(producto_actual))
    {
        return;
    }
    int op;
    std::cout << "Elija una opción. \n";
    std::cout << "1. Reporte por rango entre dos fechas\n";
    std::cout << "2. Reporte por rango a partir de una fecha\n";
    std::cout << "3. Reporte por rango hasta una fecha.\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros();
    if (op == 1)
    {
        Fecha fecha_inicio;
        Fecha fecha_final;
        std::cout << "Ingrese la fecha inicial en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &fecha_inicio.dia, &fecha_inicio.mes, &fecha_inicio.ano);
        if (!validarDiaPorMes(fecha_inicio.dia, fecha_inicio.mes, fecha_inicio.ano))
        {
            std::cout << "Fecha no válida. \n";
            std::cout << "Volviendo al menú anterior.\n";
            return;
        }
        std::cout << "Ingrese la fecha final en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &fecha_final.dia, &fecha_final.mes, &fecha_final.ano);
        if (!validarDiaPorMes(fecha_final.dia, fecha_final.mes, fecha_final.ano))
        {
            std::cout << "Fecha no válida. \n";
            std::cout << "Volviendo al menú anterior.\n";
            return;
        }
        if (buscarLotesPorFecha(producto_actual, fecha_inicio, fecha_final))
        {
            std::cout << "Mostrando todos los lotes del producto \"" << producto_actual->producto.nombre_producto << "\" para las fechas ingresadas.\n ";
            lista_Reporte_Rango *aux = reporte_rango;
            while (aux != NULL)
            {
                mostrarLoteDeReporteDeRango(aux);
                aux = aux->siguiente;
            }
        }
        else
        {
            std::cout << "No hay lotes que coincidan con estas fechas.\n";
        }
    }
    else if (op == 2)
    {
        Fecha fecha_inicial;
        std::cout << "Ingrese la fecha inicial en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &fecha_inicial.dia, &fecha_inicial.mes, &fecha_inicial.ano);
        if (!validarDiaPorMes(fecha_inicial.dia, fecha_inicial.mes, fecha_inicial.ano))
        {
            std::cout << "Fecha no válida. \n";
            std::cout << "Volviendo al menú anterior.\n";
            return;
        }
        if (buscarLotesPorFecha(producto_actual, fecha_inicial))
        {
            std::cout << "Mostrando todos los lotes del producto \"" << producto_actual->producto.nombre_producto << "\" para las fechas ingresadas.\n ";
            lista_Reporte_Rango *aux = reporte_rango;
            while (aux != NULL)
            {
                mostrarLoteDeReporteDeRango(aux);
                aux = aux->siguiente;
            }
        }
        else
        {
            std::cout << "No hay lotes que coincidan con estas fechas.\n";
        }
    }
    else if (op == 3)
    {
        Fecha fecha_finalizar;
        std::cout << "Ingrese la fecha final en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &fecha_finalizar.dia, &fecha_finalizar.mes, &fecha_finalizar.ano);
        if (!validarDiaPorMes(fecha_finalizar.dia, fecha_finalizar.mes, fecha_finalizar.ano))
        {
            std::cout << "Fecha no válida. \n";
            std::cout << "Volviendo al menú anterior.\n";
            return;
        }
        if (buscarLotesPorFecha(producto_actual, {0, 0, 0}, fecha_finalizar))
        {
            std::cout << "Mostrando todos los lotes del producto \"" << producto_actual->producto.nombre_producto << "\" para las fechas ingresadas.\n ";
            lista_Reporte_Rango *aux = reporte_rango;
            while (aux != NULL)
            {
                mostrarLoteDeReporteDeRango(aux);
                aux = aux->siguiente;
            }
        }
        else
        {
            std::cout << "No hay lotes que coincidan con estas fechas.\n";
        }
    }
    else
    {
        std::cout << "Error al ingresar el numero.\n";
        std::cout << "Volviendo al menú anterior.\n";
    }
    eliminarListaDeReporteDeRango(reporte_rango);
}
bool buscarLotesPorFecha(lista_Producto *producto_actual, Fecha fecha_inicio, Fecha fecha_final)
{
    bool desdeFechaInicio = (fecha_inicio.dia == 0) && (fecha_inicio.mes == 0) && (fecha_inicio.ano == 0);
    bool hastaFechaFinal = (fecha_final.dia == 0) && (fecha_final.mes == 0) && (fecha_final.ano == 0);
    Lista_Ano *ano_actual = producto_actual->producto.anos_producto;
    while (ano_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL) // 20/11/2023            20/11/2023
            {
                if (!lote_actual->lote.validacion)
                {
                    bool validado = false;
                    if (!desdeFechaInicio && !hastaFechaFinal)
                    {
                        if (validarFecha(fecha_inicio, fecha_final, lote_actual))
                        {
                            validado = true;
                        }
                    }
                    else if (desdeFechaInicio)
                    {
                        if (!comprobarEstadoFecha(fecha_final.dia, fecha_final.mes, fecha_final.ano, lote_actual))
                        {
                            validado = true;
                        }
                    }
                    else if (hastaFechaFinal)
                    {
                        if (comprobarEstadoFecha(fecha_inicio.dia, fecha_inicio.mes, fecha_inicio.ano, lote_actual))
                        {
                            validado = true;
                        }
                    }
                    if (validado)
                    {
                        lista_Reporte_Rango *nuevo_nodo = new lista_Reporte_Rango();
                        nuevo_nodo->lote.id_lote = lote_actual->lote.id_lote;
                        nuevo_nodo->lote.ingreso_fecha = lote_actual->lote.ingreso_fecha;
                        nuevo_nodo->lote.expiracion_fecha = lote_actual->lote.expiracion_fecha;
                        nuevo_nodo->lote.cantidad_de_producto = lote_actual->lote.cantidad_de_producto;
                        nuevo_nodo->lote.precio_producto = lote_actual->lote.precio_producto;
                        guardarLoteEnListaDeReporteDeRango(nuevo_nodo);
                    }
                }
                lote_actual = lote_actual->siguiente;
            }
        }
        ano_actual = ano_actual->siguiente;
    }
    if (reporte_rango != NULL)
    {
        return true;
    }
    return false;
}
bool validarFecha(Fecha fecha_inicio, Fecha fecha_final, cola_Lote *lote_actual)
{
    if (comprobarEstadoFecha(fecha_inicio.dia, fecha_inicio.mes, fecha_inicio.ano, lote_actual) && !comprobarEstadoFecha(fecha_final.dia, fecha_final.mes, fecha_final.ano, lote_actual))
    { // 10/11/2023      20/11/2024

        return true;
    }

    return false;
}
void guardarLoteEnListaDeReporteDeRango(lista_Reporte_Rango *&reporte_actual)
{
    if (reporte_rango == NULL)
    {

        reporte_rango = reporte_actual;
    }
    else
    {

        lista_Reporte_Rango *aux = reporte_rango;
        lista_Reporte_Rango *aux2 = NULL;

        while (aux != NULL)
        {
            aux2 = aux;
            aux = aux->siguiente;
        }
        reporte_actual->siguiente = aux;
        aux2->siguiente = reporte_actual;
    }
}
void mostrarLoteDeReporteDeRango(lista_Reporte_Rango *lote_actual)
{
    std::cout << "\nID del lote: " << lote_actual->lote.id_lote << "\n";
    std::cout << "Fecha de ingreso del lote: " << lote_actual->lote.ingreso_fecha.dia << "/" << lote_actual->lote.ingreso_fecha.mes << "/" << lote_actual->lote.ingreso_fecha.ano << "\n";
    std::cout << "Fecha de expiración del lote: " << lote_actual->lote.expiracion_fecha.dia << "/" << lote_actual->lote.expiracion_fecha.mes << "/" << lote_actual->lote.expiracion_fecha.ano << "\n";
    std::cout << "Precio del producto en Córdobas en este lote: C$" << lote_actual->lote.precio_producto << "\n";
    std::cout << "Cantidad del producto ingresada en este lote: " << lote_actual->lote.cantidad_de_producto << "\n";
}
void eliminarListaDeReporteDeRango(lista_Reporte_Rango *&reporte_rango)
{
    while (reporte_rango != NULL)
    {
        lista_Reporte_Rango *aux = reporte_rango;
        reporte_rango = reporte_rango->siguiente;
        delete aux;
    }
}

void generarReporteDeLotesPorExpirar()
{
    int op = 0;
    int ano = obtenerAno();
    int mes = obtenerMes();
    int dia = obtenerDia();
    int sumar = 0;
    std::cout << "Para ingresar los lotes que están por expirar, ¿Desea ingresar como estándar 7 días a partir de hoy?\n";
    verificarModificacionEnProducto(op);
    if (op == 1 || op == 2)
    {
        if (op == 1)
        {
            sumar+=7;
            sumarFecha(ano, mes, dia, sumar);
        }
        else
        {
            std::cout << "Ingrese la cantidad en dias para obtener los reportes que están por expirar: ";
            sumar = soloEnteros();
            sumarFecha(ano, mes, dia, sumar);
        }
        Fecha fecha = {dia, mes, ano};
        if (!buscarLoteParaReporteDeLotesPorExpirar(fecha))
        {
            std::cout << "No se han encontrado lotes que expiren actualmente.\n";
            return;
        }
        std::cout << "Mostrando todos los lotes que van a expirar " << sumar;
        (sumar == 1) ? std::cout << " dia" : std::cout << " dias";
        std::cout << " a partir de la fecha ";
        std::cout << fecha.dia << "/" << fecha.mes << "/" << fecha.ano << "\n";
        lista_Lote_Alerta_Caducidad *aux = lote_caducidad;
        while (aux != NULL)
        {
            mostrarAlertaCaducidad(aux);
            aux = aux->siguiente;
        }
        std::cout << "Fin de los lotes.\n";
        // Ingresar lo extra
        eliminarListaDeAlerta(lote_caducidad);
    }
    else
    {
        std::cout << "Valor inválido.\n";
        std::cout << "Volviendo al menú anterior.\n";
    }
}

bool buscarLoteParaReporteDeLotesPorExpirar(Fecha fecha)
{
    lista_Producto *aux = lista_producto;
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
                        if (!lote_actual->lote.validacion && !comprobarEstadoFecha(fecha.dia, fecha.mes, fecha.ano, lote_actual))
                        {
                            lista_Lote_Alerta_Caducidad *nuevo_lote = new lista_Lote_Alerta_Caducidad(); // Crear
                            nuevo_lote->lote.nombre_producto = aux->producto.nombre_producto;                    // Almacenar
                            nuevo_lote->lote.id_lote = lote_actual->lote.id_lote;
                            nuevo_lote->lote.fecha_expiracion = lote_actual->lote.expiracion_fecha;
                            guardarLoteEnLista(nuevo_lote); // Guardar
                        }
                        lote_actual = lote_actual->siguiente;
                    }
                }
                ano_actual = ano_actual->siguiente;
            }
        }
        aux = aux->siguiente;
    }
    if (lote_caducidad != NULL)
    {
        return true;
    }
    return false;
}

void generarReporteStockCritico()
{
    if (!buscarProductosDeReporteStockMinimo())
    {
        std::cout << "No hay productos con stock crítico en el sistema.\n";
        return;
    }
    std::cout << "Mostrando todos los productos con stock Crítico.\n";
    lista_Producto_Alerta_Cantidad *aux = producto_cantidad;
    while (aux != NULL)
    {
        mostrarAlertaCantidadMinima(aux);
        aux = aux->siguiente;
    }
    std::cout << "\nFin del reporte.\n";
    eliminarListaProductoCantidadMinima();
}

bool buscarProductosDeReporteStockMinimo()
{
    lista_Producto *aux = lista_producto;
    while (aux != NULL)
    {
        if (aux->producto.existencia_cantidad < aux->producto.minima_cantidad && !aux->producto.anulado) // La condicional
        {
            lista_Producto_Alerta_Cantidad *nuevo_producto = new lista_Producto_Alerta_Cantidad();
            nuevo_producto->producto.nombre_producto = aux->producto.nombre_producto;
            nuevo_producto->producto.id_producto = aux->producto.id_producto;
            nuevo_producto->producto.actual_cantidad = aux->producto.existencia_cantidad;
            nuevo_producto->producto.minima_cantidad = aux->producto.minima_cantidad;
            guardarProductoEnLista(nuevo_producto);
        }
        aux = aux->siguiente;
    }
    if (producto_cantidad != NULL)
    {
        return true;
    }
    return false;
}

void generarReporteCostoInventario()
{
    double costo_total = 0;
    lista_Producto *aux = lista_producto;
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
                        if (!lote_actual->lote.validacion)
                        {
                            costo_total += (lote_actual->lote.cantidad_de_producto * lote_actual->lote.precio_producto);
                            lote_actual = lote_actual->siguiente;
                        }
                    }
                }
                ano_actual = ano_actual->siguiente;
            }
        }
        aux = aux->siguiente;
    }
    if (costo_total == 0)
    {
        std::cout << "No hay productos en el sistema.\n";
        return;
    }
    std::cout << "El costo total del inventario SaboresSostenibles es: C$" << costo_total << "\n";
}
