#include "structs.h"
#include "inicio_sesion.cpp"

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int opcion = 0;

    inicioSesion(opcion, lista_usuario);

    eliminarTodo(lista_usuario, lista_producto,lista_unidad_medida);

    return 0;
}