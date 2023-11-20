#include "structs.h"
#include "complemento.cpp"

void generarReporteDeExistenciasActuales(lista_Producto_Existencia *&producto_existencia);
void guardarProductoEnListaDeReporteDeExistencia(lista_Producto_Existencia *&producto_existencia);
void mostrarProductoDeReporteDeExistencia(lista_Producto_Existencia *producto_actual);
void generarReportePorRango();
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
        }
        producto_actual = producto_actual->siguiente;
    }
    if (producto_existencia != NULL)
    {
        std::cout << "Existencia de cada producto.\n";

        return;
    }
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
    std::cout << "";
}