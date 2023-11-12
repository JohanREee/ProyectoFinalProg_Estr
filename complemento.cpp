#ifndef complemento
#define complemento

#include "structs.h"

int soloEnteros(int numero);
double soloFlotantes(double numero);
char *primerNombre(char *nombre);
char *primerApellido(char *apellido);
char *nombreFormal(char *nombre, char *apellido);
Lista_Año *buscarAñoActualDeProducto(lista_Producto *producto, int año);
bool validarDiaPorMes(int dia, int mes, int año);
bool esBisiesto(int año);
void asociarMesConNumero(int mes);
void limpiarBuffer();
bool verificarModificacionEnLote(int &op);
bool verificarModificacionEnProducto(int &op);
bool verificarModificacionEnUsuario(int &op);
bool comprobarCorreo(char *correo, lista_Usuario *lista_usuario);

int soloEnteros(int numero)
{
    if (std::cin >> numero)
    {
        limpiarBuffer();
        return numero;
    }
    limpiarBuffer();
    return numero;
}

double soloFlotantes(double numero)
{
    if (std::cin >> numero)
    {
        return numero;
    }
    limpiarBuffer();
    return numero;
}

char *nombreFormal(Usuario usuario_actual)
{
    char *nombre = new char[strlen(usuario_actual.nombres) + 1];
    char *apellido = new char[strlen(usuario_actual.apellidos) + 1];
    strcpy(nombre, usuario_actual.nombres);
    strcpy(apellido, usuario_actual.apellidos);

    char *primerNombre = strtok(nombre, " ");
    char *primerApellido = strtok(apellido, " ");

    int length = strlen(primerNombre) + strlen(primerApellido) + 2;
    char *nombreFormal = new char[length];

    strcpy(nombreFormal, nombre);
    strcat(nombreFormal, " ");
    strcat(nombreFormal, apellido);
    delete[] nombre;
    delete[] apellido;
    return nombreFormal;
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

void asociarMesConNumero(int mes)
{
    switch (mes + 1)
    {
    case 1:
        std::cout << "Mes: Enero";
        break;
    case 2:
        std::cout << "Mes: Febrero";
        break;
    case 3:
        std::cout << "Mes: Marzo";
        break;
    case 4:
        std::cout << "Mes: Abril";
        break;
    case 5:
        std::cout << "Mes: Mayo";
        break;
    case 6:
        std::cout << "Mes: Junio";
        break;
    case 7:
        std::cout << "Mes: Julio";
        break;
    case 8:
        std::cout << "Mes: Agosto";
        break;
    case 9:
        std::cout << "Mes: Septiembre";
        break;
    case 10:
        std::cout << "Mes: Octubre";
        break;
    case 11:
        std::cout << "Mes: Noviembre";
        break;
    case 12:
        std::cout << "Mes: Diciembre";
        break;

    default:
        break;
    }
}

bool validarDiaPorMes(int dia, int mes, int año)
{
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta febrero para años bisiestos
    if (esBisiesto(año))
    {
        diasEnMes[1] = 29;
    }

    if (dia < 1 || dia > diasEnMes[mes - 1])
    {
        return false; // Día inválido para el mes dado
    }

    return true; // Fecha válida
}

bool esBisiesto(int año)
{
    return (año % 4 == 0 && año % 100 != 0) || (año % 400 == 0);
}

bool ingresarFechaExpiracion(int año, int mes, int dia, int añoe, int mese, int diae)
{
    if ((añoe == año) && (mese == mes) && (diae > dia)) // Validar en el mes actual
    {
        if (validarDiaPorMes(diae, mese, añoe))
        {
            return true;
        }
    }
    else if ((añoe == año) && (mese > mes))
    {
        if (validarDiaPorMes(diae, mese, añoe))
        {
            return true;
        }
    }
    else if (añoe > año)
    {
        if (validarDiaPorMes(diae, mese, añoe))
        {
            return true;
        }
    }
    return false;
}

bool comprobarEstadoFecha(int dia, int mes, int año, cola_Lote *lote_actual)
{
    Fecha fecha_expira = lote_actual->lote.expiracion_fecha; // 11/11/2023         //18/11/2023
    if (ingresarFechaExpiracion(año, mes, dia, fecha_expira.año, fecha_expira.mes, fecha_expira.dia))
    {
        return true;
    }
    return false;
}
void limpiarBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return;
}
bool verificarModificacionEnLote(int &op)
{
    std::cout << "¿Estás seguro de querer modificar este valor?\n";
    std::cout << "1.Sí\n2.No\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros(op);
    if (op == 1)
    {
        return true;
    }
    return false;
}
bool verificarModificacionEnProducto(int &op)
{
    std::cout << "1.Sí\n2.No\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros(op);
    if (op == 1)
    {
        return true;
    }
    return false;
}
bool verificarModificacionEnUsuario(int &op)
{
    std::cout << "\n1.Sí\n2.No\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros(op);
    if (op == 1)
    {
        return true;
    }
    return false;
}

bool comprobarCorreo(char *correo, lista_Usuario *lista_usuario)
{
    if ((strchr(correo, '@') != NULL) && (strlen(correo) > 3))
    {
        lista_Usuario *aux = lista_usuario;
        while (aux != NULL)
        {
            if (strcmp(aux->usuario.correo, correo) == 0)
            {
                return false;
            }
            aux = aux->siguiente;
        }
        return true;
    }
    return false;
}
#endif