#include "structs.h"
#include "complemento.cpp"
void menuPrincipal(int &opcion);
void menuGestionProductos(int &opcion);
void menuGestionLotes(int &opcion);
void menuReporteHistorico(int &opcion);
void menuGestionUsuarios(int &opcion);
// void menuGestionMovimiento();

void menuPrincipal(int &opcion)
{
    opcion = 0;
    while (opcion != 6 || opcion != 5)
    {
        std::cout << "Bienvenido, " << primerNombre(usuario_actual->usuario.nombre_completo) << "\n";
        std::cout << "\t Sistema de Gestion de Inventario SaboresSostenibles \n"
                  << std::endl;
        std::cout << "1. Gestion de productos" << std::endl;
        std::cout << "2. Gestion de lotes" << std::endl;
        std::cout << "3. Ingresar movimiento" << std::endl;
        std::cout << "4. Generar Reportes Historicos" << std::endl;
        std::cout << "5. Cerrar sesion" << std::endl;
        std::cout << "6. Salir" << std::endl;
        if (usuario_actual->usuario.administrador)
        {
            std::cout << "7. Gestión de usuarios\n";
        }
        std::cout << "Ingresar opcion: ";
        opcion = soloEnteros(opcion);
        fflush(stdin);
        switch (opcion)
        {
        case 1:
            std::cout << "Ingresando al sistema de gestión de productos\n";
            menuGestionProductos(opcion);
            break;
        case 2:
            menuGestionLotes(opcion);
            break;
        case 3:
            std::cout << "Ingresar movimiento..." << std::endl;
            break;
        case 4:
            menuReporteHistorico(opcion);
            break;
        case 5:
            std::cout << "Cerrando sesión de " << primerNombre(usuario_actual->usuario.nombre_completo) << std::endl;
            opcion = 2;
            return;
        case 6:
            std::cout << "Saliendo del programa.\n";
            return;
        case 7:
            if (usuario_actual->usuario.administrador)
            {
                // menu de gestion
            }
            else
            {
                std::cout << "Opcion invalida. Por favor, seleccione una opcion valida.\n";
            }
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
            break;
        }

        std::cout << std::endl;
        system("pause");
    }
}

void menuGestionProductos(int &opcion)
{
    opcion = 0;
    while (opcion != 6 || opcion != 7)
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
        fflush(stdin);
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
            std::cout << "Activando producto..." << std::endl;
        case 5:
            mostrarTodosProducto(lista_producto);
            break;
        case 6:
            modificarProducto(lista_producto);
            break;
        case 7:
            std::cout << "Volviendo al menú principal." << std::endl;
            return;
        case 8:
            std::cout << "Saliendo del sistema." << std::endl;
            exit(0);
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
    }
    opcion = 0;
}
void menuGestionLotes(int &opcion)
{
    opcion = 0;
    while (opcion != 7 || opcion != 8)
    {
        std::cout << "=== Bienvenido al módulo de gestión de lotes ===" << std::endl;
        std::cout << "1. Agregar lote" << std::endl;
        std::cout << "2. Buscar lote" << std::endl;
        std::cout << "3. Eliminar lote" << std::endl;
        std::cout << "4. Mostrar todos los lotes" << std::endl;
        std::cout << "5. Mostrar todos los lotes por producto" << std::endl;
        std::cout << "6. Modificar lote\n";
        std::cout << "7. Volver al menu anterior" << std::endl;
        std::cout << "8. Salir" << std::endl;
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

            break;
        case 4:
            mostrarTodosLotesDeTodosProductos(lista_producto);
            break;
        case 5:
            mostrarTodosLotesDeProducto(lista_producto);
            break;
        case 6:
            modificarLoteDeProducto(lista_producto);
        case 7:
            std::cout << "Volviendo al menú principal.";
            return;
        case 8:
            std::cout << "Saliendo del programa. �Hasta luego!" << std::endl;
            exit(0);
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
    }
    vencerLotes(lista_producto);
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
            std::cout << "Saliendo del programa. �Hasta luego!" << std::endl;
            exit(0);
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
    }
}

void menuGestionUsuario(int &opcion)
{
    opcion = 0;
    while (opcion != 5)
    {
        std::cout << "=== Bienvenido al módulo de gestión de usuarios ===" << std::endl;
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
            std::cout << "Saliendo del programa. �Hasta luego!" << std::endl;
            exit(0);
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
    }
}