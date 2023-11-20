#include "structs.h"
#include "complemento.cpp"

void generarReporteDeExistenciasActuales(lista_Producto_Existencia *&producto_existencia);
void guardarProductoEnListaDeReporteDeExistencia(lista_Producto_Existencia *&producto_existencia);
void mostrarProductoDeReporteDeExistencia(lista_Producto_Existencia *producto_actual);
void eliminarListaDeReporteDeExistencia(lista_Producto_Existencia *&producto_existencia);
void generarReporteDeLotesPorRango();
void guardarLoteEnListaDeReporteDeRango(lista_Reporte_Rango *&reporte_actual);
void mostrarLoteDeReporteDeRango(lista_Reporte_Rango *lote_actual);
void eliminarListaDeReporteDeRango(lista_Producto_Existencia *&reporte_rango);
bool buscarLotesPorFecha(lista_Producto *producto_actual, Fecha fecha_inicio = {0, 0, 0}, Fecha fecha_final = {0, 0, 0});
bool validarFecha(Fecha fecha_inicio, Fecha fecha_final, cola_Lote *lote_actual);
void generarReporteDeLotesPorExpirar();
void generarReporteStockCritico();

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
        } // buscarLotesPorFecha(&producto, fecha_final: {31, 12, 2023});
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
        producto_existencia->siguiente = aux;
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
    std::cout << "3.Reporte por rango hasta una fecha.\n";
    op = soloEnteros();
    if (op == 1)
    {
        Fecha fecha_inicio;
        Fecha fecha_final;
        std::cout << "Ingrese la fecha inicial en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &fecha_inicio.dia, &fecha_inicio.mes, &fecha_inicio.año);
        if (!validarDiaPorMes(fecha_inicio.dia, fecha_inicio.mes, fecha_inicio.año))
        {
            std::cout << "Fecha no válida. \n";
            std::cout << "Volviendo al menú anterior.\n";
            return;
        }
        std::cout << "Ingrese la fecha final en formato dd/mm/yyyy: ";
        scanf("%2d/%2d/%4d", &fecha_final.dia, &fecha_final.mes, &fecha_final.año);
        if (!validarDiaPorMes(fecha_final.dia, fecha_final.mes, fecha_final.año))
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
        scanf("%2d/%2d/%4d", &fecha_inicial.dia, &fecha_inicial.mes, &fecha_inicial.año);
        if (!validarDiaPorMes(fecha_inicial.dia, fecha_inicial.mes, fecha_inicial.año))
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
        else // CONTINUE
        {
            std::cout << "No hay lotes que coincidan con estas fechas.\n";
        }
    }
    else if (op == 3)
    {
        Fecha fecha_finalizar;
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
    bool desdeFechaInicio = (fecha_inicio.dia != 0) && (fecha_inicio.mes != 0) && (fecha_inicio.año != 0);
    bool hastaFechaFinal = (fecha_final.dia != 0) && (fecha_final.mes != 0) && (fecha_final.año != 0);
    Lista_Año *año_actual = producto_actual->producto.años_producto;
    while (año_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL) // 20/11/2023            20/11/2023
            {
                if (!lote_actual->lote.validacion)
                {
                    if (!desdeFechaInicio && hastaFechaFinal)
                    {
                        if (comprobarEstadoFecha(fecha_inicio.dia, fecha_inicio.mes, fecha_inicio.año, lote_actual))
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
                    else if (!hastaFechaFinal && desdeFechaInicio)
                    {
                        if (!comprobarEstadoFecha(fecha_final.dia, fecha_final.mes, fecha_final.año, lote_actual))
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
                    else
                    {
                        if (validarFecha(fecha_inicio, fecha_final, lote_actual))
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
                }
                lote_actual = lote_actual->siguiente;
            }
        }
        año_actual = año_actual->siguiente;
    }
    if (reporte_rango != NULL)
    {
        return true;
    }
    return false;
}
bool validarFecha(Fecha fecha_inicio, Fecha fecha_final, cola_Lote *lote_actual)
{
    if (comprobarEstadoFecha(fecha_inicio.dia, fecha_inicio.mes, fecha_inicio.año, lote_actual) && !comprobarEstadoFecha(fecha_final.dia, fecha_final.mes, fecha_final.año, lote_actual))
    {
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
        reporte_rango->siguiente = aux;
        aux2->siguiente = reporte_actual;
    }
}
void mostrarLoteDeReporteDeRango(lista_Reporte_Rango *lote_actual)
{
    std::cout << "\nID del lote: " << lote_actual->lote.id_lote << "\n";
    std::cout << "Fecha de ingreso del lote: " << lote_actual->lote.ingreso_fecha.dia << "/" << lote_actual->lote.ingreso_fecha.mes << "/" << lote_actual->lote.ingreso_fecha.año << "\n";
    std::cout << "Fecha de expiración del lote: " << lote_actual->lote.expiracion_fecha.dia << "/" << lote_actual->lote.expiracion_fecha.mes << "/" << lote_actual->lote.expiracion_fecha.año << "\n";
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