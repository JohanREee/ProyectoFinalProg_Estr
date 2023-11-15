
#ifndef structs
#define structs

#define MAXCHAR 250
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <windows.h>
#include <ctime>

char input[MAXCHAR];

struct Fecha
{
    int dia;
    int mes;
    int año;
};

struct lista_Unidad_Medida
{
    char *unidad_medida = NULL;
    lista_Unidad_Medida *siguiente;
};

struct Movimiento
{
    int id_movimiento;
    char *tipo_movimiento;
    int cantidad;
    Fecha fecha;
};

struct Lote
{
    char *id_lote;
    Fecha ingreso_fecha;
    Fecha expiracion_fecha;
    double precio_producto;
    int cantidad_de_producto;
    bool validacion = false;
    int forma_validacion = 1;
    // 1 significa que fue borrado o activado por el usuario. Denota valor primario
    // 2 significa que fue borrado por el propio sistema y el producto caduco por su fecha.
    // 3 significa que fue activado por el usuario cuando el sistema lo desactivó.
};

struct cola_Lote
{ // Cola para los lotes de un producto
    Lote lote;
    cola_Lote *siguiente;
};

struct lista_Movimiento
{
    Movimiento movimiento;
    lista_Movimiento *siguiente;
};

struct Informacion_Mes
{
    int mes;
    cola_Lote *lotes = NULL;
    int lotes_cantidad = 0;
    lista_Movimiento *movimientos = NULL;
};

struct Año_Producto
{
    int año;
    Informacion_Mes producto[12];
};

struct Lista_Año
{ // Lista enlazada para cada año
    Año_Producto año_producto;
    Lista_Año *siguiente;
};

struct Usuario
{
    char *nombres = NULL;
    char *apellidos = NULL;
    int telefono;
    char *correo = NULL;
    char *contraseña = NULL;
    bool administrador;
    bool validacion = false;
};

struct Producto
{
    int id_producto;
    char *nombre_producto = NULL;
    char *unidad_medida = NULL;
    char *descripcion_producto = NULL;
    Lista_Año *años_producto = NULL;
    int existencia_cantidad = 0;
    bool anulado = false;
};

struct lista_Producto
{ // Lista enlazada con todos los productos
    Producto producto;
    lista_Producto *siguiente;
};

struct lista_Usuario
{
    Usuario usuario;
    lista_Usuario *siguiente;
};

struct reporte_Historico
{
    char *autor;
    char *id_reporte;
    char *id_producto;
    char *administrador_asignado;
    Fecha fecha_elaboracion;
    Fecha fecha_inicio;
    Fecha fecha_final;
};

struct lista_Reporte_Historico
{
    reporte_Historico reporte;
    lista_Reporte_Historico *siguiente;
};

lista_Usuario *lista_usuario = NULL;
lista_Reporte_Historico *lista_reporte_historico = NULL;
lista_Producto *lista_producto = NULL;
lista_Unidad_Medida *lista_unidad_medida = NULL;
lista_Usuario *usuario_activo = NULL; 
int conteo_id_producto = 0;

// Prototipado de funcionaes

// General

void agregarElementoPuntero(char *&dato, char *input);
void modificarElementoPuntero(char *&dato, char *input);
void eliminarTodo(lista_Usuario *&lista_usuario, lista_Producto *&lista_producto, lista_Unidad_Medida *&lista_unidad_medida);
bool ingresarFechaExpiracion(int año, int mes, int dia, int añoe, int mese, int diae);
void asociarMesConNumero(int mes);
void inicioSesion(int &opcion);
void ingresarDatos(lista_Usuario *lista_usuario);
//Menu

void menuPrincipal(int &opcion);
void menuGestionProductos(int &opcion, char *&user);
void menuGestionLotes(int &opcion, char *&user);
void menuReporteHistorico(int &opcion, char *&user);
void menuGestionUsuarios(int &opcion, char *&user);
// Usuarios
void agregarUsuarioMaestro(lista_Usuario *&lista_usuario);
void agregarUsuarioEnLista(lista_Usuario *&lista_usuario);
void mostrarUsuarioEnPantalla(lista_Usuario *lista_usuario);
void mostrarUsuario(Usuario usuario);
lista_Usuario *buscarUsuarioParaSesion(lista_Usuario *lista, char *correo, char *contraseña);
lista_Usuario *buscarUsuario(lista_Usuario *lista, char *correo);
void modificarUsuario(lista_Usuario *&lista_usuario, char *&user);
void eliminarUsuario(lista_Usuario *&lista_usuario);
void activarUsuario(lista_Usuario *&lista_usuario);
void modificarNombreYApellido(lista_Usuario *&usuario_actual, char *user);
void modificarTelefono(lista_Usuario *&usuario_actual, char *user);
void modificarCorreo(lista_Usuario *&usuario_actual, char *user);
void modificarContraseña(lista_Usuario *&usuario_actual, char *user);
void modificarPermiso(lista_Usuario *&usuario_actual, char *user);
void mostrarUsuarios(lista_Usuario *lista_usuario);
// Unidades de medida

void agregarUnidadMedida(lista_Unidad_Medida *&lista, char *input);
bool comprobarUnidadMedida(lista_Unidad_Medida *lista, char *unidad_medida);

// Producto

void agregarProductoEnLista(lista_Producto *&producto, char *input);
void mostrarTodosProducto(lista_Producto *lista_producto);
void mostrarProducto(lista_Producto *producto);
void mostrarProductosNoAnulados(lista_Producto *producto);
void mostrarProductosAnulados(lista_Producto *producto);
lista_Producto *buscarProducto(lista_Producto *lista, int id_producto);
lista_Producto *buscarProductoAnulado(lista_Producto *lista, int id_producto);
void modificarProducto(lista_Producto *&lista_producto);
void eliminarTodaListaProducto(lista_Producto *&lista_producto);
void eliminarProducto(lista_Producto *&lista_producto);
void obtenerProducto(lista_Producto *lista_producto);
lista_Producto *buscarProductoParaInformacion(lista_Producto *lista, int id_producto);
void activarProducto(lista_Producto *&lista_producto);

// Lote
void agregarPrimerLote(lista_Producto *&producto);
char *generarIdLote(int dia, int mes, int año, Informacion_Mes *mes_actual, Producto producto_actual);
void agregarLotesAProducto(lista_Producto *&producto);
void mostrarLotesDeProducto(cola_Lote *cola);
void mostrarTodosLotesDeTodosProductos(lista_Producto *lista_producto);
void mostrarTodosLotesDeProducto(lista_Producto *lista_producto);
void buscarLote(lista_Producto *lista_producto);
cola_Lote *obtenerLote(lista_Producto *producto, char *id_lote);
void vencerLotes(lista_Producto *&producto);
void modificarLoteDeProducto(lista_Producto *&producto_actual);
void eliminarLoteDeProducto(lista_Producto *&lista_producto);
void eliminarLotesYMovimientosTodoDeProducto(cola_Lote *&cola_lote, lista_Movimiento *&cola_movimiento, char *id_producto, char *codigo_acceso);
bool comprobarEstadoFecha(int dia, int mes, int año, cola_Lote *lote_actual);
void registroDeInformacionLote(Lote &lote);
void activarLoteDeProducto(lista_Producto *&lista_producto);

// Movimiento

void agregarMovimientoDeProducto(lista_Movimiento *&cola);
void mostrarMovimientosDeProducto(lista_Movimiento *cola, char *id_producto);
void mostrarMovimientosDeTodoProductos(lista_Movimiento *cola, char *id_producto);

// Reporte

void generarReporteHistorico(lista_Reporte_Historico *&lista, lista_Producto *listaproducto);
void buscarReporteHistorico(lista_Reporte_Historico *lista, char *id_producto, char *id_reporte);
void eliminarReporteHistorico(lista_Reporte_Historico *&lista);
void asignarReporteHistorico(lista_Reporte_Historico *lista, lista_Usuario *usuario);

// Definicion funciones

// General
void agregarElementoPuntero(char *&dato, char *input)
{
    do
    {
        std::cin.getline(input, 250);
        if(input[0] == '\0')
        {
            input[0] = '\0';
            continue;
        }
        else
        {
            break;
        }
    } while(true);

    int length = strlen(input);
    dato = new char[length + 1];
    strcpy(dato, input);
    input[0] = '\0';
}

// Usuario

// Si
void eliminarTodo(lista_Usuario *&lista_usuario, lista_Producto *&lista_producto, lista_Unidad_Medida *&lista_unidad_medida) //! IMPORTANT
{
    while (lista_usuario != NULL)
    {
        lista_Usuario *aux = lista_usuario;

        delete[] aux->usuario.nombres;
        aux->usuario.nombres = NULL;
        delete[] aux->usuario.apellidos;
        aux->usuario.apellidos = NULL;
        delete[] aux->usuario.correo;
        aux->usuario.correo = NULL;
        delete[] aux->usuario.contraseña;
        aux->usuario.contraseña = NULL;
        lista_usuario = lista_usuario->siguiente;
        delete aux;
    }
    while (lista_producto != NULL)
    {
        lista_Producto *aux = lista_producto;
        delete[] aux->producto.unidad_medida;
        aux->producto.unidad_medida = NULL;
        delete[] aux->producto.nombre_producto;
        aux->producto.nombre_producto = NULL;
        delete[] aux->producto.descripcion_producto;
        aux->producto.descripcion_producto = NULL;
        while (lista_producto->producto.años_producto != NULL)
        {
            Lista_Año *año_actual = lista_producto->producto.años_producto;
            for (int i = 0; i < 12; i++)
            {
                while (año_actual->año_producto.producto[i].lotes != NULL)
                {
                    cola_Lote *lote_actual = año_actual->año_producto.producto[i].lotes;
                    delete[] lote_actual->lote.id_lote;
                    lote_actual->lote.id_lote = NULL;
                    año_actual->año_producto.producto[i].lotes = año_actual->año_producto.producto[i].lotes->siguiente;
                    delete lote_actual;
                    lote_actual = NULL;
                }
                while (año_actual->año_producto.producto[i].movimientos != NULL)
                {
                    lista_Movimiento *movimiento_actual = año_actual->año_producto.producto[i].movimientos;
                    delete[] movimiento_actual->movimiento.tipo_movimiento;
                    movimiento_actual->movimiento.tipo_movimiento = NULL;
                    año_actual->año_producto.producto[i].movimientos = año_actual->año_producto.producto[i].movimientos->siguiente;
                    delete movimiento_actual;
                    movimiento_actual = NULL;
                }
            }
            lista_producto->producto.años_producto = lista_producto->producto.años_producto->siguiente;
            delete año_actual;
            año_actual = NULL;
        }

        lista_producto = lista_producto->siguiente;
        delete aux;
        aux = NULL;
    }

    while (lista_unidad_medida != NULL)
    {
        lista_Unidad_Medida *aux = lista_unidad_medida;
        delete[] aux->unidad_medida;
        aux->unidad_medida = NULL;
        lista_unidad_medida = lista_unidad_medida->siguiente;
        delete aux;
        aux = NULL;
    }

    exit(0);
}

#endif