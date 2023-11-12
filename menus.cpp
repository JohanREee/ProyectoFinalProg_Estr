#include "structs.h"
#include "complemento.cpp"

// void menuGestionMovimiento();

void menuPrincipal(int &opcion)
{
    opcion = 0;
    char *user = nombreFormal(usuario_activo->usuario);
    do
    {
        std::cout << "\nBienvenido, " << user << "\n";
        std::cout << "\t Sistema de Gestion de Inventario SaboresSostenibles \n";
        std::cout << "1. Gestion de productos" << std::endl;
        std::cout << "2. Gestion de lotes" << std::endl;
        std::cout << "3. Ingresar movimiento" << std::endl;
        std::cout << "4. Generar Reportes Historicos" << std::endl;
        std::cout << "5. Cerrar sesion" << std::endl;
        std::cout << "6. Salir" << std::endl;
        if (usuario_activo->usuario.administrador)
        {
            std::cout << "7. Gestión de usuarios\n";
        }
        std::cout << "Ingresar opcion: ";
        opcion = soloEnteros(opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            std::cout << "Ingresando al sistema de gestión de productos.\n";
            menuGestionProductos(opcion);
            break;
        case 2:
            std::cout << "Ingresando al sistema de gestión de lotes.\n";
            menuGestionLotes(opcion);
            break;
        case 3:
            std::cout << "Ingresar movimiento..." << std::endl;
            break;
        case 4:
            menuReporteHistorico(opcion);
            break;
        case 5:
            std::cout << "Cerrando sesión de " << user << std::endl;
            opcion = 2;
            delete[] user;
            return;
        case 6:
            std::cout << "Saliendo del programa.\n";
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto, lista_unidad_medida);
            break;
        case 7:
            if (usuario_activo->usuario.administrador)
            {
                menuGestionUsuarios(opcion);
            }
            else
            {
                std::cout << "Opcion invalida. Por favor, seleccione una opcion valida.\n";
            }
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida.\n";
            break;
        }
        std::cout << std::endl;
        delete[] user;
        system("pause");
    } while (opcion != 5);
}

void menuGestionProductos(int &opcion)
{
    opcion = 0;
    do
    {
        std::cout << "=== Bienvenido al módulo de gestión de productos ===" << std::endl;
        std::cout << "1. Agregar producto" << std::endl;
        std::cout << "2. Buscar producto" << std::endl;
        std::cout << "3. Anular producto" << std::endl;
        std::cout << "4. Activar producto\n";
        std::cout << "5. Mostrar todos los productos" << std::endl;
        std::cout << "6. Modificar producto" << std::endl;
        std::cout << "7. Volver al menu anterior" << std::endl;
        std::cout << "8. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        opcion = soloEnteros(opcion);
        limpiarBuffer();
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:
            agregarProductoEnLista(lista_producto, input);
            break;
        case 2:
            obtenerProducto(lista_producto);
            break;
        case 3:
            eliminarProducto(lista_producto);
            break;
        case 4:
            activarProducto(lista_producto);
        case 5:
            mostrarTodosProducto(lista_producto);
            break;
        case 6:
            modificarProducto(lista_producto);
            break;
        case 7:
            std::cout << "Volviendo al menú principal." << std::endl;
            break;
        case 8:
            std::cout << "Saliendo del sistema." << std::endl;
            eliminarTodo(lista_usuario, lista_producto, lista_unidad_medida);
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
    } while (opcion != 7);
    opcion = 0;
    std::cout << "\n";
    system("pause");
}
void menuGestionLotes(int &opcion)
{
    opcion = 0;
    do
    {
        std::cout << "=== Bienvenido al módulo de gestión de lotes ===" << std::endl;
        std::cout << "1. Agregar lote" << std::endl;
        std::cout << "2. Buscar lote" << std::endl;
        std::cout << "3. Eliminar lote" << std::endl;
        std::cout << "4. Activar lote" << std::endl;
        std::cout << "5. Mostrar todos los lotes" << std::endl;
        std::cout << "6. Mostrar todos los lotes por producto" << std::endl;
        std::cout << "7. Modificar lote\n";
        std::cout << "8. Volver al menu anterior" << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        opcion = soloEnteros(opcion);
        fflush(stdin);
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:
            agregarLotesAProducto(lista_producto);
            break;
        case 2:
            buscarLote(lista_producto);
            break;
        case 3:
            eliminarLoteDeProducto(lista_producto);
            break;
        case 4:

            break;
        case 5:
            mostrarTodosLotesDeTodosProductos(lista_producto);
            break;
        case 6:
            mostrarTodosLotesDeProducto(lista_producto);
            break;
        case 7:
            modificarLoteDeProducto(lista_producto);
            break;
        case 8:
            std::cout << "Volviendo al menú principal.";
            return;
        case 9:
            std::cout << "Saliendo del programa." << std::endl;
            eliminarTodo(lista_usuario, lista_producto, lista_unidad_medida);
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
    } while (opcion != 8);
    vencerLotes(lista_producto);
    std::cout << std::endl;
    system("pause");
    opcion = 0;
}
void menuReporteHistorico(int &opcion)
{
    opcion = 0;
    while (opcion != 5)
    {
        std::cout << "=== Bienvenido al módulo de reportes historicos ===" << std::endl;
        std::cout << "1. Reporte de existencias por producto." << std::endl;
        std::cout << "2. Reporte por rango de tiempo." << std::endl;
        std::cout << "3. Reporte de lotes por expirar." << std::endl;
        std::cout << "4. Reporte de productos bajos en stock." << std::endl;
        std::cout << "5. Volver al menu anterior." << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        opcion = soloEnteros(opcion);
        fflush(stdin);
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            std::cout << "Volviendo al menú principal.";
            return;
            break;
        case 6:
            std::cout << "Saliendo del programa.\n";
            eliminarTodo(lista_usuario, lista_producto, lista_unidad_medida);
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
        std::cout << std::endl;
        system("pause");
        opcion = 0;
    }
}

void menuGestionUsuarios(int &opcion)
{
    opcion = 0;
    while (opcion != 6)
    {
        std::cout << "=== Bienvenido al módulo de gestión de usuarios ===" << std::endl;
        std::cout << "1. Añadir usuario." << std::endl;
        std::cout << "2. Buscar usuario" << std::endl;
        std::cout << "3. Modificar usuario" << std::endl;
        std::cout << "4. Anular usuario" << std::endl;
        std::cout << "5. Activar usuario\n";
        std::cout << "5. Mostrar todos los usuarios" << std::endl;
        std::cout << "6. Volver al menu anterior." << std::endl;
        std::cout << "7. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        opcion = soloEnteros(opcion);
        fflush(stdin);
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

        case 6:
            std::cout << "Volviendo al menú principal.";
            return;
        case 7:
            std::cout << "Saliendo del programa." << std::endl;
            eliminarTodo(lista_usuario, lista_producto, lista_unidad_medida);
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
        std::cout << std::endl;
        system("pause");
    }
}
