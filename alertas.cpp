#include "structs.h"

void generarAlertaCaducidadPorProducto(lista_Producto *&producto_actual)
{
    if (lote_caducidad != NULL)
        eliminarListaDeAlerta(lote_caducidad);
    int ano = obtenerAno();
    int mes = obtenerMes();
    int dia = obtenerDia();
    sumarFecha(ano, mes, dia, 7300);
    Lista_Ano *ano_actual = producto_actual->producto.anos_producto;
    while (ano_actual != NULL)
    {
        for (int i = 0; i < 12; i++)
        {
            Informacion_Mes *mes_actual = &ano_actual->ano_producto.producto[i];
            cola_Lote *lote_actual = mes_actual->lotes;
            while (lote_actual != NULL)
            { // 16/11/23 --------    23/11/23

                if (!lote_actual->lote.validacion && !comprobarEstadoFecha(dia, mes, ano, lote_actual))
                {
                    lista_Lote_Alerta_Caducidad *nuevo_lote = new lista_Lote_Alerta_Caducidad(); // Almacenar
                    nuevo_lote->lote.id_lote = lote_actual->lote.id_lote;
                    nuevo_lote->lote.fecha_expiracion = &lote_actual->lote.expiracion_fecha;
                    nuevo_lote->lote.costo_venta = &lote_actual->lote.costo_venta;
                    nuevo_lote->lote.cantidad_de_producto = &lote_actual->lote.cantidad_de_producto;
                    nuevo_lote->lote.precio_producto = &lote_actual->lote.precio_producto;
                    guardarLoteEnLista(nuevo_lote); // Guardar
                }
                lote_actual = lote_actual->siguiente;
            }
        }
        ano_actual = ano_actual->siguiente;
    }
    if (lote_caducidad != NULL)
    {
        int cont = 0;
        lista_Lote_Alerta_Caducidad *aux2 = lote_caducidad;
        gotoxy(92, 6);
        std::cout << "Lotes mas prontos a vencer para el producto \"" << producto_actual->producto.nombre_producto << "\".\n";
        int y = 7;
        while (cont != 7)
        {
            cont++;
            mostrarAlertaCaducidadPorProducto(aux2, y);
            if (aux2->siguiente == NULL)
            {
                break;
            }
            aux2 = aux2->siguiente;
        }
    }
}

void mostrarAlertaCaducidadPorProducto(lista_Lote_Alerta_Caducidad *&lote_actual, int &y)
{
    Fecha *fecha = lote_actual->lote.fecha_expiracion;
    gotoxy(92, ++y);
    std::cout << "ID de lote: " << lote_actual->lote.id_lote << "\n";
    gotoxy(92, ++y);
    std::cout << "Fecha de expiración: " << fecha->dia << "/" << fecha->mes << "/" << fecha->ano << "\n";
    gotoxy(92, ++y);
    std::cout << "Costo: C$" << *(lote_actual->lote.costo_venta) << "\n";
    y += 2;
}

void generarAlertaCaducidad()
{
    if (lote_caducidad != NULL)
        eliminarListaDeAlerta(lote_caducidad);
    int ano = obtenerAno();
    int mes = obtenerMes();
    int dia = obtenerDia();
    sumarFecha(ano, mes, dia, 7); // Suma 7 dias
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
                    { // 16/11/23 --------    23/11/23

                        if (!lote_actual->lote.validacion && !comprobarEstadoFecha(dia, mes, ano, lote_actual))
                        {
                            lista_Lote_Alerta_Caducidad *nuevo_lote = new lista_Lote_Alerta_Caducidad(); // Crear
                            nuevo_lote->lote.nombre_producto = aux->producto.nombre_producto;            // Almacenar
                            nuevo_lote->lote.id_lote = lote_actual->lote.id_lote;
                            nuevo_lote->lote.fecha_expiracion = &lote_actual->lote.expiracion_fecha;
                            nuevo_lote->lote.costo_venta = &lote_actual->lote.costo_venta;
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
        int cont = 0;
        lista_Lote_Alerta_Caducidad *aux2 = lote_caducidad;
        gotoxy(92, 6);
        std::cout << "Lotes mas prontos a vencer.\n";
        int y = 7;
        while (cont != 6)
        {
            cont++;
            mostrarAlertaAlertaCaducidad(aux2, y);
            if (aux2->siguiente == NULL)
            {
                break;
            }
            aux2 = aux2->siguiente;
        }
        eliminarListaDeAlerta(lote_caducidad);
    }
}

void mostrarAlertaAlertaCaducidad(lista_Lote_Alerta_Caducidad *lote_actual, int &y)
{
    Fecha *fecha = lote_actual->lote.fecha_expiracion;
    gotoxy(92, y);
    std::cout << "Nombre: " << lote_actual->lote.nombre_producto << "\n";
    gotoxy(92, ++y);
    std::cout << "ID de lote: " << lote_actual->lote.id_lote << "\n";
    gotoxy(92, ++y);
    std::cout << "Fecha de expiración: " << fecha->dia << "/" << fecha->mes << "/" << fecha->ano << "\n";
    gotoxy(92, ++y);
    std::cout << "Costo: C$" << *(lote_actual->lote.costo_venta) << "\n";
    y += 2;
}
void mostrarAlertaCaducidad(lista_Lote_Alerta_Caducidad *lote_actual)
{
    Fecha *fecha = lote_actual->lote.fecha_expiracion;
    std::cout << "\n\nNombre: " << lote_actual->lote.nombre_producto << "\n";
    std::cout << "ID de lote: " << lote_actual->lote.id_lote << "\n";
    std::cout << "Fecha de expiración: " << fecha->dia << "/" << fecha->mes << "/" << fecha->ano << "\n";
    std::cout << "Costo: C$" << *(lote_actual->lote.costo_venta) << "\n";
}

void sumarFecha(int &ano, int &mes, int &dia, int cantidad)
{
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && esBisiesto(ano))
    {
        diasEnMes[1] = 29;
    }

    dia += cantidad;

    while (dia > diasEnMes[mes - 1])
    {
        dia -= diasEnMes[mes - 1];
        mes += 1;
        if (mes > 12)
        {
            mes = 1;
            ano += 1;
        }
    }
}
void guardarLoteEnLista(lista_Lote_Alerta_Caducidad *&nuevo_lote)
{
    if (lote_caducidad == NULL)
    {
        lote_caducidad = nuevo_lote;
    }
    else
    {
        lista_Lote_Alerta_Caducidad *aux = lote_caducidad;
        lista_Lote_Alerta_Caducidad *aux2 = NULL;

        if (aux == NULL || !comprobarEstadoFecha2(aux->lote.fecha_expiracion->dia, aux->lote.fecha_expiracion->mes, aux->lote.fecha_expiracion->ano, nuevo_lote))
        {
            nuevo_lote->siguiente = lote_caducidad;
            lote_caducidad = nuevo_lote;
        }
        else
        {

            while (aux != NULL && comprobarEstadoFecha2(aux->lote.fecha_expiracion->dia, aux->lote.fecha_expiracion->mes, aux->lote.fecha_expiracion->ano, nuevo_lote))
            {
                aux2 = aux;
                aux = aux->siguiente;
            }

            nuevo_lote->siguiente = aux;
            aux2->siguiente = nuevo_lote;
        }
    }
}
void eliminarListaDeAlerta(lista_Lote_Alerta_Caducidad *&lista)
{
    while (lista != NULL)
    {
        lista_Lote_Alerta_Caducidad *aux = lista;
        lista = lista->siguiente;
        delete aux;
    }
}

void generarAlertarCantidadMinima()
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
            nuevo_producto->producto.costo_de_venta_total = aux->producto.costo_de_venta_total;
            guardarProductoEnLista(nuevo_producto);
        }
        aux = aux->siguiente;
    }
    if (producto_cantidad != NULL)
    {
        int cont = 0;
        lista_Producto_Alerta_Cantidad *aux2 = producto_cantidad;
        gotoxy(92, 6);
        int y = 7;
        std::cout << "Productos con cantidad minima en stock crítica.\n";
        while (cont != 6)
        {
            cont++;
            mostrarAlertaAlertaCantidadMinima(aux2, y);
            if (aux2->siguiente == NULL)
                break;
            aux2 = aux2->siguiente;
        }
        eliminarListaProductoCantidadMinima();
    }
}
void mostrarAlertaAlertaCantidadMinima(lista_Producto_Alerta_Cantidad *producto_actual, int &y)
{
    gotoxy(92, ++y);
    std::cout << "Nombre del producto: " << producto_actual->producto.nombre_producto << "\n";
    gotoxy(92, ++y);
    std::cout << "ID del producto: " << producto_actual->producto.id_producto << "\n";
    gotoxy(92, ++y);
    std::cout << "Cantidad total: " << producto_actual->producto.actual_cantidad << "\n";
    gotoxy(92, ++y);
    std::cout << "Cantidad mínima: " << producto_actual->producto.minima_cantidad << "\n";
    gotoxy(92, ++y);
    std::cout << "Costo total: C$" << producto_actual->producto.costo_de_venta_total << "\n";
    y += 2;
}
void mostrarAlertaCantidadMinima(lista_Producto_Alerta_Cantidad *producto_actual)
{
    std::cout << "\n\nNombre del producto: " << producto_actual->producto.nombre_producto << "\n";
    std::cout << "ID del producto: " << producto_actual->producto.id_producto << "\n";
    std::cout << "Cantidad total: " << producto_actual->producto.actual_cantidad << "\n";
    std::cout << "Cantidad mínima: " << producto_actual->producto.minima_cantidad << "\n";
}
void guardarProductoEnLista(lista_Producto_Alerta_Cantidad *&producto_actual)
{
    if (producto_cantidad == NULL)
    {
        producto_cantidad = producto_actual;
    }
    else
    {
        lista_Producto_Alerta_Cantidad *aux = producto_cantidad;
        lista_Producto_Alerta_Cantidad *aux2 = NULL;

        while (aux != NULL)
        {
            aux2 = aux;
            aux = aux->siguiente;
        }
        producto_actual->siguiente = aux;
        aux2->siguiente = producto_actual;
    }
}
void eliminarListaProductoCantidadMinima()
{
    while (producto_cantidad != NULL)
    {
        lista_Producto_Alerta_Cantidad *aux = producto_cantidad;
        producto_cantidad = producto_cantidad->siguiente;
        delete aux;
    }
}
