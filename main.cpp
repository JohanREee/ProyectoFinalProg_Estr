#include "structs.h"
#include "inicio_sesion.cpp"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int opcion = 0;
    agregarUsuarioMaestro(lista_usuario);
    inicioSesion(opcion);
    return 0;
}