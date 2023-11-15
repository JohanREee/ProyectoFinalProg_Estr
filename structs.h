
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
    int motivo = 0;
    //1 significa caducidad
    //2 significa que no tiene productos en existencia
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
lista_Usuario *usuario_activo = NULL; 
int conteo_id_producto = 0;

// Prototipado de funcionaes

// General

void agregarElementoPuntero(char *&dato, char *input);
void modificarElementoPuntero(char *&dato, char *input);
void eliminarTodo(lista_Usuario *&lista_usuario, lista_Producto *&lista_producto);
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

// Producto

void agregarProductoEnLista(lista_Producto *&producto, char *input);
void mostrarTodosProducto(lista_Producto *lista_producto);
void mostrarProductos(lista_Producto *producto, bool show = false);
lista_Producto *buscarProducto(lista_Producto *lista, int id_producto);
void modificarProducto(lista_Producto *&lista_producto);
void anularProducto(lista_Producto *&lista_producto);
void obtenerProducto(lista_Producto *lista_producto);
void activarProducto(lista_Producto *&lista_producto);
bool ingresarProducto(lista_Producto *&producto_actual);
void guardarProductoEnLista(lista_Producto *&lista_producto, lista_Producto *&nuevo_producto);
// Lote
void agregarPrimerLote(lista_Producto *&producto);
char *generarIdLote(int dia, int mes, int año, Informacion_Mes *mes_actual, Producto producto_actual);
void agregarLotesAProducto(lista_Producto *&producto);
void guardarLoteEnProducto(Informacion_Mes *mes_actual, cola_Lote *&lote_lista);
bool ingresarLote(lista_Producto *producto_actual, cola_Lote *&lote_actual);
void mostrarLotesDeProducto(cola_Lote *cola);
void mostrarTodosLotesDeTodosProductos(lista_Producto *lista_producto);
void mostrarTodosLotesDeProducto(lista_Producto *lista_producto);
void buscarLote(lista_Producto *lista_producto);
cola_Lote *obtenerLote(lista_Producto *producto, char *id_lote);
void vencerLotes(lista_Producto *&producto);
void modificarLoteDeProducto(lista_Producto *&producto_actual);
void eliminarLoteDeProducto(lista_Producto *&lista_producto);
bool comprobarEstadoFecha(int dia, int mes, int año, cola_Lote *lote_actual);
void registroDeInformacionLote(Lote &lote);

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


// Usuario

// Si
void eliminarTodo(lista_Usuario *&lista_usuario, lista_Producto *&lista_producto) //! IMPORTANT
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

    exit(0);
}

#endif