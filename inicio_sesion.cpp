#include "structs.h"
#include "complemento.cpp"
#include "menus.cpp"
#include "producto.cpp"
#include "lote.cpp"

/*
void agregarUsuarioEnLista(lista_Usuario *&usuario, char *input, int &administrador);
void mostrarTodosUsuario(lista_Usuario *lista);
void mostrarUsuario(lista_Usuario *lista);
void buscarUsuarioEnLista(lista_Usuario *lista, char *nombre);
void modificarUsuario(lista_Usuario *&lista);
void eliminarTodaListaUsuario(lista_Usuario *&lista);
void eliminarListaUsuario(lista_Usuario *&lista, char *nombre, char *codigo_acceso);
*/

void inicioSesion(int &opcion);
void inicioSesionAdministradorPersonal(lista_Usuario *&usuario, int &opcion);
void elegirPermiso(int administrador, int &cont, lista_Usuario *&nuevo_usuario);
void agregarPrimerUsuarioEnLista(lista_Usuario *&usuario, char *input);
void inicioSesion(int &opcion, lista_Usuario *&usuario)
{
    do
    {
        std::cout << "Bienvenido al sistema de Gestion de Inventario \"Sabores Sostenibles\"\n\n\n\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Salir\n";
        std::cout << "Seleccionar opcion: ";
        opcion = soloEnteros(opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            if(usuario ==NULL){
                agregarPrimerUsuarioEnLista(usuario, input);
            }
            else{
                inicioSesionAdministradorPersonal(usuario,opcion);
            }
            break;
        case 2:
            std::cout << "Saliendo del sistema...\n";
            break;
        default:
            break;
        }

    } while (opcion !=2);
}

void inicioSesionAdministradorPersonal(lista_Usuario *&usuario, int &opcion)
{
    if (usuario == NULL)
    {
        std::cout << "¡Parece que aún no hay usuarios en el sistema!" << std::endl;
        std::cout << "¿Deseas ingresar un usuario?" << std::endl;
        std::cout << "1. Sí\n";
        std::cout << "2. No\n";
        std::cout << "Ingresar numero: ";
        int op = soloEnteros(op);
        fflush(stdin);
        if (op == 1)
        {
            agregarPrimerUsuarioEnLista(usuario, input);
        }
        else if (op == 2)
        {
            std::cout << "Volviendo al menú anterior...\n";
            system("pause");
            return;
        }
        else
        {
            std::cout << "Has elegido una opción incorrecta. Serás enviado al menú anterior.\n";
            system("pause");
        }
    }
    else
    {
        char *correo;
        char *contraseña;
        std::cout << "Ingrese su correo: ";
        agregarElementoPuntero(correo, input);
        std::cout << "Ingrese su contraseña: ";
        agregarElementoPuntero(contraseña, input);
        if (buscarUsuarioEnLista(usuario, correo, contraseña, &usuario_actual))
        {
            delete[] correo;
            delete[] contraseña;
            menuPrincipal(opcion); //Ejecuta el sistema 
            return;
        }
        else
        {
            delete[] correo;
            delete[] contraseña;
            std::cout << "Los datos del usuario ingresados no son validos. Volviendo al menu anterior...\n";
            system("pause");
        }
        
    }
}

void agregarPrimerUsuarioEnLista(lista_Usuario *&usuario, char *input)
{
    lista_Usuario *nuevo_usuario = new lista_Usuario();
    //std::cout << "Ingrese su nombre completo: ";
    agregarElementoPuntero(nuevo_usuario->usuario.nombre_completo, "admin@admin.com");
    //std::cout << "Ingrese su telefono: ";
    nuevo_usuario->usuario.telefono = soloEnteros(nuevo_usuario->usuario.telefono);
    //fflush(stdin);
    //std::cout << "Ingrese su correo: ";
    agregarElementoPuntero(nuevo_usuario->usuario.correo, "00000000");
    //std::cout << "Ingrese su contraseña: ";
    agregarElementoPuntero(nuevo_usuario->usuario.contraseña, "admin123456");
    char *user = primerNombre(nuevo_usuario->usuario.nombre_completo);
    //std::cout << "Usuario " << user << " agregado a la lista de usuarios." << std::endl;
    //std::cout << "Por defecto, el primer usuario ingresado debe ser un administrador.\n";
    //system("pause");
    nuevo_usuario->usuario.administrador = true;
    // usuario = NULL
    lista_Usuario *aux = usuario; // Reservamos el valor original de la lista
    lista_Usuario *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la llista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (aux == usuario) // Nunca pasó por el while
    { 
        usuario = nuevo_usuario;
    }
    else // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
    { 
        aux2->siguiente = nuevo_usuario;
    }
    nuevo_usuario->siguiente = aux; // nuevo_usuario apunta a NULL
}

void agregarUsuarioEnLista(lista_Usuario *&usuario, char *input)
{
    lista_Usuario *nuevo_usuario = new lista_Usuario();
    int administrador;
    std::cout << "Ingrese su nombre completo: ";
    agregarElementoPuntero(nuevo_usuario->usuario.nombre_completo, input);
    std::cout << "Ingrese su telefono: ";
    nuevo_usuario->usuario.telefono = soloEnteros(nuevo_usuario->usuario.telefono);
    fflush(stdin);
    std::cout << "Ingrese su correo: ";
    agregarElementoPuntero(nuevo_usuario->usuario.correo, input);
    std::cout << "Ingrese su contraseña: ";
    agregarElementoPuntero(nuevo_usuario->usuario.contraseña, input);
    std::cout << "Usuario agregado a la lista de usuarios." << std::endl;
    char *user = primerNombre(nuevo_usuario->usuario.nombre_completo);
    int cont = 0;
    do
    {
        std::cout << "¿Desea otorgar permisos de administrador a " << user << "?\n";
        std::cout << "1. Sí\n";
        std::cout << "2. No\n";
        std::cout << "Ingresar numero: ";
        administrador = soloEnteros(administrador);
        fflush(stdin);
        elegirPermiso(administrador, cont, nuevo_usuario);
    } while (administrador != 1 || administrador != 2 || cont == 3);
    lista_Usuario *aux = usuario; // Reservamos el valor original de la lista
    lista_Usuario *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la llista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (usuario == aux)
    { // Nunca pasó por el while
        usuario = nuevo_usuario;
    }
    else
    { // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
        aux2->siguiente = nuevo_usuario;
    }
    nuevo_usuario->siguiente = aux; // nuevo_usuario apunta a NULL
}

void elegirPermiso(int administrador, int &cont, lista_Usuario *&nuevo_usuario)
{
    if (administrador == 1)
    {
        nuevo_usuario->usuario.administrador = true;
        std::cout << "Permisos otorgados. Esto hace al usuario un administrador\n";
        system("pause");
        return;
    }
    else if (administrador == 2)
    {
        nuevo_usuario->usuario.administrador = false;
        std::cout << "Permisos denegados. Esto hace al usuario parte del personal\n";
        system("pause");
        return;
    }
    else if (cont == 3)
    {
        std::cout << "Has cometido muchos errores al ingresar un numero. El usuario " << primerNombre(nuevo_usuario->usuario.nombre_completo) << " no tendrá permisos de administrador";
        system("pause");
        return;
    }
    else
    {
        std::cout << "Error. No has ingresado un valor valido.";
        system("pause");
        std::cout << "\n\n";
        cont++;
    }
}