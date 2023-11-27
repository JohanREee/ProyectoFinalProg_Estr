
#ifndef structs
#define structs

#define MAXCHAR 250

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <locale.h> /* NO ESTOY SEGURO*/
#include <nlohmann/json.hpp>
#include <iomanip>
using json = nlohmann::json;

extern char input[];

struct Fecha
{
    int dia;
    int mes;
    int ano;
};
struct Lote
{
    char *id_lote = NULL;
    Fecha ingreso_fecha;
    Fecha expiracion_fecha;
    double precio_producto = 0;
    int cantidad_de_producto = 0;
    double costo_venta = 0; // new
    bool validacion = false;
    int motivo = 0;
    // 1 significa fecha de caducidad
    // 2 significa que no tiene productos en existencia
};

struct cola_Lote
{ // Cola para los lotes de un producto
    Lote lote;
    cola_Lote *siguiente;
};

struct Informacion_Mes
{
    int mes = 0;
    cola_Lote *lotes = NULL;
    int lotes_cantidad = 0;
};

struct Ano_Producto
{
    int ano = 0;
    Informacion_Mes producto[12];
};

struct Lista_Ano
{ // Lista enlazada para cada ano
    Ano_Producto ano_producto;
    Lista_Ano *siguiente;
};

struct Producto
{
    int id_producto = 0;
    char *nombre_producto = NULL;
    char *descripcion_producto = NULL;
    Lista_Ano *anos_producto = NULL;
    int existencia_cantidad = 0;
    int minima_cantidad = 0;
    double costo_de_venta_total = 0; // Costo de todos los lotes con cada cantidad que tienen
    double porcentaje_ganancia = 0; // va de 0 a 1
    bool anulado = false;
};

struct lista_Producto
{ // Lista enlazada con todos los productos
    Producto producto;
    lista_Producto *siguiente;
};

struct Usuario
{
    char *nombres = NULL;
    char *apellidos = NULL;
    int telefono = 0;
    char *correo = NULL;
    char *contrasena = NULL;
    bool administrador;
    bool validacion = false;
};

struct lista_Usuario
{
    Usuario usuario;
    lista_Usuario *siguiente;
};

struct lote_Alerta_Caducidad
{
    char *nombre_producto = NULL;
    char *id_lote = NULL;
    Fecha fecha_expiracion;
    double costo_venta = 0;
};

struct lista_Lote_Alerta_Caducidad
{
    lote_Alerta_Caducidad lote;
    lista_Lote_Alerta_Caducidad *siguiente;
};

struct producto_Alerta_Cantidad
{
    char *nombre_producto = NULL;
    int id_producto = 0;
    int actual_cantidad = 0;
    int minima_cantidad = 0;
    double costo_de_venta_total = 0;
};

struct lista_Producto_Alerta_Cantidad
{
    producto_Alerta_Cantidad producto;
    lista_Producto_Alerta_Cantidad *siguiente;
};

struct producto_Existencia
{
    char *nombre_producto = NULL;
    int id_producto = 0;
    int actual_cantidad = 0;
};

struct lista_Producto_Existencia
{
    producto_Existencia producto;
    lista_Producto_Existencia *siguiente;
};

struct reporte_Rango
{
    char *id_lote = NULL;
    Fecha ingreso_fecha;
    Fecha expiracion_fecha;
    double precio_producto = 0;
    int cantidad_de_producto = 0;
};

struct lista_Reporte_Rango
{
    reporte_Rango lote;
    lista_Reporte_Rango *siguiente;
};

extern lista_Usuario *lista_usuario;
extern lista_Producto *lista_producto;
extern lista_Usuario *usuario_activo;
extern lista_Lote_Alerta_Caducidad *lote_caducidad;
extern lista_Producto_Alerta_Cantidad *producto_cantidad;
extern lista_Producto_Existencia *producto_existencia;
extern lista_Reporte_Rango *reporte_rango;

extern int conteo_id_producto, conteo_id_movimiento;

// Prototipado de funcionaes

// Complemento
int soloEnteros();
double soloFlotantes();
char *nombreFormal(Usuario usuario_actual);
Lista_Ano *buscarAnoActualDeProducto(lista_Producto *producto, int ano);
bool validarDiaPorMes(int dia, int mes, int ano);
bool esBisiesto(int ano);
void asociarMesConNumero(int mes);
void limpiarBuffer();
void verificarModificacionEnLote(int &op);
void verificarModificacionEnProducto(int &op);
bool verificarModificacionEnUsuario(int &op);
bool comprobarCorreo(char *correo, lista_Usuario *lista_usuario);
void pausar();
void limpiar();
void pausarYLimpiar();
char *digitarContrasena();
int obtenerAno();
int obtenerMes();
int obtenerDia();
bool comprobarEstadoFecha2(int dia, int mes, int ano, lista_Lote_Alerta_Caducidad *lote_actual);
void gotoxy(int x, int y);
// General

void agregarElementoPuntero(char *&dato, char *input);
void modificarElementoPuntero(char *&dato, char *input);
void eliminarTodo(lista_Usuario *&lista_usuario, lista_Producto *&lista_producto);
bool ingresarFechaExpiracion(int ano, int mes, int dia, int anoe, int mese, int diae);
void asociarMesConNumero(int mes);
void inicioSesion(int &opcion);
void ingresarDatos(lista_Usuario *lista_usuario);

// Menu

void menuPrincipal(int &opcion);
void menuGestionProductos(int &opcion, char *&user);
void menuGestionLotes(int &opcion, char *&user);
void menuReporteHistorico(int &opcion, char *&user);
void menuGestionUsuarios(int &opcion, char *&user);
void marco();

// Usuarios
void agregarUsuarioMaestro(lista_Usuario *&lista_usuario);
void agregarUsuarioEnLista(lista_Usuario *&lista_usuario);
void mostrarUsuarioEnPantalla(lista_Usuario *lista_usuario);
void mostrarUsuario(Usuario usuario);
lista_Usuario *buscarUsuarioParaSesion(lista_Usuario *lista, char *correo, char *contrasena);
lista_Usuario *buscarUsuario(lista_Usuario *lista, char *correo);
void modificarUsuario(lista_Usuario *&lista_usuario, char *&user);
void eliminarUsuario(lista_Usuario *&lista_usuario);
void activarUsuario(lista_Usuario *&lista_usuario);
void modificarNombreYApellido(lista_Usuario *&usuario_actual, char *user);
void modificarTelefono(lista_Usuario *&usuario_actual, char *user);
void modificarCorreo(lista_Usuario *&usuario_actual, char *user);
void modificarContrasena(lista_Usuario *&usuario_actual, char *user);
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
void mostrarProducto(lista_Producto *producto);
void mostrarProductos(lista_Producto *producto, bool show);
void asignarMesAEstructura(Informacion_Mes *mes_actual);
void guardarListaAno(Lista_Ano *&ano_actual);
void calcularCostoVentaTotal(lista_Producto *&producto_actual);
void asignarCostoVentaACadaLote(lista_Producto *&producto_actual);
// Lote
void agregarPrimerLote(lista_Producto *&producto);
char *generarIdLote(int dia, int mes, int ano, Informacion_Mes *mes_actual, Producto producto_actual);
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
void eliminarLoteDeProducto();
bool comprobarEstadoFecha(int dia, int mes, int ano, cola_Lote *lote_actual);
void registroDeInformacionLote(Lote &lote);
void borrarLote(lista_Producto *&producto_actual, char *id_lote);
void registroDeVentas();

// Movimiento

// Alerta de caducidad

void generarAlertaCaducidad();
void mostrarAlertaCaducidad(lista_Lote_Alerta_Caducidad *lote_actual);
void mostrarAlertaAlertaCaducidad(lista_Lote_Alerta_Caducidad *lote_actual, int &y);
void mostrarAlertaAlertaCantidadMinima(lista_Producto_Alerta_Cantidad *producto_actual, int &y);
void sumarFecha(int &ano, int &mes, int &dia, int cantidad);
void guardarLoteEnLista(lista_Lote_Alerta_Caducidad *&lista_lote);
void eliminarListaDeAlerta(lista_Lote_Alerta_Caducidad *&lista);

// Alerta de cantidad minima en stock

void generarAlertarCantidadMinima();
void mostrarAlertaCantidadMinima(lista_Producto_Alerta_Cantidad *producto_actual);
void guardarProductoEnLista(lista_Producto_Alerta_Cantidad *&producto_actual);
void eliminarListaProductoCantidadMinima();

// Reportes
void guardarProductoEnListaDeReporteDeExistencia(lista_Producto_Existencia *&producto_existencia);
void mostrarProductoDeReporteDeExistencia(lista_Producto_Existencia *producto_actual);
void eliminarListaDeReporteDeExistencia(lista_Producto_Existencia *&producto_existencia);
void generarReporteDeLotesPorRango();
void guardarLoteEnListaDeReporteDeRango(lista_Reporte_Rango *&reporte_actual);
void mostrarLoteDeReporteDeRango(lista_Reporte_Rango *lote_actual);
void eliminarListaDeReporteDeRango(lista_Reporte_Rango *&reporte_rango);
bool buscarLotesPorFecha(lista_Producto *producto_actual, Fecha fecha_inicio = {0, 0, 0}, Fecha fecha_final = {0, 0, 0});
bool validarFecha(Fecha fecha_inicio, Fecha fecha_final, cola_Lote *lote_actual);
void generarReporteDeLotesPorExpirar();
bool buscarLoteParaReporteDeLotesPorExpirar(Fecha fecha);
void generarReporteStockCritico();
void generarReporteCostoInventario();
void generarReporteDeExistenciasActuales(lista_Producto *lista_producto, lista_Producto_Existencia *&producto_existencia);
bool buscarProductosDeReporteStockMinimo();

// JSON 
// JSON USERS
json estructuraUsuarioAJSON(Usuario &usuario);
json listaUsuariosAJSON(lista_Usuario *&lista_usuario);
void escribirUsuariosAJSON(lista_Usuario *&lista_usuario);
void leerUsuariosEnJSON(lista_Usuario *&lista_usuario);
void guardarUsuario(lista_Usuario *&nuevo_usuario);
// JSON PRODUCTS

json estructuraProductoAJSON(Producto &producto);
json estructuraFechaAJSON(Fecha &fecha);
json estructuraLoteAJSON(Lote &lote);
json estructuraListaAnoAJSON(Ano_Producto &ano_producto);
json estructuraInformacionMesAJSON(Informacion_Mes *mes_actual);
json listaProductoAJSON(lista_Producto *lista_producto);
json agregarListaAno(Lista_Ano *lista_ano);
json agregarListaLote(cola_Lote *cola_lote);
json agregarInformacionMes(Informacion_Mes *mes);
void escribirProductosEnArchivoJSON(lista_Producto *lista_producto);
void leerProductosDeArchivo(lista_Producto *&lista_producto);
void agregarListaAno(lista_Producto *&producto_actual, const json &item);
void guardarAnoEnLista(lista_Producto *&producto_actual, Lista_Ano *&ano_actual);
char *agregarPuntero(std::string, const json &item);
Fecha leerFecha(std::string, const json &item);
void eliminarTodo(lista_Usuario *&lista_usuario, lista_Producto *&lista_producto);
#endif