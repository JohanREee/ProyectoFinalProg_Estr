#ifndef complemento
#define complemento

#include "structs.h"

int soloEnteros(int numero);
double soloFlotantes(double numero);
char *primerNombre(char *nombre);
Lista_Año *buscarAñoActualDeProducto(lista_Producto *producto, int año);
bool validarDiaPorMes(int dia, int mes, int año);
bool esBisiesto(int año);

int soloEnteros(int numero)
{
    if (std::cin >> numero)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

bool validarDiaPorMes(int dia, int mes, int año)
{
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta febrero para años bisiestos
    if (esBisiesto(año))
    {
        diasEnMes[2] = 29;
    }

    if (dia < 1 || dia > diasEnMes[mes])
    {
        return false; // Día inválido para el mes dado
    }

    return true; // Fecha válida
}

bool esBisiesto(int año)
{
    return (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0);
}