#include "structs.h"

void inicioSesion(int &opcion)
{
    do
    {
        pausarYLimpiar();
        marco();
        gotoxy(2, 6);
        std::cout << "1. Iniciar sesión\n";
        gotoxy(2, 7);
        std::cout << "2. Salir\n";
        gotoxy(2, 8);
        std::cout << "Seleccionar opcion: ";
        opcion = soloEnteros();
        switch (opcion)
        {
        case 1:
            ingresarDatos(lista_usuario);
            pausarYLimpiar();
            break;
        case 2:
            pausarYLimpiar();
            gotoxy(2, 6);
            std::cout << "Saliendo del sistema...\n";
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            pausarYLimpiar();
            gotoxy(2, 6);
            std::cout << "Opcion invalida. Volver a intentar.\n";
            break;
        }
    } while (true);
}

void ingresarDatos(lista_Usuario *lista_usuario)
{
    int opcion = 0;
    char *correo;
    char *contrasena;
    gotoxy(2, 9);
    std::cout << "Digite el correo electrónico del usuario: ";
    agregarElementoPuntero(correo, input);
    gotoxy(2, 10);
    std::cout << "Digite la contraseña del usuario: ";
    contrasena = digitarContrasena();
    lista_Usuario *usuario_actual = buscarUsuarioParaSesion(lista_usuario, correo, contrasena);
    delete[] correo;
    delete[] contrasena;
    if (usuario_actual != NULL)
    {
        usuario_activo = usuario_actual;
        menuPrincipal(opcion);
        return;
    }
    gotoxy(2, 11);
    std::cout << "Usuario no encontrado.\n";
    return;
}
