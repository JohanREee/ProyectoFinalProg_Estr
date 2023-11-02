#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "auxx.h"
#define MAX 1000  // Constante
#define MAXEMP 10 // Constante
#define MAXC 100
#define color SetConsoleTextAttribute // Constante para no poner una funcion grande todo el tiempo

HANDLE salida = GetStdHandle(STD_OUTPUT_HANDLE); // Color
int i = 0, reg = 0, pos = 0, reg_ing = 0;
int opEMP = 0, op = 0, opADM = 0;         // Opciones
int datoC;                                // Comparador
int comp;                                 // Comparador
bool band = false, administrador = false; // Valor logico
int num_rand;                             // Numero aleatorio
char cedula[MAXC], contraseña[MAXC], usuario[MAXC];

FILE *registros; // Archivo
FILE *registro;

struct adm
{ // Estructura de administrador
    std::string usuario_adm = "Christian";
    std::string contraseña_adm = "123";
} adm;

struct empleado
{ // Estructura de empleado
    char nombre_empleado[MAXC];
    char apellido_empleado[MAXC];
    char cedula_empleado[MAXC];
    char contraseña_empleado[MAXC];
    char nombre_apellido[MAXC];
} emp[MAXEMP];

struct cita
{ // Estructura para todos los datos de la cita
    char cita[MAXC];
    char hora_cita_inicio[MAXC];
    char hora_cita_final[MAXC];
    bool cita_t = false;
};

typedef struct
{ // Estructura para todos los datos del cliente con una estructura anidada que corresponden a los datos de cita
    char nombre_cliente[MAXC];
    char apellido_cliente[MAXC];
    char nombre_apellido[MAXC];
    char email_cliente[MAXC];
    char numero_celular[MAXC];
    int codigo_cliente;
    struct cita cit;
} cliente;

cliente clt[MAX];

int randd();
void AgregarCliente();  // done
void VerDatosCliente(); // done
void EditarCliente();   // done
void AgendarCita();     // done
void VerDatosCita();    // done
void CancelarCita();    // done

// Modificar
int MenuEMP();  // done
int MenuADM();  // done
void Ingreso(); // done (Modify anyway)
// Modificar

// Nuevos
void GuardarCliente();       // done
void LeerCliente();          // done
void BorrarCliente();        // done
void ReinicioCliente(int x); // done

void GuardarCliente();                      // done
int CalcularRegistroCliente(FILE *archivo); // done
void Busqueda(int i);
void M1();                                   // done
void M2();                                   // done
void NombreApellido(int x);                  // done
void NombreApellidoE(int x);                 // done
void GuardarEmpleado();                      // done
void LeerEmpleado();                         // done
void BorrarEmpleado();                       // NOW
void ReinicioEmpleado(int y);                // NOW
int CalcularRegistroEmpleado(FILE *archivo); // done
void DatoEmp();                              // done
void DatoT();                                // done
// Nuevos

int randd()
{ // Numero aleatorio
    srand(time(NULL));
    int inf = 10000, sup = 99999, num;

    num = inf + rand() % (sup + 1 - inf); /* Estableciendo limite inferior y superior de los numeros (100000 y 1000000)*/

    return num; // Retornar valor
}

void GenerarCodigoCliente()
{
    clt[reg].codigo_cliente = randd(); // Importante mencionar que randd() ya no es una funcion, sino el valor retornado de la funcion
    std::cout << "Tu codigo de cliente es: " << clt[reg].codigo_cliente << std::endl;
    color(salida, 4);
    std::cout << "Ten en cuenta que NO se puede cambiar" << std::endl;
    color(salida, 15);
}

void AgregarCliente()
{
    fflush(stdin);
    std::cout << "Ingresa los siguientes campos: " << std::endl;
    std::cout << "Nombre: ";
    std::cin.getline(clt[reg].nombre_cliente, MAXC, '\n');
    std::cout << "Apellido: ";
    std::cin.getline(clt[reg].apellido_cliente, MAXC, '\n');
    std::cout << "Email: ";
    std::cin.getline(clt[reg].email_cliente, MAXC, '\n');
    std::cout << "Numero de celular: ";
    std::cin.getline(clt[reg].numero_celular, MAXC, '\n');
    NombreApellido(reg);
    GenerarCodigoCliente();
    std::cout << "Cliente Agregado con exito." << std::endl;
    reg++;
}
void VerDatosCliente()
{
    fflush(stdin);
    std::cout << "Ingrese su codigo de cliente: ";
    std::cin >> comp; // Ingresa el codigo de cliente
    Busqueda(i);      // Busqueda por seleccion
    if (band == false)
    { // Indica que el bucle no paso por el proceso de mostrar los datos del cliente
        std::cout << "El codigo de cliente no coincide con ningun cliente. Volver a intentar" << std::endl;
    }
    else if (band)
    {
        std::cout << "Datos del cliente " << clt[pos].nombre_apellido << std::endl;
        std::cout << "Nombre: " << clt[pos].nombre_cliente << std::endl;
        std::cout << "Apellido: " << clt[pos].apellido_cliente << std::endl;
        std::cout << "Email: " << clt[pos].email_cliente << std::endl;
        std::cout << "Numero de celular: " << clt[pos].numero_celular << std::endl;
        std::cout << "Codigo de cliente: " << clt[pos].codigo_cliente << std::endl;
        if (clt[pos].cit.cita_t)
        {
            std::cout << "Fecha de la cita: " << clt[pos].cit.cita << std::endl;
            std::cout << "Hora de inicio: " << clt[pos].cit.hora_cita_inicio << std::endl;
            std::cout << "Hora de finalizacion: " << clt[pos].cit.hora_cita_final << std::endl;
        }
    }
    band = false;
}

void DatoT()
{
    if (reg != 0)
    {
        for (i = 0; i < reg; i++)
        { // Muestra todos los datos de todos los clientes
            std::cout << "Datos del cliente ";
            color(salida, 14);
            std::cout << clt[i].nombre_apellido;
            color(salida, 15);
            std::cout << "\n\nNombre: " << clt[i].nombre_cliente << std::endl;
            std::cout << "Apellido: " << clt[i].apellido_cliente << std::endl;
            std::cout << "Email: " << clt[i].email_cliente << std::endl;
            std::cout << "Numero de celular: " << clt[i].numero_celular << std::endl;
            std::cout << "Codigo de cliente: " << clt[i].codigo_cliente << std::endl;
            if (clt[i].cit.cita_t)
            {
                std::cout << "Fecha de la cita: " << clt[i].cit.cita << std::endl;
                std::cout << "Hora de inicio: " << clt[i].cit.hora_cita_inicio << std::endl;
                std::cout << "Hora de finalizacion: " << clt[i].cit.hora_cita_final << std::endl;
            }
            std::cout << "============================================================\n"
                      << std::endl;
        }
    }
    else
    {
        std::cout << "No hay registro para clientes." << std::endl;
    }
    band = false;
}
void EditarCliente()
{
    fflush(stdin);
    std::cout << "Para cambiar los datos del cliente, ingrese su codigo de cliente: ";
    std::cin >> comp; // Ingresa codigo de cliente
    Busqueda(i);
    if (band)
    {
        std::cout << clt[pos].nombre_apellido << ", ingrese el nombre del dato que quiere cambiar: " << std::endl;
        std::cout << "1. Nombre \n2. Apellido \n3. Email \n4. Numero de celular \n5. Todos" << std::endl;
        std::cout << "\n\n\nIngresar numero: ";
        std::cin >> datoC;
        fflush(stdin);
        if (datoC == 1)
        { // Para cambiar nombre
            std::cout << "Ingrese su nuevo nombre: ";
            std::cin.getline(clt[pos].nombre_cliente, MAXC, '\n'); // Ingresar nuevo nombre
            strcpy(clt[pos].nombre_apellido, "");                  // Vaciar el valor de la variable

            NombreApellido(pos); // Nombre y apellido en una sola cadena
            std::cout << "Hola, " << clt[pos].nombre_apellido << std::endl;
            band = false;
        }
        else if (datoC == 2)
        { // Para cambiar apellido
            std::cout << "Ingrese su nuevo apellido: ";
            std::cin.getline(clt[pos].apellido_cliente, MAXC, '\n'); // Ingresar nuevo apellido
            strcpy(clt[pos].nombre_apellido, "");                    // Vaciar el valor de la variable

            NombreApellido(pos);
            std::cout << "Hola, " << clt[pos].nombre_apellido << std::endl;
            band = false;
        }
        else if (datoC == 3)
        { // Para cambiar email
            std::cout << "Ingrese su nuevo email: ";
            std::cin.getline(clt[pos].email_cliente, MAXC, '\n'); // Ingresar nuevo email
            std::cout << "Email cambiado." << std::endl;
            band = false;
        }
        else if (datoC == 4)
        { // Para cambiar Numero de celular
            std::cout << "Ingrese su nuevo numero de celular: ";
            std::cin.getline(clt[pos].numero_celular, MAXC, '\n'); // Ingresar nuevo numero de celular
            std::cout << "Numero de celular cambiado." << std::endl;
            band = false;
        }
        else if (datoC == 5)
        { // Para cambiar todo
            std::cout << "Has elegido la opcion para cambiar todos los datos.\n"
                      << std::endl;
            std::cout << "Ingrese el nuevo nombre: ";
            std::cin.getline(clt[pos].nombre_cliente, MAXC, '\n'); // Ingresar nuevo nombre
            std::cout << "Ingrese el nuevo apellido: ";
            std::cin.getline(clt[pos].apellido_cliente, MAXC, '\n'); // Ingresar nuevo apellido
            std::cout << "Ingrese el nuevo email: ";
            std::cin.getline(clt[pos].email_cliente, MAXC, '\n'); // Ingresar nuevo email
            std::cout << "Ingrese el nuevo numero de celular: ";
            std::cin.getline(clt[pos].numero_celular, MAXC, '\n'); // Ingresar nuevo numero de celular
            strcpy(clt[pos].nombre_apellido, "");

            NombreApellido(pos); // Nombre y apellido en una sola cadena
            std::cout << "Hola, " << clt[pos].nombre_apellido << ". TODOS tus datos han sido modificados. " << std::endl;
            band = false;
        }
        else
        {
            std::cout << "El parametro ingresado es invalido.";
            band = false;
        } // Cuando el usuario digita un parametro invalido
    }
    else
    {
        std::cout << "El codigo de cliente no se encuentra en nuestra base de datos. " << std::endl;
    }
    band = false;
}

void AgendarCita()
{
    fflush(stdin);
    std::cout << "Para agendar una cita, debes escribir el codigo de cliente del usuario: ";
    std::cin >> comp; // Digitar codigo de cliente
    Busqueda(i);      // Busqueda por seleccion
    if (band)
    {
        std::cout << "Ingrese el dia en que desea realizar su cita (formato: dd/MM/yyyy)";
        std::cin >> clt[pos].cit.cita;
        std::cout << "Ingrese la hora de inicio de su cita: ";
        std::cin >> clt[pos].cit.hora_cita_inicio;
        std::cout << "Ingrese la hora de finalizacion de su cita: ";
        std::cin >> clt[pos].cit.hora_cita_final;
        std::cout << "Cita agregada con exito. " << std::endl;
        clt[pos].cit.cita_t = true;
    }
    else
    {
        std::cout << "El codigo de cliente no coincide con ningun cliente." << std::endl;
    }
    band = false;
}
void VerDatosCita()
{
    std::cout << "Para ver los datos de la cita, debes ingresar tu codigo de cliente: ";
    std::cin >> comp;
    Busqueda(i); // Busqueda por seleccion
    if (band)
    {
        std::cout << "Hola, " << clt[pos].nombre_apellido << ". Estos son los datos de tu cita: \n";
        std::cout << "Dia de la cita: " << clt[pos].cit.cita << std::endl;
        std::cout << "Hora de inicio de la cita: " << clt[pos].cit.hora_cita_inicio << std::endl;
        std::cout << "Hora de finalizacion de la cita: " << clt[pos].cit.hora_cita_final << std::endl;
    }
    else
    {
        std::cout << "El codigo de cliente ingresado no coincide. ";
    }
    band = false;
}
void CancelarCita()
{
    std::cout << "Para cancelar tu cita, debes escribir tu codigo de cliente: ";
    std::cin >> comp;
    Busqueda(i);
    if (band && clt[pos].cit.cita_t)
    {
        std::cout << "Hola, " << clt[i].nombre_apellido << ". Tu cita ha sido cancelada." << std::endl;
        clt[i].cit.cita_t = false;
        strcpy(clt[i].cit.hora_cita_final, "");
        strcpy(clt[i].cit.hora_cita_inicio, "");
        strcpy(clt[i].cit.cita, "");
    }
    else if (band == false)
    {
        std::cout << "El codigo de cliente no coincide con ningun cliente." << std::endl;
    }
    else if (clt[pos].cit.cita_t == false)
    {
        std::cout << "No has ingresado los datos para tu cita." << std::endl;
    }
    band = false;
}

int MenuADM()
{
    int opADM = 0;
    std::cout << "Cantidad de clientes añadidos: ";
    color(salida, 9);
    std::cout << reg << std::endl;
    color(salida, 15);
    if(administrador){
        std::cout << "Cantidad de empleados añadidos: ";
        color(salida, 9);
        std::cout << reg_ing<< std::endl;
        color(salida, 10);
    }

    std::cout << "\n\n1. Agregar cliente. " << std::endl;
    std::cout << "2. Ver datos de cliente con código de cliente. " << std::endl;
    if (administrador == false)
    {
        color(salida, 4);
        std::cout << "3. Editar datos de cliente con código de cliente. " << std::endl;
        std::cout << "4. Borrar cliente con código de cliente. " << std::endl;
        color(salida, 10);
    }
    else
    {
        std::cout << "3. Editar datos de cliente con código de cliente. " << std::endl;
        std::cout << "4. Borrar cliente con código de cliente. " << std::endl;
    }

    std::cout << "5. Agendar cita con código de cliente " << std::endl;
    std::cout << "6. Ver datos de cita con código de cliente " << std::endl;
    std::cout << "7. Cancelar cita  " << std::endl;
    std::cout << "8. Cerrar sesion." << std::endl;
    if (administrador == false)
    {
        color(salida, 4);
        std::cout << "9. Ver datos de todos los clientes" << std::endl;
        std::cout << "10. Ver datos de todos los empleados" << std::endl;
        std::cout << "11. Borrar empleado con su cedula. " << std::endl;
        color(salida, 10);
    }
    else
    {
        std::cout << "9. Ver datos de todos los clientes" << std::endl;
        std::cout << "10. Ver datos de todos los empleados" << std::endl;
        std::cout << "11. Borrar empleado con su cedula. " << std::endl;
    }

    std::cout << "12. Salir del sistema" << std::endl;
    color(salida, 8);
    std::cout << "\n\n\nIngresar numero: ";
    color(salida, 7);
    std::cin >> opADM;
    color(salida, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return opADM;
}

void Ingreso()
{
    LeerEmpleado();
principio1:
    M1();
    std::cin >> op;
    color(salida, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    if ((op == 1) && (strcmp(emp[0].cedula_empleado, "") == 0))
    {
        M2();
        goto principio1;
    }
    else if ((op == 1) && (strcmp(emp[0].cedula_empleado, "") != 0))
    {
        system("cls");
        std::cout << "\n1. Registrar empleado \n2. Ingresar con empleado registrado \n ";
        std::cin >> op;
        if (op == 1)
        {
            system("cls");
            M2();
            system("cls");
            goto principio1;
        }
        else if (op == 2)
        {
            system("cls");
            administrador = false;
            std::cout << "Escriba su cedula de identidad: ";
            std::cin >> cedula;
            std::cout << "Escriba su contraseña: ";
            std::cin >> contraseña;
            for (i = 0; i < reg_ing; i++)
            {
                if ((strcmp(emp[i].cedula_empleado, cedula) == 0) && (strcmp(emp[i].contraseña_empleado, contraseña) == 0))
                {
                    band = true;
                    pos = i;
                    break;
                }
            }
            if (band)
            {
                goto principio2;
            }
        }
    }

    else if (op == 2)
    {
        system("cls");
        std::cout << "Ingrese su usuario: ";
        std::cin >> usuario;
        std::cout << "Ingrese su contraseña: ";
        std::cin >> contraseña;
        if ((adm.usuario_adm == usuario) && (adm.contraseña_adm == contraseña))
        {
            color(salida, 12);
            system("cls");
            std::cout << "\n\nBienvenido Christian." << std::endl;
            administrador = true;
            LeerCliente();
            goto principio2;
        }
    }
    else
    {
        std::cout << "La contraseña o el usuario no conciden. Volver a intentar. " << std::endl;
        system("pause");
        goto principio1;
    }
principio2:
    do
    {
        opADM = MenuADM();
        switch (opADM)
        {
        case 1:
            system("cls");
            AgregarCliente();
            system("pause");
            break;
        case 2:
            system("cls");
            VerDatosCliente();
            system("pause");
            break;
        case 3:
            system("cls");
            if (administrador)
            {
                EditarCliente();
            }
            else
            {
                std::cout << "Funcion valida solo para administradores." << std::endl;
            }
            system("pause");
            break;
        case 4:
            if (administrador)
            {
                BorrarCliente();
            }
            else
            {
                std::cout << "Funcion valida solo para administradores. " << std::endl;
            }
            system("pause");
            break;
        case 5:
            system("cls");
            AgendarCita();
            system("pause");
            break;
        case 6:
            system("cls");
            VerDatosCita();
            system("pause");
            break;
        case 7:
            system("cls");
            CancelarCita();
            system("pause");
            break;
        case 8:
            system("cls");
            std::cout << "Has cerrado de sesion correctamente. " << std::endl;
            administrador = false;
            opADM = 0;
            system("pause");
            goto principio1;
        case 9:
            system("cls");
            if (administrador)
            {
                DatoT();
            }
            else
            {
                std::cout << "Funcion valida solo para administradores. ";
            }
            system("pause");
            break;
        case 10:
            system("cls");
            if (administrador)
            {
                DatoEmp();
            }
            else
            {
                std::cout << "Funcion valida solo para administradores. ";
            }
            system("pause");
            break;
        case 11:
            system("cls");
            if (administrador)
            {
                BorrarEmpleado();
            }
            else
            {
                std::cout << "Funcion valida solo para administradores. ";
            }
            system("pause");
            break;
        case 12:
            system("cls");
            std::cout << "Sistema detenido...";
            break;
        default:
            std::cout << "Opcion invalida. Volver a intentar. \n";
            opADM = 0;
            system("pause");
            break;
        }
        system("cls");
        GuardarCliente();
        GuardarEmpleado();
    } while (opADM != 12);
}
void GuardarCliente()
{
    registros = fopen("data.bin", "wb");
    fwrite(clt, sizeof(cliente), reg, registros);
    fclose(registros);
}
void LeerCliente()
{
    registros = fopen("data.bin", "rb");
    if (registros == NULL)
    {
        return;
    }
    reg = CalcularRegistroCliente(registros);
    fread(clt, sizeof(cliente), MAX, registros);
    fclose(registros);
}

int CalcularRegistroCliente(FILE *archivo)
{
    int length, numClientes;
    fseek(archivo, 0, SEEK_END);
    length = ftell(archivo);
    rewind(archivo);

    numClientes = length / sizeof(cliente);
    return numClientes;
}

void NombreApellido(int x)
{
    strcpy(clt[x].nombre_apellido, clt[x].nombre_cliente);
    strcat(clt[x].nombre_apellido, " ");
    strcat(clt[x].nombre_apellido, clt[x].apellido_cliente);
}

void M1()
{
    color(salida, 14);
    gotoxy(15, 4);
    std::cout << "Bienvenido al sistema 'Boomy Nails' Creado para generar citas. Desea ingresar como: \n\n"
              << std::endl;
    color(salida, 12 | FOREGROUND_INTENSITY);
    gotoxy(17, 6);
    std::cout << "1. Empleado \n";
    gotoxy(17, 7);
    std::cout << "2. Administrador \n\n\n";
    color(salida, 11);
    gotoxy(17, 10);
    std::cout << "Ingresar numero: ";
}
void M2()
{
    system("cls");
    std::cout << "Antes de empezar, debes digitar tus datos" << std::endl;
    fflush(stdin);
    std::cout << "Nombre: ";
    std::cin.getline(emp[reg_ing].nombre_empleado, MAXC, '\n');
    std::cout << "Apellido: ";
    std::cin.getline(emp[reg_ing].apellido_empleado, MAXC, '\n');
    std::cout << "Cedula de identidad: ";
    std::cin.getline(emp[reg_ing].cedula_empleado, MAXC, '\n');
    std::cout << "Contraseña: ";
    std::cin.getline(emp[reg_ing].contraseña_empleado, MAXC, '\n');
    NombreApellidoE(reg_ing);
    reg_ing++;
    std::cout << "\nEl empleado ha sido añadido al sistema. " << std::endl;
    GuardarEmpleado();
    system("pause");
    system("cls");
}

void BorrarCliente()
{
    std::cout << "Para borrar un cliente, digite su codigo: ";
    std::cin >> comp;
    for (i = 0; i < reg; i++)
    { // Busqueda por seleccion para encontrar algun cliente con el codigo de cliente digitado
        if (clt[i].codigo_cliente == comp)
        {
            band = true;
            pos = i;
            break;
        }
    }
    if (band)
    {
        std::cout << "Estas a punto de ELIMINAR TODOS los datos de " << clt[pos].nombre_apellido << ". ¿Estas seguro?" << std::endl;
        std::cout << "1. Eliminar" << std::endl;
        std::cout << "2. No Eliminar\n\n"
                  << std::endl;
        color(salida, 14);
        std::cout << "Ingresar número: ";
        std::cin >> comp;
        color(salida, 15);
        if (comp == 1)
        {
            for (i = pos; i < reg - 1; i++)
            {

                clt[i] = clt[i + 1];
            }
            reg--;
            ReinicioCliente(reg);
            std::cout << "Datos borrados exitosamente." << std::endl;
            system("pause");
            system("cls");
        }
        else if (comp == 2)
        {
            std::cout << "Cliente no borrado. " << std::endl;
            system("pause");
            system("cls");
        }
        else
        {
            std::cout << "Parámetro incorrecto. " << std::endl;
            system("pause");
            system("cls");
        }
    }
    else
    {
        std::cout << "Código de cliente invalido. " << std::endl;
    }
}

void ReinicioCliente(int x)
{ // Vaciar todos los datos del cliente que se va a borrar
    strcpy(clt[x].apellido_cliente, "");
    clt[x].codigo_cliente = 0;
    strcpy(clt[x].email_cliente, "");
    strcpy(clt[x].nombre_apellido, "");
    strcpy(clt[x].nombre_cliente, "");
    strcpy(clt[x].numero_celular, "");
}

void Busqueda(int i)
{
    for (i = 0; i <= reg; i++)
    { // Busqueda por seleccion
        if (clt[i].codigo_cliente == comp)
        {
            band = true;
            pos = i; // Valor encontrado
            break;
        }
    }
}

void GuardarEmpleado()
{
    registro = fopen("datae.bin", "wb");
    fwrite(emp, sizeof(empleado), reg_ing, registro);
    fclose(registro);
}

void LeerEmpleado()
{
    registro = fopen("datae.bin", "rb");
    if (registro == NULL)
    {
        return;
    }
    reg_ing = CalcularRegistroEmpleado(registro);
    fread(emp, sizeof(empleado), 10, registro);
    fclose(registro);
}

int CalcularRegistroEmpleado(FILE *archivo)
{
    int length1, numEmpleado;
    fseek(archivo, 0, SEEK_END);
    length1 = ftell(archivo);
    rewind(archivo);

    numEmpleado = length1 / sizeof(empleado);

    return numEmpleado;
}
void NombreApellidoE(int x)
{
    strcpy(emp[x].nombre_apellido, emp[x].nombre_empleado);
    strcat(emp[x].nombre_apellido, " ");
    strcat(emp[x].nombre_apellido, emp[x].apellido_empleado);
}
void DatoEmp()
{
    if (reg_ing == 0)
    {
        std::cout << "No hay registros de empleados. ";
        band = false;
        return;
    }
    for (i = 0; i < reg_ing; i++)
    {
        std::cout << "Datos del empleado ";
        color(salida, 14);
        std::cout << emp[i].nombre_apellido;
        color(salida, 15);
        std::cout << "\n\nNombre: " << emp[i].nombre_empleado << std::endl;
        std::cout << "Apellido: " << emp[i].apellido_empleado << std::endl;
        std::cout << "Cédula: " << emp[i].cedula_empleado << std::endl;
        std::cout << "Contraseña: " << emp[i].contraseña_empleado << std::endl;
        std::cout << "========================================================" << std::endl;
    }
    band = false;
}
void BorrarEmpleado()
{
    std::cout << "Para borrar los datos de un empleado, debe escribir su cedula: ";
    fflush(stdin);
    std::cin.getline(cedula, MAXC, '\n');
    for (i = 0; i < reg_ing; i++)
    {
        if (strcmp(emp[i].cedula_empleado, cedula) == 0)
        {
            band = true;
            pos = i;
            break;
        }
        if (band)
        {
            std::cout << "¿Estás seguro de que deseas BORRAR los Datos del empleado ";
            color(salida, 14);
            std::cout << emp[pos].cedula_empleado << "?" << std::endl;
            color(salida, 15);
            std::cout << "1. Borrar\n";
            std::cout << "2. No borrar\n\n\n";
            color(salida, 6);
            std::cout << "Ingresar numero: ";
            std::cin >> comp;
            color(salida, 15);

            if (comp == 1)
            {
                for (i = pos; i < reg_ing - 1; i++)
                {
                    emp[i] = emp[i + 1];
                }
                reg_ing--;
                ReinicioEmpleado(reg_ing);
                std::cout << "Empleado borrado. " << std::endl;
            }
            else if (comp == 2)
            {
                std::cout << "Empleado no borrado. " << std::endl;
            }
            else
            {
                std::cout << "Has ingresado un dato invalido, Volver a intentar. " << std::endl;
            }
        }
    }
}

void ReinicioEmpleado(int y)
{
    strcpy(emp[y].nombre_empleado, "");
    strcpy(emp[y].apellido_empleado, "");
    strcpy(emp[y].cedula_empleado, "");
    strcpy(emp[y].contraseña_empleado, "");
    strcpy(emp[y].nombre_apellido, "");
}
