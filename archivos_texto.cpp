#include "structs.h"
#include "complemento.cpp"

// Usuarios

void escribirEnArchivoDeUsuario(lista_Usuario *usuario_actual);
void leerEnArchivoDeUsuario(lista_Usuario *&lista_usuario);
void agregarDatosDeUsuario(lista_Usuario *&nuevo_usuario, std::istringstream &linea);
void guardarUsuario(lista_Usuario *&nuevo_usuario);
void escribirEnArchivoDeUsuarioTodo(lista_Usuario *lista_usuario);

// Productos
json estructuraProductoAJSON(Producto &producto);
json estructuraFechaAJSON(Fecha &fecha);
json estructuraLoteAJSON(Lote &lote);
json estructuraMovimientoAJSON(Movimiento &movimiento);
json estructuraListaAñoAJSON(Lista_Año *lista_año);
json estructuraInformacionMesAJSON(Informacion_Mes *mes_actual);
json listaProductoAJSON(lista_Producto *lista_producto);
json agregarListaAño(Lista_Año *lista_año);
json agregarListaLote(cola_Lote *cola_lote);
json agregarInformacionMes(Informacion_Mes *mes);
void escribirProductosEnArchivo(lista_Producto *lista_producto);
void leerProductosDeArchivo(lista_Producto *&lista_producto);
Lista_Año *agregarListaAño(lista_Producto *&producto_actual, const json &item);
void guardarAñoEnLista(lista_Producto *&producto_actual, Lista_Año *&año_actual);
char *agregarPuntero(std::string, const json &item);
Fecha leerFecha(std::string, const json &item);
json estructuraFechaAJSON(Fecha &fecha)
{
    json j;
    j["dia"] = fecha.dia;
    j["mes"] = fecha.mes;
    j["año"] = fecha.año;
    return j;
}
json estructuraMovimientoAJSON(Movimiento &movimiento)
{
    json j;
    j["id_producto"] = movimiento.id_producto;
    j["id_lote"] = movimiento.id_lote;
    j["id_movimiento"] = movimiento.id_movimiento;
    j["tipo_movimiento"] = movimiento.tipo_movimiento;
    j["fecha_movimiento"] = estructuraFechaAJSON(movimiento.fecha);
    j["cantidad"] = movimiento.cantidad;
    return j;
}

json estructuraLoteAJSON(Lote &lote)
{
    json j;
    j["id_lote"] = lote.id_lote;
    j["ingreso_fecha"] = estructuraFechaAJSON(lote.ingreso_fecha);
    j["expiracion_fecha"] = estructuraFechaAJSON(lote.expiracion_fecha);
    j["cantidad_de_producto"] = lote.cantidad_de_producto;
    j["precio_producto"] = lote.precio_producto;
    j["validacion"] = (lote.validacion) ? "Si" : "No";
    j["motivo"] = lote.motivo;
    return j;
}
json agregarListaLote(cola_Lote *cola_lote)
{
    json j = json::array();
    cola_Lote *aux = cola_lote;
    while (aux != NULL)
    {
        j.push_back(estructuraLoteAJSON(cola_lote->lote));
        aux = aux->siguiente;
    }
    return j;
}
json estructuraInformacionMesAJSON(Informacion_Mes *mes_actual)
{
    json j;
    j["mes"] = mes_actual->mes;
    j["lotes"] = agregarListaLote(mes_actual->lotes);
    j["lotes_cantidad"] = mes_actual->lotes_cantidad;
    return j;
}
json agregarInformacionMes(Informacion_Mes *mes)
{
    json j = json::array();
    for (int i = 0; i < 12; i++)
    {
        if (mes[i].lotes != NULL)
        {
            j.push_back(estructuraInformacionMesAJSON(&mes[i]));
        }
    }
    return j;
}
json estructuraListaAñoAJSON(Año_Producto &año_producto)
{
    json j;
    j["año"] = año_producto.año;
    j["informacion_mes"] = agregarInformacionMes(año_producto.producto);
    return j;
}
json agregarListaAño(Lista_Año *lista_año)
{
    json j = json::array();
    Lista_Año *aux = lista_año;
    while (aux != NULL)
    {
        j.push_back(estructuraListaAñoAJSON(aux));
        aux = aux->siguiente;
    }
    return j;
}
json estructuraProductoAJSON(Producto &producto)
{
    return json{
        {"id_producto", producto.id_producto},
        {"nombre_producto", producto.nombre_producto},
        {"descripcion_producto", producto.descripcion_producto},
        {"lista_año", agregarListaAño(producto.años_producto)},
        {"existencia_cantidad", producto.existencia_cantidad},
        {"minima_cantidad", producto.minima_cantidad},
        {"anulado", (producto.anulado) ? "Si" : "No"},
    };
}

json listaProductoAJSON(lista_Producto *lista_producto)
{
    json j = json::array();
    lista_Producto *aux = lista_producto;
    while (aux != NULL)
    {
        j.push_back(estructuraProductoAJSON(aux->producto));
        aux = aux->siguiente;
    }
    return j;
}
void escribirProductosEnArchivo(lista_Producto *lista_producto)
{
    std::ofstream file("productos.json");
    if (file.is_open())
    {
        json j = listaProductoAJSON(lista_producto);
        file << j.dump(4);
        file.close();
    }
}

char *agregarPuntero(std::string texto, const json &item)
{
    if (!item.contains(texto))
    {
        return NULL;
    }
    std::string information = item[texto].get<std::string>();
    char *dato = new char[information.length() + 1];
    strcpy(dato, information.c_str());
    return dato;
}
void guardarAñoEnLista(lista_Producto *&producto_actual, Lista_Año *&año_actual)
{
    Lista_Año *aux = lista_producto->producto.años_producto; // Reservamos el valor original de la lista
    Lista_Año *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la lista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (lista_producto->producto.años_producto == aux)
    { // Nunca pasó por el while
        lista_producto->producto.años_producto = año_actual;
    }
    else
    { // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
        aux2->siguiente = año_actual;
    }
    año_actual->siguiente = aux; // nuevo_producto apunta a NULL
}
Fecha leerFecha(const json &item)
{
    Fecha fecha;
    fecha.dia = item["dia"].get<int>();
    fecha.mes = item["mes"].get<int>();
    fecha.año = item["año"].get<int>();
    return fecha;
}
Lista_Año *agregarListaAño(lista_Producto *&producto_actual, const json &item)
{
    if (item.contains("lista_año") && item["lista_año"].is_array())
    {
        for (const json &year_item : item["lista_año"])
        {
            Lista_Año *nuevo_año = new Lista_Año();
            nuevo_año->año_producto.año = year_item["año"].get<int>();
            if (year_item.contains("informacion_mes") && item["informacion_mes"].is_array())
            {
                for (const json &month_item : year_item["informacion_mes"])
                {
                    int mes = month_item["mes"].get<int>();
                    Informacion_Mes *mes_actual = &nuevo_año->año_producto.producto[mes - 1];
                    mes_actual->mes = month_item["mes"].get<int>();
                    if (month_item.contains("lotes") && month_item["lotes"].is_array())
                    {
                        for (const json &lot_item : month_item["lotes"])
                        {
                            cola_Lote *nuevo_lote = new cola_Lote();
                            nuevo_lote->lote.id_lote = agregarPuntero("id_lote", lot_item);
                            nuevo_lote->lote.ingreso_fecha = leerFecha(lot_item["ingreso_fecha"]);
                            nuevo_lote->lote.expiracion_fecha = leerFecha(lot_item["expiracion_fecha"]);
                            nuevo_lote->lote.cantidad_de_producto = lot_item["cantidad_de_producto"].get<int>();
                            nuevo_lote->lote.precio_producto = lot_item["precio_producto"].get<int>();
                            bool validacion = (lot_item["validacion"].get<std::string>() =="Si");
                            nuevo_lote->lote.validacion = validacion;
                            nuevo_lote->lote.motivo = lot_item["motivo"].get<int>();
                            //agregar para guardar lotes en la lista
                            //terminar de detalles y revisar codigo
                        }
                    }
                    mes_actual->lotes_cantidad = month_item["lotes_cantidad"].get<int>();
                }
            }

            guardarAñoEnLista(producto_actual, nuevo_año);
        }
    }

    return NULL; // agregar el return correspondiente
}
void leerProductosDeArchivo(lista_Producto *&lista_producto)
{
    std::ifstream file("productos.json");
    if (file.is_open())
    {
        json j;
        file >> j;
        for (const auto &item : j)
        {
            lista_Producto *nuevo_producto = new lista_Producto();
            nuevo_producto->producto.id_producto = item["id_producto"].get<int>();
            nuevo_producto->producto.nombre_producto = agregarPuntero("nombre_producto", item);
            nuevo_producto->producto.descripcion_producto = agregarPuntero("descripcion_producto", item);
            // agregar lista_producto;
            nuevo_producto->producto.existencia_cantidad = item["existencia_cantidad"].get<int>();
            nuevo_producto->producto.minima_cantidad = item["minima_cantidad"].get<int>();
            bool anulado = (item["anulado"].get<std::string>() == "Si");
            nuevo_producto->producto.anulado = anulado;
            guardarProductoEnLista(lista_producto, nuevo_producto);
        }
    }
}
void escribirEnArchivoDeUsuarioTodo(lista_Usuario *lista_usuario)
{
    std::ofstream archivo("usuarios.txt", std::ios::trunc);
    if (!archivo)
    {
        return;
    }
    lista_Usuario *aux = lista_usuario;
    while (aux != NULL)
    {
        archivo << aux->usuario.nombres << ";";
        archivo << aux->usuario.apellidos << ";";
        archivo << aux->usuario.telefono << ";";
        archivo << aux->usuario.correo << ";";
        archivo << aux->usuario.contraseña << ";";
        archivo << (aux->usuario.administrador ? "Si" : "No") << ";";
        archivo << (aux->usuario.validacion ? "Si" : "No");
        archivo << std::endl;
        aux = aux->siguiente;
    }
    archivo.close();
}

void escribirEnArchivoDeUsuario(lista_Usuario *usuario_actual)
{
    std::ofstream archivo("usuarios.txt", std::ios::app);
    if (!archivo)
    {
        return;
    }
    archivo << std::endl;
    archivo << usuario_actual->usuario.nombres << ";";
    archivo << usuario_actual->usuario.apellidos << ";";
    archivo << usuario_actual->usuario.telefono << ";";
    archivo << usuario_actual->usuario.correo << ";";
    archivo << usuario_actual->usuario.contraseña << ";";
    archivo << (usuario_actual->usuario.administrador ? "Si" : "No") << ";";
    archivo << (usuario_actual->usuario.validacion ? "Si" : "No");
    archivo << std::endl;

    archivo.close();
}

void leerEnArchivoDeUsuario(lista_Usuario *&lista_usuario)
{
    std::ifstream archivo("usuarios.txt", std::ios::in);
    if (!archivo)
    {
        return;
    }
    std::string dato;
    while (getline(archivo, dato))
    {
        if (dato.empty())
            continue;
        std::istringstream iss(dato);
        lista_Usuario *nuevo_usuario = new lista_Usuario;
        nuevo_usuario->siguiente = NULL;
        agregarDatosDeUsuario(nuevo_usuario, iss);
        guardarUsuario(nuevo_usuario);
    }
}
void agregarDatosDeUsuario(lista_Usuario *&nuevo_usuario, std::istringstream &linea)
{
    std::string informacion;
    std::getline(linea, informacion, ';');
    nuevo_usuario->usuario.nombres = new char[informacion.length() + 1];
    strcpy(nuevo_usuario->usuario.nombres, informacion.c_str());
    std::getline(linea, informacion, ';');
    nuevo_usuario->usuario.apellidos = new char[informacion.length() + 1];
    strcpy(nuevo_usuario->usuario.apellidos, informacion.c_str());
    std::getline(linea, informacion, ';');
    nuevo_usuario->usuario.telefono = std::stoi(informacion);
    std::getline(linea, informacion, ';');
    nuevo_usuario->usuario.correo = new char[informacion.length() + 1];
    strcpy(nuevo_usuario->usuario.correo, informacion.c_str());
    std::getline(linea, informacion, ';');
    nuevo_usuario->usuario.contraseña = new char[informacion.length() + 1];
    strcpy(nuevo_usuario->usuario.contraseña, informacion.c_str());
    std::getline(linea, informacion, ';');
    bool validacion = (informacion == "Si") ? true : false;
    nuevo_usuario->usuario.validacion = validacion;
    std::getline(linea, informacion, ';');
    bool administrador = (informacion == "Si") ? true : false;
    nuevo_usuario->usuario.administrador = administrador;
    guardarUsuario(nuevo_usuario);
}
void guardarUsuario(lista_Usuario *&nuevo_usuario)
{
    lista_Usuario *aux = lista_usuario; // Reservamos el valor original de la lista
    lista_Usuario *aux2;
    while (aux != NULL)
    {                         // Comprobamos que aux no apunte a null
        aux2 = aux;           // Reservamos el valor original de aux que por ahora es la llista
        aux = aux->siguiente; // Corre una posición, buscando NULL
    }
    if (aux == lista_usuario) // Nunca pasó por el while
    {
        lista_usuario = nuevo_usuario;
    }
    else // Al pasar por el while, sabemos que aux2 apunta una posicion antes de NULL, que debe ser aux
    {
        aux2->siguiente = nuevo_usuario;
    }
    nuevo_usuario->siguiente = aux; // nuevo_usuario apunta a NULL
}

void agregarDatosDeProducto(lista_Producto *&nuevo_producto)
{
    std::ifstream archivo("productos.txt", std::ios::in);
    if (!archivo)
    {
        return;
    }
    // codigo
}
