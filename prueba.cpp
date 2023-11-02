#include <ctime>
#include <iostream>
#include <string.h>
#include <limits>
#include <cstdio>
void agregarElementoPuntero(char *&dato, char *input)
{
    std::cin.getline(input, 50, '\n');
    int length = strlen(input);
    dato = new char[length + 1];
    strcpy(dato, input);
    input[0] = '\0';
}
int soloEnteros(int numero)
{
    if (std::cin >> numero)
    {
        return numero;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return numero;
}

double soloFlotantes(double numero)
{
    if (std::cin >> numero)
    {
        return numero;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return numero;
}

char *primerNombre(char *nombre)
{
    return strtok(nombre, " ");
}

int obtenerAño(int &año)
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    año = now->tm_year + 1900;
    return año;
}
int obtenerMes(int &mes)
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    mes = now->tm_mon + 1;
    return mes;
}
int obtenerDia(int &dia)
{
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    dia = now->tm_mday;
    return dia;
}

char input[250];
struct Fecha
{
    int dia;
    int mes;
    int año;
};

struct lista_Unidad_Medida
{
    char *unidad_medida;
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
    int lotes_cantidad = 0;
    bool validacion = false;
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
    char *nombre_completo;
    int telefono;
    char *correo;
    char *contraseña;
    bool administrador;
};

struct Producto
{
    int id_producto;
    char *nombre_producto;
    char *unidad_medida;
    char *descripcion_producto;
    Lista_Año *años_producto = NULL;
    int existencia_cantidad;
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
lista_Usuario *usuario_actual = NULL;

// Usuario

void agregarProductoEnLista(lista_Producto *&producto, char *input);
void mostrarTodosProducto(lista_Producto *&producto);
void mostrarProducto(lista_Producto *&producto);
void buscarProducto(lista_Usuario *lista, char *id_producto); //! important
void modificarProducto(lista_Usuario *&lista);
void eliminarTodaListaProducto(lista_Usuario *&lista);
void eliminarListaProducto(lista_Usuario *&lista, char *nombre, char *codigo_acceso);

// Lote

void agregarLotesAProducto(cola_Lote *&cola);
void mostrarLotesDeProducto(cola_Lote *cola, char *id_producto);
void mostrarLotesDeTodosProductos(cola_Lote *cola);
void buscarLote(cola_Lote *cola, char *id_producto);
void modificarLoteDeProducto(cola_Lote *&cola);
void eliminarLoteYMovimientoDeProducto(cola_Lote *&cola_lote, lista_Movimiento *&cola_movimiento, char *id_producto, char *codigo_acceso);
void eliminarLotesYMovimientosTodoDeProducto(cola_Lote *&cola_lote, lista_Movimiento *&cola_movimiento, char *id_producto, char *codigo_acceso);

void agregarUnidadMedida(lista_Unidad_Medida *lista, char *input);
bool comprobarUnidadMedida(lista_Unidad_Medida *lista, char *unidad_medida);
char *generarIdLote(int dia, int mes, int año, Informacion_Mes *mes_actual);
int conteo_id_producto = 0;
int main()
{

    return 0;
}

void agregarUnidadMedida(lista_Unidad_Medida *lista, char *input)
{
    char *unidad_medida;
    if (lista == NULL)
    {
        std::cout << "Antes de comenzar a ingresar productos, debes establecer al menos una unidad de medida en el sistema\n";
        std::cout << "Ingresar unidad de medida: ";
        agregarElementoPuntero(lista->unidad_medida, input);
        std::cout << "Unidad de medida agregada exitosamente.";
        system("pause");
        return;
    }
    else
    {
        std::cout << "Ingrese la nueva unidad de medida: ";
        agregarElementoPuntero(unidad_medida, input);
        while (lista != NULL)
        {
            if (strcmp(unidad_medida, lista->unidad_medida) == 0)
            {
                std::cout << "Esta unidad de medida ya existe dentro de la lista de unidades de medida.";
                system("pause");
                delete[] unidad_medida;
                return;
            }
            lista = lista->siguiente;
        }
        std::cout << "Unidad de medida añadida al sistema exitosamente.";
    }
    delete[] unidad_medida;
}
void agregarProductoEnLista(lista_Producto *&producto, char *input)
{
    char *unidad_medida;
    if (lista_unidad_medida == NULL)
    {
        agregarUnidadMedida(lista_unidad_medida, input);
    }
    lista_Producto *nuevo_producto = new lista_Producto();
    nuevo_producto->producto.id_producto = ++conteo_id_producto;
    std::cout << "Ingresar el nombre del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.nombre_producto, input);
    std::cout << "Ingresar unidad de medida: ";
    agregarElementoPuntero(unidad_medida, input);
    if (!comprobarUnidadMedida(lista_unidad_medida, unidad_medida))
    {
        std::cout << "\nSerás enviado al menú anterior.\n";
        system("pause");
        conteo_id_producto--;
        delete[] unidad_medida;
        delete[] nuevo_producto->producto.nombre_producto;
        delete nuevo_producto;
        return;
    }
    delete[] unidad_medida;
    std::cout << "Ingresar descripción del producto: ";
    agregarElementoPuntero(nuevo_producto->producto.descripcion_producto, input);
    std::cout << "Para ingresar la cantidad en existencia (no puede ser menor que 0) ";
    std::cout << "Ten en cuenta que, si es un valor mayor que cero, se generará un lote en este preciso momento\n";
    std::cout << "Ingresar cantidad en existencia: ";
    nuevo_producto->producto.existencia_cantidad = soloEnteros(nuevo_producto->producto.existencia_cantidad);
    if (nuevo_producto->producto.existencia_cantidad <= 0)
    {
        nuevo_producto->producto.existencia_cantidad = 0;
    }
    else
    {
        Lista_Año *año_actual = nuevo_producto->producto.años_producto;
        int año = obtenerAño(año);
        año_actual->año_producto.año = año;
        int mes = obtenerMes(mes);
        Informacion_Mes *mes_actual = &año_actual->año_producto.producto[mes];
        int dia = obtenerDia(dia);
        Lote lote_actual = mes_actual->lotes->lote;
        cola_Lote *nuevo_lote = new cola_Lote;
        char *id_lote = generarIdLote(dia, mes, año, mes_actual);
        lote_actual.id_lote = new char[strlen(id_lote) + 1];
        strcpy(lote_actual.id_lote, id_lote);
        lote_actual.ingreso_fecha = {dia, mes, año};
        while (true)
        {
            std::cout << "\nIngrese la fecha de expiración del lote en formato dd/mm//yy: ";
            scanf("%2d/%2d/%2d", &dia, &mes, &año);
            if (!((dia < 1 || dia > 31) || (mes < 1 || mes > 12) || (año < 1)))
            {
                lote_actual.expiracion_fecha = {dia, mes, año};
                break;
            }
            std::cout << "Error al ingresar la fecha. Vuelve a intentarlo.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("pause");
        }
        std::cout << "Ingrese el precio actual del producto: ";
        lote_actual.precio_producto = soloFlotantes(lote_actual.precio_producto);
        lote_actual.cantidad_de_producto = nuevo_producto->producto.existencia_cantidad;
        lote_actual.lotes_cantidad++;
        std::cout << "Producto ingresado exitosamente.\n";
        system("pause");
    }
    // nuevo_lote->lote.id_lote =

    // Ejecutar un codigo para generar un lote con un año y mes nuevo en el caso de que no hayan sido ingresados
}

char *generarIdLote(int dia, int mes, int año, Informacion_Mes *mes_actual)
{
    char id[20];
    int incremental = 0;
    while (mes_actual->lotes !=NULL)
    {
        incremental++;
        mes_actual->lotes = mes_actual->lotes->siguiente;
    }
    sprintf(id,"%d%02d%02d%d%d", conteo_id_producto, dia, mes, año %100, incremental);
    char *id_total = new char[strlen(id)+1];
    strcpy(id_total,id);
    return id_total;
}
bool comprobarUnidadMedida(lista_Unidad_Medida *lista, char *unidad_medida)
{
    do
    {
        if (strcmp(lista->unidad_medida, unidad_medida) == 0)
        {
            return true;
        }
        lista = lista->siguiente;
        if (lista == NULL)
        {
            std::cout << "Unidad de medida no encontrada en el sistema. ";
            return false;
        }
    } while (lista != NULL);
    return false;
}

/*
void insertarLote(lista_Producto *productos, int id_producto, int año, int mes, Lote nuevo_lote)
{

    // 1. Buscar el producto correcto
    lista_Producto *producto_actual = productos;
    while (producto_actual != nullptr && producto_actual->producto.id_producto != id_producto)
    {
        producto_actual = producto_actual->siguiente;
    }
    if (producto_actual == nullptr)
    {
        std::cout << "Producto no encontrado." << std::endl;
        return;
    }

    // 2. Buscar el año correcto
    Lista_Año *año_actual = producto_actual->producto.años_producto;
    while (año_actual != nullptr && año_actual->año_producto.año != año)
    {
        año_actual = año_actual->siguiente;
    }
    if (año_actual == nullptr)
    {
        std::cout << "Año no encontrado." << std::endl;
        return;
    }

    // 3. Buscar el mes correcto
    if (mes < 1 || mes > 12)
    {
        std::cout << "Mes inválido." << std::endl;
        return;
    }

    Informacion_Mes *mes_actual = &año_actual->año_producto.producto[mes - 1];

    // 4. Insertar el lote en la cola
    cola_Lote *nuevo_nodo = new cola_Lote;
    nuevo_nodo->lote = nuevo_lote;
    nuevo_nodo->siguiente = nullptr;
    if (mes_actual->lotes == nullptr)
    {
        // La cola está vacía
        mes_actual->lotes = nuevo_nodo;
    }
    else
    {
        // Insertar al final de la cola
        cola_Lote *ultimo = mes_actual->lotes;
        while (ultimo->siguiente != nullptr)
        {
            ultimo = ultimo->siguiente;
        }
        ultimo->siguiente = nuevo_nodo;
    }

    //producto_actual->producto.años_producto->año_producto.producto[mes-1].lotes->lote.cantidad_de_producto;
}

*/
