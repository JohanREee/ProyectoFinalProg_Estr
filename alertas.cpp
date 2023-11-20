#include "structs.h"
#include "complemento.cpp"

void generarAlertaCaducidad()
{
    if (lote_caducidad != NULL)
        eliminarListaDeAlerta(lote_caducidad);
    int año = obtenerAño();
    int mes = obtenerMes();
    int dia = obtenerDia();
    sumarFecha(año, mes, dia, 7); // Suma 7 dias
    lista_Producto *aux = lista_producto;
    while (aux != NULL)
    {
        Lista_Año *año_actual = aux->producto.años_producto;
        while (año_actual != NULL)
        {
            for (int i = 0; i < 12; i++)
            {

                Informacion_Mes *mes_actual = &año_actual->año_producto.producto[i];
                cola_Lote *lote_actual = mes_actual->lotes;
                while (lote_actual != NULL)
                { // 16/11/23 --------    23/11/23
                    
                    if (!lote_actual->lote.validacion && !comprobarEstadoFecha(dia, mes, año, lote_actual))
                    {
                        lista_Lote_Alerta_Caducidad *nuevo_lote = new lista_Lote_Alerta_Caducidad(); // Crear
                        nuevo_lote->lote.nombre_producto = aux->producto.nombre_producto;            // Almacenar
                        nuevo_lote->lote.id_lote = lote_actual->lote.id_lote;
                        nuevo_lote->lote.fecha_expiracion = lote_actual->lote.expiracion_fecha;
                        guardarLoteEnLista(nuevo_lote); // Guardar
                    }
                    lote_actual = lote_actual->siguiente;
                }
            }
            año_actual = año_actual->siguiente;
        }
        aux = aux->siguiente;
    }

    if (lote_caducidad != NULL)
    {
        int cont = 0;
        lista_Lote_Alerta_Caducidad *aux2 = lote_caducidad;
        std::cout << "\nLotes mas prontos a vencer.\n";
        while (cont != 6)
        {
            cont++;
            mostrarAlertaCaducidad(aux2);
            if (aux2->siguiente == NULL)
            {
                break;
            }
            aux2 = aux2->siguiente;
        }
        eliminarListaDeAlerta(lote_caducidad);
    }
}

void mostrarAlertaCaducidad(lista_Lote_Alerta_Caducidad *lote_actual)
{
    Fecha fecha = {lote_actual->lote.fecha_expiracion.dia, lote_actual->lote.fecha_expiracion.mes, lote_actual->lote.fecha_expiracion.año};
    std::cout << "\n\nNombre: " << lote_actual->lote.nombre_producto << "\n";
    std::cout << "ID de lote: " << lote_actual->lote.id_lote << "\n";
    std::cout << "Fecha de expiración: " << fecha.dia << "/" << fecha.mes << "/" << fecha.año << "\n";
}

void sumarFecha(int &año, int &mes, int &dia, int cantidad)
{
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && esBisiesto(año))
    {
        diasEnMes[1] = 29;
    }
    int aux;
    dia += cantidad;
    while (dia < diasEnMes[mes])
    {
        if (dia > diasEnMes[mes - 1] && mes != 12)
        {                                     // 29/11/23 ------- 6/12/23
            aux = (dia - diasEnMes[mes - 1]); // Cantidad del siguiente dia del siguiente mes, que es 6
            mes += 1;                         // Avanzamos al siguiente mes
            dia -= aux;                        // Asignamos la cantidad en dia
        }
        else if (dia > diasEnMes[mes - 1] && mes == 12)
        {                                     // 29/12/23----------------- 5/1/23
            aux = (dia - diasEnMes[mes - 1]); // Cantidad del siguiente dia del siguiente mes, que es 5
            mes = 1;
            año += 1;
            dia -= aux;
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

        if (aux == NULL || !comprobarEstadoFecha2(aux->lote.fecha_expiracion.dia, aux->lote.fecha_expiracion.mes, aux->lote.fecha_expiracion.año, nuevo_lote))
        {
            nuevo_lote->siguiente = lote_caducidad;
            lote_caducidad = nuevo_lote;
        }
        else
        {

            while (aux != NULL && comprobarEstadoFecha2(aux->lote.fecha_expiracion.dia, aux->lote.fecha_expiracion.mes, aux->lote.fecha_expiracion.año, nuevo_lote))
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
    if (lote_caducidad != NULL)
        eliminarListaDeAlerta(lote_caducidad);
    int año = obtenerAño();
    int mes = obtenerMes();
    int dia = obtenerDia();
    sumarFecha(año, mes, dia, 7); // Suma 7 dias
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
        int cont = 0;
        lista_Producto_Alerta_Cantidad *aux2 = producto_cantidad;
        std::cout << "Productos con cantidad minima en stock crítica.\n";
        while (cont != 6)
        {
            cont++;
            mostrarAlertaCantidadMinima(aux2);
            if (aux2->siguiente == NULL)
                break;
            aux2 = aux2->siguiente;
        }
        eliminarListaProductoCantidadMinima();
    }
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
/*
nuevo_lote->siguiente = aux;
aux2->siguiente = nuevo_lote;*/
/* char *nombre_producto = NULL;
    int id_producto = 0;
    int actual_cantidad = 0;
    int minima_cantidad = 0;*/
