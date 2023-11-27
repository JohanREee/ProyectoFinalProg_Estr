#include "structs.h"

void marco()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int lim_der = 140;
    int cent = 90;
    int lim_abajo = 35;

    // ESQUINAS //
    gotoxy(0, 0); // ariba izquierda
    std::cout << "*";
    gotoxy(0, lim_abajo); // abajo izquierda
    std::cout << "*";
    gotoxy(lim_der, 0); // arriba derecha
    std::cout << "*";
    gotoxy(lim_der, lim_abajo); // abajo derecha
    std::cout << "*";

    // ARRIBA (PRIMERA LÍNEA)
    for (int up = 1; up < lim_der; up++)
    {
        gotoxy(up, 0);
        std::cout << "*";
    }

    // ARRIBA (SEGUNDA LÍNEA)
    for (int up = 1; up < lim_der; up++)
    {
        gotoxy(up, 3);
        std::cout << "*";
    }

    // ABAJO (PRIMERA LÍNEA)
    for (int down = 1; down < lim_der; down++)
    {
        gotoxy(down, lim_abajo - 2);
        std::cout << "*";
    }

    // ABAJO (SEGUNDA LÍNEA)
    for (int down = 1; down < lim_der; down++)
    {
        gotoxy(down, lim_abajo);
        std::cout << "*";
    }

    // LADO DERECHO 1RA CAJA
    for (int side = 1; side < lim_abajo; side++)
    {
        gotoxy(cent, side);
        std::cout << "*";
    }

    // LADO DERECHO 2DA CAJA
    for (int side = 1; side < lim_abajo; side++)
    {
        gotoxy(lim_der, side);
        std::cout << "*";
    }

    // LADO IZQUIERDO

    for (int side = 1; side < lim_abajo; side++)
    {
        gotoxy(0, side);
        std::cout << "*";
    }

    // NOMBRE SISTEMA
    gotoxy(2, 1);
    std::cout << "SISTEMA DE GESTION";
    gotoxy(2, 2);
    std::cout << "DISKInventory";

    // NOMBRE SUBSISTEMA
    gotoxy(cent + 2, 1);
    std::cout << "NOTIFICACIONES";
    gotoxy(cent + 2, 2);
    std::cout << "Y ALERTAS";
}
// void menuGestionMovimiento();

//HOJA REPORTE

void marcoReporte()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int lim_der = 120;
    int lim_abajo = 40;

    // ESQUINAS //
    gotoxy(0, 0); // ariba izquierda
    std::cout << "*";
    gotoxy(0, lim_abajo); // abajo izquierda
    std::cout << "*";
    gotoxy(lim_der, 0); // arriba derecha
    std::cout << "*";
    gotoxy(lim_der, lim_abajo); // abajo derecha
    std::cout << "*";

    // ARRIBA (PRIMERA LÍNEA)
    for (int up = 1; up < lim_der; up++)
    {
        gotoxy(up, 0);
        std::cout << "*";
    }

    // ARRIBA (SEGUNDA LÍNEA)
    for (int up = 1; up < lim_der; up++)
    {
        gotoxy(up, 3);
        std::cout << "*";
    }

    // ABAJO (PRIMERA LÍNEA)
    for (int down = 1; down < lim_der; down++)
    {
        gotoxy(down, lim_abajo - 2);
        std::cout << "*";
    }


    // LADO DERECHO
    for (int side = 1; side < lim_abajo; side++)
    {
        gotoxy(lim_der, side);
        std::cout << "*";
    }

    // LADO IZQUIERDO

    for (int side = 1; side < lim_abajo; side++)
    {
        gotoxy(0, side);
        std::cout << "*";
    }

    // NOMBRE SISTEMA
    gotoxy(2, 1);
    std::cout << "SISTEMA DE GESTION";
    gotoxy(2, 2);
    std::cout << "DISKInventory";
}

void menuPrincipal(int &opcion)
{
    pausarYLimpiar();
    marco();
    char *user = nombreFormal(usuario_activo->usuario);
    opcion = 0;
    do
    {
        pausarYLimpiar();
        marco();
        gotoxy(2, 6);
        std::cout << "\tBienvenido, " << user << "\n";
        std::cout << "\t Sistema de Gestión de Inventario DISKInventory \n";
        std::cout << "\t1. Gestion de productos" << std::endl;
        std::cout << "\t2. Gestion de lotes" << std::endl;
        std::cout << "\t3. Gestión de usuarios\n";
        std::cout << "\t4. Generar reportes" << std::endl;
        std::cout << "\t5. Cerrar sesion" << std::endl;
        std::cout << "\t6. Salir" << std::endl;
        std::cout << "\tIngresar opcion: ";
        opcion = soloEnteros();
        switch (opcion)
        {
        case 1:
            std::cout << "\tIngresando al sistema de gestión de productos.\n";
            menuGestionProductos(opcion, user);
            break;
        case 2:
            std::cout << "\tIngresando al sistema de gestión de lotes.\n";
            menuGestionLotes(opcion, user);
            break;
        case 3:
            std::cout << "\tIngresando al sistema de gestión de usuarios.\n";
            menuGestionUsuarios(opcion, user);
            break;
        case 4:
            std::cout << "\tIngresando al sistema de gestión de reportes históricos.\n";
            menuReporteHistorico(opcion, user);
            break;
        case 5:
            std::cout << "\tCerrando sesión de " << user << std::endl;
            opcion = 2;
            delete[] user;
            usuario_activo = NULL;
            return;
        case 6:
            std::cout << "\tSaliendo del programa.\n";
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "\tOpcion invalida. Por favor, seleccione una opcion valida.\n";
            break;
        }
    } while (opcion != 5);
    pausarYLimpiar();
}

void menuGestionProductos(int &opcion, char *&user)
{
    pausarYLimpiar();
    marco();
    opcion = 0;
    do
    {
        pausarYLimpiar();
        marco();
        generarAlertarCantidadMinima();
        gotoxy(2, 6);
        std::cout << "\t=== Bienvenido al módulo de gestión de productos ===" << std::endl;
        std::cout << "\t1. Agregar producto" << std::endl;
        std::cout << "\t2. Buscar producto" << std::endl;
        std::cout << "\t3. Anular producto" << std::endl;
        std::cout << "\t4. Activar producto\n";
        std::cout << "\t5. Mostrar todos los productos" << std::endl;
        std::cout << "\t6. Modificar producto" << std::endl;
        std::cout << "\t7. Volver al menu anterior" << std::endl;
        std::cout << "\t8. Salir" << std::endl;
        std::cout << "\tSeleccione una opcion: ";
        opcion = soloEnteros();
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:
            pausarYLimpiar();
            marco();
            agregarProductoEnLista(lista_producto, input);
            break;
        case 2:
            pausarYLimpiar();
            marco();
            obtenerProducto(lista_producto);
            break;
        case 3:
            pausarYLimpiar();
            marco();
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "\tNo tienes los permisos acceder a esta opción.\n";
                break;
            }
            anularProducto(lista_producto);
            break;
        case 4:
            pausarYLimpiar();
            marco();
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "\tNo tienes los permisos acceder a esta opción.\n";
                break;
            }
            activarProducto(lista_producto);
            break;
        case 5:
            pausarYLimpiar();
            marco();
            mostrarTodosProducto(lista_producto);
            break;
        case 6:
            pausarYLimpiar();
            marco();
            modificarProducto(lista_producto);
            break;
        case 7:
            std::cout << "\tVolviendo al menú principal." << std::endl;
            break;
        case 8:
            std::cout << "\tSaliendo del sistema." << std::endl;
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "\tOpcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
        pausarYLimpiar();
        marco();
    } while (opcion != 7);
    opcion = 0;
    std::cout << "\n";
}
void menuGestionLotes(int &opcion, char *&user)
{
    pausarYLimpiar();
    marco();
    opcion = 0;
    vencerLotes(lista_producto);
    do
    {
        pausarYLimpiar();
        marco();
        generarAlertaCaducidad();
        gotoxy(2, 6);
        std::cout << "\t=== Bienvenido al módulo de gestión de lotes ===" << std::endl;
        std::cout << "\t1. Compra de producto" << std::endl;
        std::cout << "\t2. Buscar lote" << std::endl;
        std::cout << "\t3. Registrar venta de producto" << std::endl;
        std::cout << "\t4. Eliminar lote\n";
        std::cout << "\t5. Modificar lote\n";
        std::cout << "\t6. Mostrar todos los lotes" << std::endl;
        std::cout << "\t7. Mostrar todos los lotes por producto" << std::endl;
        std::cout << "\t8. Volver al menu anterior" << std::endl;
        std::cout << "\t9. Salir" << std::endl;
        std::cout << "\tSeleccione una opcion: ";
        opcion = soloEnteros();
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:
            pausarYLimpiar();
            marco();
            agregarLotesAProducto(lista_producto);
            break;
        case 2:
            pausarYLimpiar();
            marco();
            buscarLote(lista_producto);
            break;
        case 3:
            pausarYLimpiar();
            marco();
            registroDeVentas();
            break;
        case 4:
            pausarYLimpiar();
            marco();
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "\tNo tienes los permisos acceder a esta opción.\n";
                break;
            }
            eliminarLoteDeProducto();
            break;
        case 5:
            pausarYLimpiar();
            marco();
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "\tNo tienes los permisos acceder a esta opción.\n";
                break;
            }
            modificarLoteDeProducto(lista_producto);
            break;
        case 6:
            pausarYLimpiar();
            marco();
            if (!usuario_activo->usuario.administrador)
            {
                std::cout << "\tNo tienes los permisos acceder a esta opción.\n";
                break;
            }
            mostrarTodosLotesDeTodosProductos(lista_producto);
            break;
        case 7:
            pausarYLimpiar();
            marco();
            mostrarTodosLotesDeProducto(lista_producto);
            break;
        case 8:
            std::cout << "\tVolviendo al menú principal.";
            return;
        case 9:
            std::cout << "\tSaliendo del programa." << std::endl;
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "\tOpcion invalida. Por favor, seleccione una opcion valida." << std::endl;
            pausarYLimpiar();
            marco();
        }

        vencerLotes(lista_producto);
    } while (opcion != 8);
    opcion = 0;
}
void menuReporteHistorico(int &opcion, char *&user)
{
    opcion = 0;
    pausarYLimpiar();
    marcoReporte();
    while (opcion != 5)
    {
        pausarYLimpiar();
        marcoReporte();
        gotoxy(2,6);
        std::cout << "\t=== Bienvenido al módulo de reportes historicos ===" << std::endl;
        std::cout << "\t1. Reporte de existencias por producto." << std::endl;
        std::cout << "\t2. Reporte por rango de tiempo." << std::endl;
        std::cout << "\t3. Reporte de lotes por expirar." << std::endl;
        std::cout << "\t4. Reporte de productos bajos en stock." << std::endl;
        std::cout << "\t5. Costo total del inventario.\n";
        std::cout << "\t6. Volver al menu anterior." << std::endl;
        std::cout << "\t7. Salir" << std::endl;
        std::cout << "\tSeleccione una opcion: ";
        opcion = soloEnteros();
        fflush(stdin);
        std::cout << std::endl;
        switch (opcion)
        {
        case 1:
            pausarYLimpiar();
            marcoReporte();
            generarReporteDeExistenciasActuales(lista_producto, producto_existencia);
            break;
        case 2:
            pausarYLimpiar();
            marcoReporte();
            generarReporteDeLotesPorRango();
            break;
        case 3:
            pausarYLimpiar();
            marcoReporte();
            generarReporteDeLotesPorExpirar();
            break;
        case 4:
            pausarYLimpiar();
            marcoReporte();
            generarReporteStockCritico();
            break;
        case 5:
            pausarYLimpiar();
            marcoReporte();
            generarReporteCostoInventario();
            break;
        case 6:
            std::cout << "\tVolviendo al menú principal.";
            pausarYLimpiar();
            marco();
            return;
        case 7:
            std::cout << "\tSaliendo del programa.\n";
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            pausarYLimpiar();
            marco();
            break;
        default:
            std::cout << "\tOpcion invalida. Por favor, seleccione una opcion valida." << std::endl;
        }
        opcion = 0;
    }
}

void menuGestionUsuarios(int &opcion, char *&user)
{
    pausarYLimpiar();
    marco();
    opcion = 0;
    do
    {
        pausarYLimpiar();
        marco();
        gotoxy(2, 6);
        std::cout << "\t=== Bienvenido al módulo de gestión de usuarios ===" << std::endl;
        std::cout << "\t1. Añadir usuario." << std::endl;
        std::cout << "\t2. Buscar usuario" << std::endl;
        std::cout << "\t3. Modificar usuario" << std::endl;
        std::cout << "\t4. Anular usuario" << std::endl;
        std::cout << "\t5. Activar usuario\n";
        std::cout << "\t6. Mostrar todos los usuarios" << std::endl;
        std::cout << "\t7. Volver al menu anterior." << std::endl;
        std::cout << "\t8. Salir" << std::endl;
        std::cout << "\tSeleccione una opcion: ";
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
                std::cout << "\tNo tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            marco();
            break;
        case 2:
            mostrarUsuarioEnPantalla(lista_usuario);
            pausarYLimpiar();
            marco();
            break;
        case 3:
            if (usuario_activo->usuario.administrador)
            {
                modificarUsuario(lista_usuario, user);
            }
            else
            {
                std::cout << "\tNo tienes permisos para eliminar usuarios.\n";
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
                std::cout << "\tNo tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            marco();
            break;
        case 5:
            if (usuario_activo->usuario.administrador)
            {
                activarUsuario(lista_usuario);
            }
            else
            {
                std::cout << "\tNo tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            marco();
            break;
        case 6:
            if (usuario_activo->usuario.administrador)
            {
                mostrarUsuarios(lista_usuario);
            }
            else
            {
                std::cout << "\tNo tienes permisos para eliminar usuarios.\n";
            }
            pausarYLimpiar();
            marco();
            break;
        case 7:
            std::cout << "\tVolviendo al menú principal.";
            return;
        case 8:
            std::cout << "\tSaliendo del programa." << std::endl;
            delete[] user;
            eliminarTodo(lista_usuario, lista_producto);
            break;
        default:
            std::cout << "\tOpcion inválida. Por favor, seleccione una opcion válida." << std::endl;
            pausarYLimpiar();
        }
    } while (opcion != 7);
}