#ifndef complemento
#define complemento

#include "structs.h"

int soloEnteros(int numero);
double soloFlotantes(double numero);
char *primerNombre(char *nombre);
Lista_Año *buscarAñoActualDeProducto(lista_Producto *producto, int año);

int soloEnteros(int numero)
{
    if (std::cin >> numero)
    {
        return numero;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return numero;
}

double soloFlotantes(double numero)
{
    if (std::cin >> numero)
    {
        return numero;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return numero;
}

char *primerNombre(char *nombre)
{
    return strtok(nombre, " ");
}

int obtenerAño()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    int año = now->tm_year + 1900;
    return año;
}
int obtenerMes()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    int mes = now->tm_mon + 1;
    return mes;
}
int obtenerDia()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    int dia = now->tm_mday;
    return dia;
}

Lista_Año *buscarAñoActualDeProducto(lista_Producto *producto, int año)
{
    Lista_Año *lista_año = producto->producto.años_producto;
    while (lista_año != NULL)
    {
        if (lista_año->año_producto.año == año)
        {
            return lista_año;
        }
        lista_año = lista_año->siguiente;
    }
    return NULL;
}
#endif