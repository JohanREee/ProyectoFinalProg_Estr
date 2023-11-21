#include "structs.h"
#include "complemento.cpp"

// void menuGestionMovimiento();

void menuPrincipal(int &opcion)
{
    pausarYLimpiar();
    char *user = nombreFormal(usuario_activo->usuario);
    opcion = 0;
    do
    {
        std::cout << "\nBienvenido, " << user << "\n";
        std::cout << "\t Sistema de Gestión de Inventario SaboresSostenibles \n";
        std::cout << "1. Gestion de productos" << std::endl;
        std::cout << "2. Gestion de lotes" << std::endl;
        std::cout << "3. Gestión de usuarios\n";
        std::cout << "4. Generar reportes" << std::endl;
        std::cout << "5. Cerrar sesion" << std::endl;
        std::cout << "6. Salir" << std::endl;
        std::cout << "Ingresar opcion: ";
        opcion = soloEnteros();
        switch (opcion)
        {
        case 1:
            std::cout << "Ingresando al sistema de gestión de productos.\n";
            menuGestionProductos(opcion, user);
            break;
        case 2:
            std::cout << "Ingresando al sistema de gestión de lotes.\n";
            menuGestionLotes(opcion, user);
            break;
        case 3:
            std::cout << "Ingresando al sistema de gestión de usuarios.\n";
            menuGestionUsuarios(opcion, user);
            break;
        case 4:
            std::cout << "Ingresando al sistema de gestión de reportes históricos.\n";
            menuReporteHistorico(opcion, user);
            break;
        case 5:
            std::cout << "Cerrando sesión de " << user << std::endl;
            opcion = 2;
            delete[] user;
            usuario_activo = NULL;
            return;
        case 6:
            std::cout << "Saliendo del programa.\n";
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida.\n";
            break;
        }
    } while (opcion != 5);
    pausarYLimpiar();
}

void menuGestionProductos(int &opcion, char *&user)
{
    pausarYLimpiar();
    opcion = 0;
    do
    {
        generarAlertarCantidadMinima();
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
        opcion = soloEnteros();
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
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "No tienes los permisos acceder a esta opción.\n";
                break;
            }
            anularProducto(lista_producto);
            break;
        case 4:
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "No tienes los permisos acceder a esta opción.\n";
                break;
            }
            activarProducto(lista_producto);
            break;
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
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
        pausarYLimpiar();
    } while (opcion != 7);
    opcion = 0;
    std::cout << "\n";
}
void menuGestionLotes(int &opcion, char *&user)
{
    pausarYLimpiar();
    opcion = 0;
    vencerLotes(lista_producto);
    do
    {
        generarAlertaCaducidad();
        std::cout << "\n=== Bienvenido al módulo de gestión de lotes ===" << std::endl;
        std::cout << "1. Compra de producto" << std::endl;
        std::cout << "2. Buscar lote" << std::endl;
        std::cout << "3. Registrar venta de producto" << std::endl;
        std::cout << "4. Eliminar lote\n";
        std::cout << "5. Modificar lote\n";
        std::cout << "6. Mostrar todos los lotes" << std::endl;
        std::cout << "7. Mostrar todos los lotes por producto" << std::endl;
        std::cout << "8. Volver al menu anterior" << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        opcion = soloEnteros();
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
            registroDeVentas();
            break;
        case 4:
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "No tienes los permisos acceder a esta opción.\n";
                break;
            }
            eliminarLoteDeProducto();
            break;
        case 5:
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "No tienes los permisos acceder a esta opción.\n";
                break;
            }
            modificarLoteDeProducto(lista_producto);
            break;
        case 6:
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "No tienes los permisos acceder a esta opción.\n";
                break;
            }
            mostrarTodosLotesDeTodosProductos(lista_producto);
            break;
        case 7:
            mostrarTodosLotesDeProducto(lista_producto);
            break;
        case 8:
            std::cout << "Volviendo al menú principal.";
            return;
        case 9:
            std::cout << "Saliendo del programa." << std::endl;
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
            pausarYLimpiar();
        }

        vencerLotes(lista_producto);
    } while (opcion != 8);
    opcion = 0;
}
void menuReporteHistorico(int &opcion, char *&user)
{
    opcion = 0;
    while (opcion != 5)
    {
        std::cout << "=== Bienvenido al módulo de reportes historicos ===" << std::endl;
        std::cout << "1. Reporte de existencias por producto." << std::endl;
        std::cout << "2. Reporte por rango de tiempo." << std::endl;
        std::cout << "3. Reporte de lotes por expirar." << std::endl;
        std::cout << "4. Reporte de productos bajos en stock." << std::endl;
        std::cout << "5. Costo total del inventario.\n";
        std::cout << "6. Volver al menu anterior." << std::endl;
        std::cout << "7. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        opcion = soloEnteros();
        fflush(stdin);
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:
            generarReporteDeExistenciasActuales(lista_producto, producto_existencia);
            break;
        case 2:
            generarReporteDeLotesPorRango();
            break;
        case 3:
            generarReporteDeLotesPorExpirar();
            break;
        case 4:
            generarReporteStockCritico();
            break;
        case 5:
            generarReporteCostoInventario();
            break;
        case 6:
            std::cout << "Volviendo al menú principal.";
            return;
        case 7:
            std::cout << "Saliendo del programa.\n";
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "Opcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
        opcion = 0;
    }
}

void menuGestionUsuarios(int &opcion, char *&user)
{
    opcion = 0;
    do
    {
        std::cout << "=== Bienvenido al módulo de gestión de usuarios ===" << std::endl;
        std::cout << "1. Añadir usuario." << std::endl;
        std::cout << "2. Buscar usuario" << std::endl;
        std::cout << "3. Modificar usuario" << std::endl;
        std::cout << "4. Anular usuario" << std::endl;
        std::cout << "5. Activar usuario\n";
        std::cout << "6. Mostrar todos los usuarios" << std::endl;
        std::cout << "7. Volver al menu anterior." << std::endl;
        std::cout << "8. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        opcion = soloEnteros();

        std::cout << std::endl;
        switch (opcion)
        {
        case 1:
            if (usuario_activo->usuario.administrador)
            {
                agregarUsuarioEnLista(lista_usuario);
            }
            else
            {
                std::cout << "No tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            break;
        case 2:
            mostrarUsuarioEnPantalla(lista_usuario);
            pausarYLimpiar();
            break;
        case 3:
            if (usuario_activo->usuario.administrador)
            {
                modificarUsuario(lista_usuario, user);
            }
            else
            {
                std::cout << "No tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            break;
        case 4:
            if (usuario_activo->usuario.administrador)
            {
                eliminarUsuario(lista_usuario);
            }
            else
            {
                std::cout << "No tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            break;
        case 5:
            if (usuario_activo->usuario.administrador)
            {
                activarUsuario(lista_usuario);
            }
            else
            {
                std::cout << "No tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            break;
        case 6:
            if (usuario_activo->usuario.administrador)
            {
                mostrarUsuarios(lista_usuario);
            }
            else
            {
                std::cout << "No tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            break;
        case 7:
            std::cout << "Volviendo al menú principal.";
            return;
        case 8:
            std::cout << "Saliendo del programa." << std::endl;
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "Opcion inválida. Por favor, seleccione una opcion válida." << std::endl;
            pausarYLimpiar();
        }
    } while (opcion != 7);
}
