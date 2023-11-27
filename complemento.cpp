#include "structs.h"

char *digitarContrasena()
{
    int i = 0;
    char ch;

    while (true)
    {
        ch = _getch();

        if (ch == 13) // Presiono enter
        {
            if (i != 0) // Verifica si el primero que puso no es un enter
            {
                std::cout << "\n";
                break;
            }
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                std::cout << "\b \b";
            }
        }
        else if (i < 249)
        {
            input[i] = ch;
            i++;
            std::cout << "*";
        }
    }
    input[i] = '\0';
    char *contrasena = new char[strlen(input) + 1];
    strcpy(contrasena, input);
    input[0] = '\0';
    return contrasena;
}
void agregarElementoPuntero(char *&dato, char *input)
{
    char ch;
    int i = 0;
    do
    {
        ch = _getch();
        if (ch == 13) // Presiono enter
        {
            if (i != 0) // Verifica si el primero que puso no es un enter
            {
                std::cout << "\n";
                break;
            }
        }
        else if (ch == 8)
        {
            if (i > 0)
            {
                i--;
                std::cout << "\b \b";
            }
        }
        else if (i < 249)
        {
            input[i] = ch;
            i++;
            std::cout << ch;
        }
    } while (true);
    
    input[i] = '\0';
    int length = strlen(input);
    dato = new char[length + 1];
    strcpy(dato, input);
    input[0] = '\0';
}

int soloEnteros()
{
    int i = 0;
    char ch;
    while (true)
    {

        ch = _getch();

        if (ch == 13) // Presiono enter
        {
            if (i != 0)
            {
                input[i] = '\0';
                break;
            }
        }                 // -0.
        else if (ch == 8) // Backspace
        {
            if (i > 0)
            {
                i--;
                std::cout << "\b \b";
            }
        }
        else if (std::isdigit(ch) && i < 10) // Digito
        {
            input[i] = ch;
            i++;
            std::cout << ch;
        }
    }
    input[i] = '\0';
    std::cout << "\n";
    int numero = std::atoi(input);
    input[0] = '\0';
    return numero;
}

double soloFlotantes()
{
    int i = 0;
    char ch;
    bool punto = false;
    while (true)
    {
        ch = _getch();

        if (ch == 13) // Presiono enter
        {
            if (i != 0 && input[i - 1] != '.')
            {
                break;
            }
        }                 // -0.
        else if (ch == 8) // Backspace
        {
            if (i > 0)
            {
                if (input[i - 1] == '.')
                {
                    punto = false;
                }
                i--;
                std::cout << "\b \b";
            }
        }
        else if (i < 11) // 249 es el limite de input, input [250]
        {
            if (std::isdigit(ch)) // Digito
            {
                input[i] = ch;
                i++;
                std::cout << ch;
            }
            if (ch == '.') // PUnto decimal
            {
                if (!punto && i > 0 && std::isdigit(input[i - 1]))
                {
                    input[i] = ch;
                    i++;
                    std::cout << ch;
                    punto = true;
                }
            }
        }
    }
    input[i] = '\0';
    std::cout << "\n";
    double numero = std::atof(input);
    input[0] = '\0';
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

int obtenerAno()
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    int ano = now->tm_year + 1900;
    return ano;
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

Lista_Ano *buscarAnoActualDeProducto(lista_Producto *producto, int ano)
{
    Lista_Ano *lista_ano = producto->producto.anos_producto;
    while (lista_ano != NULL)
    {
        if (lista_ano->ano_producto.ano == ano)
        {
            return lista_ano;
        }
        lista_ano = lista_ano->siguiente;
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

bool validarDiaPorMes(int dia, int mes, int ano)
{
    int diasEnMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta febrero para anos bisiestos
    if (esBisiesto(ano))
    {
        diasEnMes[1] = 29;
    }

    if (mes < 1 || mes > 12)
    {
        return false; // Mes inválido
    }

    if (dia < 1 || dia > diasEnMes[mes - 1])
    {
        return false; // Día inválido para el mes dado
    }
    return true; // Fecha válida
}

bool esBisiesto(int ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

bool ingresarFechaExpiracion(int ano, int mes, int dia, int anoe, int mese, int diae)
{
    if ((anoe == ano) && (mese == mes) && (diae > dia)) // Validar en el mes actual
    {
        if (validarDiaPorMes(diae, mese, anoe))
        {
            return true;
        }
    }
    else if ((anoe == ano) && (mese > mes))
    {
        if (validarDiaPorMes(diae, mese, anoe))
        {
            return true;
        }
    }
    else if (anoe > ano)
    {
        if (validarDiaPorMes(diae, mese, anoe))
        {
            return true;
        }
    }
    return false;
}

bool comprobarEstadoFecha(int dia, int mes, int ano, cola_Lote *lote_actual)
{
    Fecha fecha_expira = lote_actual->lote.expiracion_fecha; // 11/11/2023         //18/11/2023
    if (ingresarFechaExpiracion(ano, mes, dia, fecha_expira.ano, fecha_expira.mes, fecha_expira.dia))
    {
        return true;
    }
    return false;
}

bool comprobarEstadoFecha2(int dia, int mes, int ano, lista_Lote_Alerta_Caducidad *lote_actual)
{
    Fecha fecha_expira = lote_actual->lote.fecha_expiracion; // 11/11/2023         //18/11/2023
    if (ingresarFechaExpiracion(ano, mes, dia, fecha_expira.ano, fecha_expira.mes, fecha_expira.dia))
    {
        return true;
    }
    return false;
}
void limpiarBuffer()
{
    std::cin.clear();
    std::cin.ignore();
    return;
}
void verificarModificacionEnLote(int &op)
{
    std::cout << "¿Estás seguro de querer modificar este valor?\n";
    std::cout << "1.Sí\n2.No\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros();
}
void verificarModificacionEnProducto(int &op)
{
    std::cout << "1.Sí\n2.No\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros();
}
bool verificarModificacionEnUsuario(int &op)
{
    std::cout << "\n1.Sí\n2.No\n";
    std::cout << "Ingresar número: ";
    op = soloEnteros();
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

void pausar()
{
    std::cout << "\nPresione ENTER para continuar...\n";
    std::cin.get();
}

void limpiar()
{
    system("cls || clear");
}

void pausarYLimpiar()
{
    pausar();
    limpiar();
}
void gotoxy(int x, int y) 
{
	// Obtiene el identificador de la consola de salida estándar
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);

	// Crea una estructura de coordenadas con las posiciones especificadas
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	// Establece la posición del cursor en la consola a las coordenadas especificadas
	SetConsoleCursorPosition(hcon, dwPos);
}
