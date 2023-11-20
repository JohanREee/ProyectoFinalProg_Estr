#include "structs.h"
#include "complemento.cpp"
#include "menus.cpp"
#include "producto.cpp"
#include "lote.cpp"
#include "usuario.cpp"
#include "movimientos.cpp"
#include "alertas.cpp"
#include "registros.cpp"
/*
void agregarUsuarioEnLista(lista_Usuario *&usuario, char *input, int &administrador);
void mostrarTodosUsuario(lista_Usuario *lista);
void mostrarUsuario(lista_Usuario *lista);
void buscarUsuarioEnLista(lista_Usuario *lista, char *nombre);
void modificarUsuario(lista_Usuario *&lista);
void eliminarTodaListaUsuario(lista_Usuario *&lista);
void eliminarListaUsuario(lista_Usuario *&lista, char *nombre, char *codigo_acceso);
*/

void inicioSesion(int &opcion)
{
    do
    {
        std::cout << "Bienvenido al sistema de Gestion de Inventario \"SaboresSostenibles\"\n\n\n\n";
        std::cout << "1. Iniciar sesión\n";
        std::cout << "2. Salir\n";
        std::cout << "Seleccionar opcion: ";
        opcion = soloEnteros();
        switch (opcion)
        {
        case 1:
            ingresarDatos(lista_usuario);
            pausarYLimpiar();
            break;
        case 2:
            std::cout << "Saliendo del sistema...\n";
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "Opcion invalida. Volver a intentar.\n";
            break;
        }
    }while(true);
}

void ingresarDatos(lista_Usuario *lista_usuario)
{
    int opcion = 0;
    char *correo;
    char *contraseña;
    std::cout << "Digite el correo electrónico del usuario: ";
    agregarElementoPuntero(correo, input);
    std::cout << "Digite la contraseña del usuario: ";
    contraseña = digitarContraseña();
    lista_Usuario *usuario_actual = buscarUsuarioParaSesion(lista_usuario, correo, contraseña);
    delete[] correo;
    delete[] contraseña;
    if (usuario_actual != NULL)
    {
        usuario_activo = usuario_actual;
        menuPrincipal(opcion);
        return;
    }
    std::cout << "Usuario no encontrado.\n";
    return;
}
