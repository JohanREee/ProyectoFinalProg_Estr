#include "structs.h"
#include "complemento.cpp"

void crearMovimiento(lista_Movimiento *&movimientos, lista_Producto *producto_actual, cola_Lote *lote_actual, bool band , int cantidad)
{ // true = entrada, false = salida
    lista_Movimiento *nuevo_movimiento = new lista_Movimiento();
    Movimiento *movimiento = &nuevo_movimiento->movimiento;
    movimiento->id_movimiento = ++conteo_id_movimiento;
    movimiento->id_producto = producto_actual->producto.id_producto;
    agregarIdLote(movimiento, lote_actual);
    (band) ? agregarMovimiento(movimiento, true) : agregarMovimiento(movimiento, false);
    // true para entrada, false para salida
    if(!band) cantidad *= -1;
    movimiento->cantidad += cantidad;
    movimiento->fecha = {obtenerDia(), obtenerMes(), obtenerAño()};
    guardarMovimientoEnLista(movimientos,nuevo_movimiento);
}

void agregarIdLote(Movimiento *&movimiento_actual, cola_Lote *lote_actual)
{ // 100            20                80
    movimiento_actual->id_lote = new char[strlen(lote_actual->lote.id_lote) + 1];
    strcpy(movimiento_actual->id_lote, lote_actual->lote.id_lote);
}

void agregarMovimiento(Movimiento *&movimiento_actual, bool band)
{
    movimiento_actual->tipo_movimiento = new char[2];
    (band) ? strcpy(movimiento_actual->tipo_movimiento, "E") : strcpy(movimiento_actual->tipo_movimiento, "S");
}

void guardarMovimientoEnLista(lista_Movimiento *&movimientos, lista_Movimiento *&nuevo_movimiento)
{
    lista_Movimiento *aux = movimientos;
    lista_Movimiento *aux2;
    while (aux != NULL)
    {
        aux2 = aux;
        aux = aux->siguiente;
    }
    if (movimientos == aux)
    {
        movimientos = nuevo_movimiento;
    }
    else
    {
        aux2->siguiente = nuevo_movimiento;
    }
    nuevo_movimiento->siguiente = aux;
}
